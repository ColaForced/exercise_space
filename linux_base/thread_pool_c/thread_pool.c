#include "thread_pool.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"


ThreadPool *thread_pool_create(int min, int max, int queueSize)
{
    do
    {
        ThreadPool * pool = (ThreadPool*)(malloc(sizeof(ThreadPool)));
        if(pool == NULL)
        {
            printf("malloc thread pool failed\n");
            break;
        }
        
        pool->workers = (pthread_t *)(malloc(sizeof(pthread_t)*max));
        if(pool->workers == NULL)
        {
            printf("malloc workers failed\n");
            break;
        }
        memset(pool->workers, 0, sizeof(pthread_t)*max);

        pool->minNum = min;
        pool->maxNum = max;
        pool->busyNum = 0;
        pool->liveNum = min;
        pool->exitNum = 0;

        if (pthread_mutex_init(&pool->mutexPool, NULL)!=0||
            pthread_mutex_init(&pool->mutexBusy, NULL)!=0||
            pthread_cond_init(&pool->notEmpty,NULL)!=0||
            pthread_cond_init(&pool->notFull,NULL)!=0)
        {
            printf("mutex of condition init fail...");
            break;
        }

        pool->taskQueue = (Task*)malloc(sizeof(Task)*queueSize);
        pool->queueCapacity = queueSize;
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueRear = 0;
        pool->shutdown = 0;

        pthread_create(&pool->manager, NULL, manager, pool);
        for(int i=0; i<min; ++i)
        {
            pthread_create(&pool->workers[i],NULL,worker,pool);
        }

        return pool;

    } while (0);
    
}



int thread_pool_destory(ThreadPool *pool)
{
    if(pool==NULL)
    {
        return -1;
    }

    pool->shutdown = 1;

    // 唤醒阻塞的消费者线程, 消费者线程会执行完后再退出？
    pthread_join(pool->manager,NULL);
    for(int i=0; i<pool->liveNum; ++i)
    {
        pthread_cond_signal(&pool->notEmpty);
    }

    if(pool->taskQueue)
    {
        free(pool->taskQueue);
        // pool->taskQueue = NULL;
    }

    if(pool->workers)
    {
        free(pool->workers);
        // pool->workers = NULL;
    }

    pthread_mutex_destroy(&pool->mutexPool);
    pthread_mutex_destroy(&pool->mutexBusy);
    pthread_cond_destroy(&pool->notEmpty);
    pthread_cond_destroy(&pool->notFull);

    free(pool);
    pool = NULL;
    return 0;
}


void thread_pool_add_task(ThreadPool*pool, void(*func)(void*), void*arg)
{
    pthread_mutex_lock(&pool->mutexPool);
    while (pool->queueSize == pool->queueCapacity && !pool->shutdown)
    {
        pthread_cond_wait(&pool->notFull, &pool->mutexPool);
    }

    if(pool->shutdown)
    {
        pthread_mutex_unlock(&pool->mutexPool);
        return;
    }

    pool->taskQueue[pool->queueRear].func = func;
    pool->taskQueue[pool->queueRear].arg = arg;
    pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
    pool->queueSize++;

    pthread_cond_signal(&pool->notEmpty);
    pthread_mutex_unlock(&pool->mutexPool);
}



int get_thread_pool_busy_num(ThreadPool *pool)
{
    pthread_mutex_lock(&pool->mutexBusy);
    int tmp = pool->busyNum;
    pthread_mutex_unlock(&pool->mutexBusy);
    return tmp;
}


int get_thread_pool_live_num(ThreadPool *pool)
{
    pthread_mutex_lock(&pool->mutexPool);
    int tmp = pool->liveNum;
    pthread_mutex_unlock(&pool->mutexPool);
    return tmp;
}


void *worker(void *arg)
{
    ThreadPool *pool = (ThreadPool*) arg;
    while (1)
    {
        pthread_mutex_lock(&pool->mutexPool);
        while (pool->queueSize==0 && !pool->shutdown)
        {
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);
            if(pool->exitNum>0)
            {
                pool->exitNum--;
                if(pool->liveNum > pool->minNum)
                {
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexPool);
                    thread_exit(pool);
                }
            }
        }

        if(pool->shutdown)
        {
            pthread_mutex_unlock(&pool->mutexPool);
            thread_exit(pool);
        }

        Task task;
        task.func = pool->taskQueue[pool->queueFront].func;
        task.arg = pool->taskQueue[pool->queueFront].arg;
        pool->queueFront = (pool->queueFront+1)%pool->queueCapacity;
        pool->queueSize--;
        pthread_cond_signal(&pool->notFull);
        pthread_mutex_unlock(&pool->mutexPool);
        
        printf("thread %ld start working...\n", pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexBusy);
        task.func(task.arg);
        
        free(task.arg);
        task.arg = NULL;
         printf("thread %ld end working...\n", pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexBusy);
    }
    return NULL;
}


void *manager(void *arg)
{
    ThreadPool* pool = (ThreadPool*)arg;
    while (!pool->shutdown)
    {
        sleep(3);
        
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->queueSize;
        int liveNum = pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);

        pthread_mutex_lock(&pool->mutexBusy);
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);

        if (queueSize > liveNum && liveNum < pool->maxNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            int counter = 0;
            for(int i=0; i < pool->maxNum && counter < NUMBER; ++i)
            {   
                if(pool->workers[i] == 0)
                {
                    pthread_create(&pool->workers[i], NULL, worker,pool);
                    counter++;
                    pool->liveNum++;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);
        }
        
        if(busyNum*2<liveNum && liveNum>pool->minNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);

            for(int i=0; i<NUMBER; i++)
            {
                pthread_cond_signal(&pool->notEmpty);
            }
        }
    }
    return NULL;
}


void thread_exit(ThreadPool *pool)
{
    pthread_t tid = pthread_self();
    for (int i = 0; i < pool->maxNum; ++i)
    {
        if (pool->workers[i] == tid)
        {
            pool->workers[i] = 0;
            printf("thread_exit() called, %ld exiting...\n", tid);
            break;
        }
    }
    pthread_exit(NULL);
}


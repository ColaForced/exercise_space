#include "task.hpp"
#include "thread_pool.h"
#include <pthread.h>
#include <string.h>
#include <iostream>
#include <string>
#include <unistd.h>

using std::cout;
using std::endl;
using std::to_string;

ThreadPool::ThreadPool(int min, int max)
{
    __task_queue__ = new TaskQueue;
    do
    {
        __minNum__ = min;
        __maxNum__ = max;
        __busyNum__ = 0;
        __aliveNum__ = 0;

        __workers__ = new pthread_t[max];
        memset(__workers__, 0, sizeof(pthread_t)*max);

        if (pthread_mutex_init(&__lock__, nullptr)!=0||
            pthread_cond_init(&__notEmpty__,nullptr)!=0)
        {
            cout << "init mutex or condition fail..." << endl;
            break;
        }

        for(int i=0; i<min; ++i)
        {
            pthread_create(&__workers__[i],nullptr,worker,this);
        }

        pthread_create(&__manager__, nullptr, manager, this);
    } while (0);
}


ThreadPool::~ThreadPool()
{
    __shutdown__ = 1;
    pthread_join(__manager__, nullptr);
    for(int i=0; i<__aliveNum__; ++i)
    {
        pthread_cond_signal(&__notEmpty__);
    }

    if(__task_queue__) delete __task_queue__;
    if(__workers__) delete __workers__;
    pthread_mutex_destroy(&__lock__);
    pthread_cond_destroy(&__notEmpty__);
}


void ThreadPool::add_task(Task &task)
{
    if (__shutdown__) return;

    __task_queue__->add_task(task);
    pthread_cond_signal(&__notEmpty__);
}


int ThreadPool::get_busy_number()
{
    int tmp = 0;
    pthread_mutex_lock(&__lock__);
    tmp = __busyNum__;
    pthread_mutex_unlock(&__lock__);
    return tmp;
}


int ThreadPool::get_alive_number()
{
    int tmp = 0;
    pthread_mutex_lock(&__lock__);
    tmp = __aliveNum__;
    pthread_mutex_unlock(&__lock__);
    return tmp;
}


void* ThreadPool::worker(void* arg)
{
    ThreadPool *pool = static_cast<ThreadPool*>(arg);
    while (true)
    {
        pthread_mutex_lock(&pool->__lock__);
        while (pool->__task_queue__->get_task_number()==0 && !pool->__shutdown__)
        {
            cout << "thread " << to_string(pthread_self()) << " waiting..." << endl;
            pthread_cond_wait(&pool->__notEmpty__, &pool->__lock__);
            if(pool->__exitNum__>0)
            {
                pool->__exitNum__--;
                if(pool->__aliveNum__ > pool->__minNum__)
                {
                    pool->__aliveNum__--;
                    pthread_mutex_unlock(&pool->__lock__);
                    pool->thread_exit();
                }
            }
        }

        if(pool->__shutdown__)
        {
            pthread_mutex_unlock(&pool->__lock__);
            pool->thread_exit();
        }

        Task task = pool->__task_queue__->take_task();
        pool->__busyNum__++;
        pthread_mutex_unlock(&pool->__lock__);
        cout << "thread " << to_string(pthread_self()) << " start working..." << endl;
        task.function(task.arg);

        // delete task.arg;
        task.arg = nullptr;
        cout << "thread " << to_string(pthread_self()) << " end working..."<<endl;
        pthread_mutex_lock(&pool->__lock__);
        pool->__busyNum__--;
        pthread_mutex_unlock(&pool->__lock__);
    }
}


void* ThreadPool::manager(void*arg)
{
    ThreadPool *pool = static_cast<ThreadPool*>(arg);
    while (!pool->__shutdown__)
    {
        sleep(3);

        pthread_mutex_lock(&pool->__lock__);
        int queueSize = pool->__task_queue__->get_task_number();
        int liveNum = pool->__aliveNum__;
        int busyNum = pool->__busyNum__;
        pthread_mutex_unlock(&pool->__lock__);

        if (queueSize > liveNum && liveNum < pool->__maxNum__)
        {
            pthread_mutex_lock(&pool->__lock__);
            int counter = 0;
            for(int i=0; i < pool->__maxNum__ && counter < __NUMBER__; ++i)
            {
                if(pool->__workers__[i] == 0)
                {
                    pthread_create(&pool->__workers__[i], nullptr, worker,pool);
                    counter++;
                    pool->__aliveNum__++;
                }
            }
            pthread_mutex_unlock(&pool->__lock__);
        }

        if(busyNum*2<liveNum && liveNum>pool->__minNum__)
        {
            pthread_mutex_lock(&pool->__lock__);
            pool->__exitNum__ = __NUMBER__;
            pthread_mutex_unlock(&pool->__lock__);

            for(int i=0; i<__NUMBER__; i++)
            {
                pthread_cond_signal(&pool->__notEmpty__);
            }
        }
    }
    return nullptr;
}


void ThreadPool::thread_exit()
{
    pthread_t tid = pthread_self();
    for (int i = 0; i < __maxNum__; ++i)
    {
        if (__workers__[i] == tid)
        {
            __workers__[i] = 0;
            cout << "threadExit() function: thread "
                 << to_string(pthread_self()) << " exiting..." << endl;
            break;
        }
    }
    pthread_exit(NULL);
}


#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H


#include "task.h"
#include <pthread.h>

const int NUMBER = 2;//管理者每次添加线程数

typedef struct ThreadPool
{
    Task *taskQueue;
    int queueCapacity;
    int queueSize;
    int queueFront;
    int queueRear;

    pthread_t manager;
    pthread_t *workers;
    int minNum;
    int maxNum;
    int busyNum;
    int liveNum;
    int exitNum;

    pthread_mutex_t mutexPool;
    pthread_mutex_t mutexBusy;
    pthread_cond_t notFull;
    pthread_cond_t notEmpty;

    int shutdown;
} ThreadPool;


ThreadPool *thread_pool_create(int min, int max, int queueSize);
int thread_pool_destory(ThreadPool *pool);
int get_thread_pool_busy_num(ThreadPool *pool);
int get_thread_pool_live_num(ThreadPool *pool);
void *worker(void *arg);
void *manager(void *arg);
void thread_exit(ThreadPool *pool);

#endif
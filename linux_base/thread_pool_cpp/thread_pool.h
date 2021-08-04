#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include <pthread.h>
#include "task.hpp"



class ThreadPool
{
public:
    ThreadPool(int min, int max);
    ~ThreadPool();
    void add_task(Task &task);
    int get_busy_number();
    int get_alive_number();

private:
    static void *worker(void *arg);
    static void *manager(void*arg);
    void thread_exit();
    static const int __NUMBER__ = 2;

private:
    pthread_mutex_t __lock__;
    pthread_cond_t __notEmpty__;
    pthread_t *__workers__;
    pthread_t __manager__;
    TaskQueue *__task_queue__;
    int __minNum__;
    int __maxNum__;
    int __busyNum__;
    int __aliveNum__;
    int __exitNum__;
    bool __shutdown__ = false;

};

#endif
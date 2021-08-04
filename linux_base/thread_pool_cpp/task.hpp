#ifndef _TASK_HPP
#define _TASK_HPP


#include <pthread.h>
#include <queue>

using callback = void(*)(void*);

struct Task
{
    Task()
    {
        function = nullptr;
        arg = nullptr;
    }

    Task(callback f, void *arg)
    {
        function = f;
        this->arg = arg;
    }

    callback function;
    void *arg;

};



class TaskQueue
{
public:
    TaskQueue()
    {
        pthread_mutex_init(&__mutex__, NULL);
    }

    ~TaskQueue()
    {
        pthread_mutex_destroy(&__mutex__);
    }

    void add_task(Task &task)
    {
        pthread_mutex_lock(&__mutex__);
        __queue__.push(task);
        pthread_mutex_unlock(&__mutex__);
    }

    void add_task(callback func, void *arg)
    {
        Task task(func, arg);
        add_task(task);
    }


    Task take_task()
    {
        Task task;
        pthread_mutex_lock(&__mutex__);
        if(__queue__.size() > 0)
        {
            task = __queue__.front();
            __queue__.pop();
        }
        pthread_mutex_unlock(&__mutex__);
        return task;
    }

    inline int get_task_number()
    {
        return __queue__.size();
    }

private:
    pthread_mutex_t __mutex__;
    std::queue<Task> __queue__;
};

#endif
#include "task.hpp"
#include "thread_pool.h"
#include "thread_pool.cpp"
#include <stdlib.h>
#include <stdio.h>

void task_func(void *arg)
{
    int num = *(int*)arg;
    printf("thread %ld is working, num=%d\n",pthread_self(),num);
    sleep(1);
}

int main(int argc, char const *argv[])
{
    ThreadPool pool(1,5);
    for(int i=0; i<100; ++i)
    {
        int *num = (int*)malloc(sizeof(int));
        *num = i+100;
        Task task(task_func, num);
        pool.add_task(task);
    }

    sleep(30);
    return 0;
}
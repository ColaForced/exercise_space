#include "thread_pool.h"
#include "thread_pool.c"
#include <unistd.h>

void task_func(void *arg)
{
    int num = *(int*)arg;
    printf("thread %ld is working, num=%d\n",pthread_self(),num);
    sleep(1);
}

int main(int argc, char const *argv[])
{
    ThreadPool *pool = thread_pool_create(1,5,100);
    for(int i=0; i<100; ++i)
    {
        int *num = (int*)malloc(sizeof(int));
        *num = i+100;
        thread_pool_add_task(pool,task_func, num);
    }

    sleep(30);
    thread_pool_destory(pool);
    return 0;
}

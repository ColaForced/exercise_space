// 奇了怪了，调用printf函数后线程并没有退出
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


void *working(void *arg)
{
    printf("child thread, id:%ld\n",pthread_self());
    for(int i=0; i<10; i++)
        { printf("child thread counting, i=%d\n",i);}
    return NULL;
}

int main(int argc, char const *argv[])
{   
    printf("father thread, id:%ld\n",pthread_self());
    pthread_t tid;
    pthread_create(&tid, NULL, working, NULL);
    printf("child thread created sucess, id:%ld\n",tid);
    
    pthread_cancel(tid);
    pthread_exit(NULL);
    return 0;
}

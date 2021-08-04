#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


void *working(void *arg)
{
    printf("child thread, id:%ld\n",pthread_self());
    for(int i=0; i<10; i++)
    {
        printf("child thread counting, i=%d\n",i);
        if (i==5) pthread_exit(NULL);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    printf("main thread:%ld\n",pthread_self());

    pthread_t tid;
    pthread_create(&tid, NULL, working, NULL);
    printf("child thread created sucess, id:%ld\n",tid);
    
    for(int i=0; i<10; i++)
    {
        printf("main thread counting, i=%d\n",i);
        if (i==3) pthread_exit(NULL);
    }

    return 0;
}

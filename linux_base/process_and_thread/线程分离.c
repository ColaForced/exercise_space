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
    pthread_t tid;
    pthread_create(&tid, NULL, working, NULL);
    printf("child thread created sucess, id:%ld\n",tid);
    
    pthread_detach(tid);
    pthread_exit(NULL);
    return 0;
}

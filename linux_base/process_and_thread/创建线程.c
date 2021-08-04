#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


void *working(void *arg)
{
    printf("child thread, id:%ld\n",pthread_self());
    return NULL;
}

int main(int argc, char const *argv[])
{
    printf("main thread:%ld\n",pthread_self());

    pthread_t tid;
    pthread_create(&tid, NULL, working, NULL);
    printf("child thread created sucess, id:%ld\n",tid);
    sleep(1);
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>


const int MAX = 100;

int number = 0;
pthread_mutex_t mutex;

void *func_a(void *arg)
{
    for(int i=0; i<MAX; ++i)
    {
        pthread_mutex_lock(&mutex);
        number ++;
        usleep(10);
        pthread_mutex_unlock(&mutex);
        printf("a thread, id:%ld, number:%d\n", pthread_self(),number);
    }
    return NULL;
}


void *func_b(void *arg)
{
    for(int i=0; i<MAX; i++)
    {
        pthread_mutex_lock(&mutex);
        number ++;
        usleep(10);
        pthread_mutex_unlock(&mutex);
        printf("b thread, id:%ld, number:%d\n", pthread_self(),number);
    }
    return NULL;
}


int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, func_a, NULL);
    pthread_create(&t2, NULL, func_b, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}

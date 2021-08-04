// create，join 写在一个循环里为什么会错
// for(int i=0; i<5; i++) 
// {
//     pthread_create(&readThreads[i],NULL, read_func, NULL);
//     pthread_join(readThreads[i], NULL);
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


int num = 0;
pthread_rwlock_t rwlock;


void *write_func(void *arg)
{
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);
        num ++;
        pthread_rwlock_unlock(&rwlock);
        printf("write func: num = %d\n",num);
        usleep(rand()%100);
    }
    
}


void *read_func(void *arg)
{
    while(1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("read func: num = %d\n",num);
        pthread_rwlock_unlock(&rwlock);
        usleep(rand()%100);
    }
    return NULL;
}


int main(int argc, char const *argv[])
{
    pthread_t writeThreads[3], readThreads[5];
    for(int i=0; i<3; i++) 
    {
        pthread_create(&writeThreads[i],NULL, write_func, NULL);
    }

    for(int i=0; i<5; i++) 
    {
        pthread_create(&readThreads[i],NULL, read_func, NULL);
    }

    for(int i=0; i<3; i++) 
    {
        pthread_join(writeThreads[i], NULL);
    }

    for(int i=0; i<5; i++) 
    {
        pthread_join(readThreads[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    return 0;
}

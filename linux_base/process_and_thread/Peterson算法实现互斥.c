// Peterson算法满足空闲让进，忙则等待，有限的等待，但不满足让权等待

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define true 1;
#define false 0;


static int flag[2] = {0,0};
int turn = 0;


void *func_1(void *arg)
{
    while(1)
    {
        flag[0] = true;
        turn = 1;
        while(flag[1] && turn==1) {};
        printf("thread 1 is running\n");
        sleep(rand()%3);
        flag[0] = false;
    }
}


void *func_2(void *arg)
{
    while(1)
    {
        flag[1] = true;
        turn = 0;
        while(flag[0] && turn==0) {};
        printf("thread 2 is running\n");
        sleep(rand()%3);
        flag[1] = false;
    }
}


int main(int argc, char const *argv[])
{
    pthread_t thread_1,thread_2;
    pthread_create(&thread_1,NULL,func_1,NULL);
    pthread_create(&thread_2,NULL,func_2,NULL);
    pthread_exit(NULL);
    return 0;
}

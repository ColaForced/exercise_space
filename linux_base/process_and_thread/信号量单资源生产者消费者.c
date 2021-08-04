// 本质是 两组前驱关系的结合

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>


struct Node
{
    int number;
    struct Node* next;
};


sem_t produceSem;
sem_t conduceSem;


struct Node*head = NULL;


void *produce(void *arg)
{
    while (1)
    {
        sem_wait(&produceSem);
        struct Node *pNew = (struct Node*)malloc(sizeof(struct Node));
        pNew->number = rand() % 1000;
        pNew->next = head;
        head = pNew;
        printf("+++producer, number = %d, tid = %ld\n", pNew->number, pthread_self());
        sem_post(&conduceSem);
        sleep(rand() % 3);
    }
    return NULL;
}


void* consume(void* arg)
{
    while(1)
    {
        sem_wait(&conduceSem);
        struct Node* pNode = head;
        printf("--consumer: number: %d, tid = %ld\n", pNode->number, pthread_self());
        head  = pNode->next;
        free(pNode);
        sem_post(&produceSem);
        sleep(rand() % 3);
    }
    return NULL;
}


int main(int argc, char const *argv[])
{
    sem_init(&produceSem, 0, 1);  // 生成者线程一共有1个信号灯
    sem_init(&conduceSem, 0, 0);  // 消费者线程一共有0个信号灯

    pthread_t produceThreads[5];
    pthread_t consumeThreads[5];
    for(int i=0; i<5; ++i)
    {
        pthread_create(&produceThreads[i], NULL, produce, NULL);
    }

    for(int i=0; i<5; ++i)
    {
        pthread_create(&consumeThreads[i], NULL, consume, NULL);
    }

    // 释放资源
    for(int i=0; i<5; ++i)
    {
        pthread_join(produceThreads[i], NULL);
    }

    for(int i=0; i<5; ++i)
    {
        pthread_join(consumeThreads[i], NULL);
    }

    sem_destroy(&produceSem);
    sem_destroy(&conduceSem);

    return 0;
}

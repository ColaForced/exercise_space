// 信号量实现  互斥操作： 信号量设置成1， 临界资源之前P操作， 临界资源之后V操作

// 信号量实现  同步关系： 前操作后 V, 后操作之前 P.

// 生产者消费者关系分析： 两对同步关系， 一对互斥关系， 三个信号量可以实现， 也可用两个信号量和一个互斥锁实现


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
pthread_mutex_t mutex;


struct Node*head = NULL;


void *produce(void *arg)
{
    while (1)
    {
        sem_wait(&produceSem);
        pthread_mutex_lock(&mutex);
        struct Node *pNew = (struct Node*)malloc(sizeof(struct Node));
        pNew->number = rand() % 1000;
        pNew->next = head;
        head = pNew;
        pthread_mutex_unlock(&mutex);
        sem_post(&conduceSem);
        printf("+++producer, number = %d, tid = %ld\n", pNew->number, pthread_self());
        sleep(rand() % 3);
    }
    return NULL;
}


void* consume(void* arg)
{
    while(1)
    {
        sem_wait(&conduceSem);
        pthread_mutex_lock(&mutex);
        struct Node* pNode = head;
        printf("--consumer: number: %d, tid = %ld\n", pNode->number, pthread_self());
        head  = pNode->next;
        free(pNode);
        pthread_mutex_unlock(&mutex);
        sem_post(&produceSem);
        sleep(rand() % 3);
    }
    return NULL;
}


int main(int argc, char const *argv[])
{
    sem_init(&produceSem, 0, 5);  // 生成者线程一共有1个信号灯
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



// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <semaphore.h>
// #include <pthread.h>


// struct Node
// {
//     int number;
//     struct Node* next;
// };


// sem_t produceSem;
// sem_t conduceSem;
// sem_t mutex;


// struct Node*head = NULL;


// void *produce(void *arg)
// {
//     while (1)
//     {
//         sem_wait(&produceSem);
//         sem_wait(&mutex);
//         struct Node *pNew = (struct Node*)malloc(sizeof(struct Node));
//         pNew->number = rand() % 1000;
//         pNew->next = head;
//         head = pNew;
//         sem_post(&mutex);
//         sem_post(&conduceSem);
//         printf("+++producer, number = %d, tid = %ld\n", pNew->number, pthread_self());
//         sleep(rand() % 3);
//     }
//     return NULL;
// }


// void* consume(void* arg)
// {
//     while(1)
//     {
//         sem_wait(&conduceSem);
//         sem_wait(&mutex);
//         struct Node* pNode = head;
//         printf("--consumer: number: %d, tid = %ld\n", pNode->number, pthread_self());
//         head  = pNode->next;
//         free(pNode);
//         sem_post(&mutex);
//         sem_post(&produceSem);
//         sleep(rand() % 3);
//     }
//     return NULL;
// }


// int main(int argc, char const *argv[])
// {
//     sem_init(&produceSem, 0, 5);  // 生成者线程一共有5个信号灯
//     sem_init(&conduceSem, 0, 0);  // 消费者线程一共有0个信号灯
//     sem_init(&mutex, 0, 1);  // 消费者线程一共有0个信号灯


//     pthread_t produceThreads[5];
//     pthread_t consumeThreads[5];
//     for(int i=0; i<5; ++i)
//     {
//         pthread_create(&produceThreads[i], NULL, produce, NULL);
//     }

//     for(int i=0; i<5; ++i)
//     {
//         pthread_create(&consumeThreads[i], NULL, consume, NULL);
//     }

//     // 释放资源
//     for(int i=0; i<5; ++i)
//     {
//         pthread_join(produceThreads[i], NULL);
//     }

//     for(int i=0; i<5; ++i)
//     {
//         pthread_join(consumeThreads[i], NULL);
//     }

//     sem_destroy(&produceSem);
//     sem_destroy(&conduceSem);

//     return 0;
// }

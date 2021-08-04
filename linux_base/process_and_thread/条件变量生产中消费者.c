#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


struct Node
{
    int number;
    struct Node* next;
};

pthread_cond_t cond;
pthread_mutex_t mutex;
struct Node* head = NULL;


void *produce(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        struct Node *pNew = (struct Node*)malloc(sizeof(struct Node));
        pNew->number = rand()%100;
        pNew->next = head;
        head = pNew;
        printf("+++produce, number = %d, tid = %ld\n", pNew->number, pthread_self());
        pthread_mutex_unlock(&mutex);

        pthread_cond_broadcast(&cond);
        sleep(rand()%3);
    }
    return NULL;
}


void *consume(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (head == NULL)
        {
            // 在阻塞线程时候，如果线程已经对互斥锁 mutex 上锁，那么会将这把锁打开，这样做是为了避免死锁
            // 当线程解除阻塞的时候，函数内部会帮助这个线程再次将这个 mutex 互斥锁锁上，继续向下访问临界区
            pthread_cond_wait(&cond, &mutex);
        }

        struct Node *pNode = head;
        printf("--consumer: number: %d, tid = %ld\n", pNode->number, pthread_self());
        head = head->next;
        free(pNode);
        pthread_mutex_unlock(&mutex);
        sleep(rand()%3);
    }
    return NULL;    
}


int main(int argc, char const *argv[])
{
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_t produceThreads[5],consumeThreads[5];

    for(int i=0; i<5; i++) 
    {
        pthread_create(&produceThreads[i],NULL, produce, NULL);
    }

    for(int i=0; i<5; i++) 
    {
        pthread_create(&consumeThreads[i],NULL, consume, NULL);
    }

    for(int i=0; i<5; i++) 
    {
        pthread_join(produceThreads[i], NULL);
    }

    for(int i=0; i<5; i++) 
    {
        pthread_join(consumeThreads[i], NULL);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}



/*
为什么在第消费者函数43行使用if 有bug:
    当任务队列为空, 所有的消费者线程都会被这个函数阻塞 pthread_cond_wait(&cond, &mutex);
    也就是阻塞在代码的第9行
	
    当生产者生产了1个节点, 调用 pthread_cond_broadcast(&cond); 唤醒了所有阻塞的线程
      - 有一个消费者线程通过 pthread_cond_wait()加锁成功, 其余没有加锁成功的线程继续阻塞
      - 加锁成功的线程向下运行, 并成功删除一个节点, 然后解锁
      - 没有加锁成功的线程解除阻塞继续抢这把锁, 另外一个子线程加锁成功
      - 但是这个线程删除链表节点的时候链表已经为空了, 后边访问这个空节点的时候就会出现段错误
    解决方案:
      - 需要循环的对链表是否为空进行判断, 需要将if 该成 while
*/


// 作者: 苏丙榅
// 链接: https://subingwen.cn/linux/thread-sync/#5-2-%E7%94%9F%E4%BA%A7%E8%80%85%E5%92%8C%E6%B6%88%E8%B4%B9%E8%80%85
// 来源: 爱编程的大丙
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
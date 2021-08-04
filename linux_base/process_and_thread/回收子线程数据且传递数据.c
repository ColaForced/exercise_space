// 通过全局变量传递 or 传主线程变量地址给子线程
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


struct Person
{
    int id;
    char name[10];
};


void *working(void *arg)
{
    printf("child thread, id:%ld\n",pthread_self());
    struct Person *p = (struct Person*)arg;
    p->id = 1;
    strcpy(p->name, "Tony");
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char const *argv[])
{
    printf("main thread:%ld\n",pthread_self());

    struct Person p;
    pthread_t tid;
    pthread_create(&tid, NULL, working, &p);
    printf("child thread created sucess, id:%ld\n",tid);
    
    pthread_join(tid, NULL);
    printf("source received from child thread>> id:%d, name:%s\n",p.id,p.name);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>



void *working(void *arg);


struct SockInfo
{
    int fd;
    pthread_t tid;
    struct sockaddr_in addr;
} infos[128];


int main(int argc, char const *argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket");
        exit(0);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10000); 
    addr.sin_addr.s_addr = INADDR_ANY; 
    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        perror("bind");
        exit(0);
    }

    ret = listen(fd, 128);
    if(ret == -1)
    {
        perror("listen");
        exit(0);
    }

    int len = sizeof(struct sockaddr);
    int max = sizeof(infos)/sizeof(infos[0]);
    for(int i=0; i<max; i++)
    {
        bzero(&infos[i], sizeof(infos[i]));
        infos[i].fd = -1;
        infos[i].tid = -1;
    }


    while (1)
    {   
        struct SockInfo* pinfo;
        for(int i=0; i<max; i++)
        {
            if(infos[i].fd == -1)
            {
                pinfo = &infos[i];
                break;
            }
            
            if(i == max-1)
            {
                sleep(1);
                i--;
            }
        }

        int connfd = accept(fd, (struct sockaddr*)&pinfo->addr, &len);
        printf("parent thread, connfd: %d\n", connfd);
        if(connfd == -1)
        {
            perror("accept");
            exit(0);
        }

        pinfo->fd = connfd;
        pthread_create(&pinfo->tid, NULL, working, pinfo);
        pthread_detach(pinfo->tid);
    }

    close(fd);

    return 0;
}


void* working(void *arg)
{
    while (1)
    {
        struct SockInfo *info = (struct SockInfo*) arg;
        char buf[1024];
        int ret = read(info->fd,buf, sizeof(buf));
        if(ret  == 0)
        {
            printf("client closed the connection...\n");
            info->fd = -1;
            break;
        }

        else if(ret == -1)
        {
            perror("read");
            info->fd = -1;
            break;
        }

        else
        {
            printf("client say: %s\n", buf);
            write(info->fd, buf, strlen(buf)+1);
        }

    }
    return NULL;
}






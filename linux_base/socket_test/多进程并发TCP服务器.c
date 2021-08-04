// 程序有bug, 一个客户端主动关闭后，服务端终端不再有输出
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


void callback(int num);
int childWork(int cfd);


int main(int argc, char const *argv[])
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1)
    {
        perror("socket");
        exit(0);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10000); 
    addr.sin_addr.s_addr = INADDR_ANY; 
    int ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        perror("bind");
        exit(0);
    }

    ret = listen(lfd, 128);
    if(ret == -1)
    {
        perror("listen");
        exit(0);
    }

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = callback;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

    while (1)
    {
        struct sockaddr_in cliaddr;
        int clilen = sizeof(cliaddr);
        int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &clilen);
        if(cfd == -1)
        {
            if(errno == EINTR) {continue;}
            else {perror("accept"); exit(0);}
        }

        char ip[24] = {0};
        printf("client IP: %s :: port: %d\n", 
                inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, sizeof(ip)),
                ntohs(cliaddr.sin_port));

        pid_t pid = fork();
        if(pid == 0)
        {
            close(lfd);
            while(1)
            {
                int ret = childWork(cfd);
                if(ret<0) {break;}
            }
            close(cfd);
            exit(0);
        }
        else if(pid>0)
        {
            close(cfd);
        }
    }

    return 0;
}


void callback(int num)
{
    while (1)
    {
        pid_t pid = waitpid(-1, NULL, WNOHANG);
        if(pid<=0)
        {
            printf("child process is runing, or it had been recycled\n");
            break;
        }
        printf("child die,pid = %d\n",pid);
    }   
}


int childWork(int cfd)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    int len = read(cfd,buf, sizeof(buf));
    if(len > 0)
    {
        printf("client say: %s\n", buf);
        write(cfd, buf, len);
    }
    else if(len  == 0)
    {
        printf("client closed the connection...\n");
    }
    else
    {
        perror("read");
    }

    return len;
}

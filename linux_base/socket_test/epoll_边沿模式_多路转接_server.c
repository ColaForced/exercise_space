#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>



int main(int argc, char const *argv[])
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1){perror("socket error"); exit(0);}

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 本地多有的ＩＰ
    
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    int ret = bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret == -1){perror("bind error"); exit(1); }
    ret = listen(lfd, 64);
    if(ret == -1){ perror("listen error");  exit(0); }

    int epfd = epoll_create(124);
    if(epfd == -1){ perror("epoll_create"); exit(0);}

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = lfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
    if(ret == -1){ perror("epoll_ctl error");  exit(0); }

    struct epoll_event evs[1024];
    int size = sizeof(evs)/sizeof(struct epoll_event);

    while (1)
    {
        int num = epoll_wait(epfd, evs, size, -1);
        {
            for(int i=0; i<num; i++)
            {
                int curfd = evs[i].data.fd;
                if(curfd == lfd)
                {
                    int cfd = accept(curfd, NULL, NULL);
                    int flag = fcntl(cfd, F_GETFL);
                    flag |= O_NONBLOCK;
                    fcntl(cfd, F_SETFL, flag);
                    ev.events = EPOLLIN|EPOLLET;
                    ev.data.fd = cfd;
                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
                    if(ret == -1){ perror("epoll_ctl-accept");  exit(0); } 
                }
                else
                {
                    char buf[1024];
                    memset(buf, 0, sizeof(buf));
                    int len = recv(curfd, buf, sizeof(buf), 0);
                    if(len == 0)
                    {
                        printf("client closed the connection\n");
                        epoll_ctl(epfd,EPOLL_CTL_DEL,curfd,NULL);
                        close(curfd);
                        break;
                    }
                    else if(len > 0)
                    {
                        printf("client szy:%s\n",buf);
                        send(curfd, buf, len, 0);
                    }
                    else
                    {
                        if(errno == EAGAIN)
                        {
                            printf("data reading done!\n");
                            break;
                        }
                        else
                        {
                            perror("recv"); 
                            exit(0);
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}

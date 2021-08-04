#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char const *argv[])
{
    int fd = socket(AF_INET,SOCK_DGRAM, 0);
    if(fd == -1){ perror("socket"); exit(0); }

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    char buf[1024];
    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999); // 接收端需要绑定9999端口
    inet_pton(AF_INET, "127.0.0.255", &cliaddr.sin_addr.s_addr);
    
    int num = 0;
    while(1)
    {
        sprintf(buf, "hello, client...%d\n", num++);
        sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&cliaddr, len);
        printf("data for brodcast: %s\n", buf);
        sleep(1);
    }

    close(fd);

    return 0;
}

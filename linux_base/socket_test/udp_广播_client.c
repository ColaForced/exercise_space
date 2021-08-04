#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char const *argv[])
{
    int fd = socket(AF_INET,SOCK_DGRAM, 0);
    if(fd == -1){ perror("socket"); exit(0); }


    struct sockaddr_in addr;
    int len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999); // 接收端需要绑定9999端口
    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1){ perror("binf"); exit(0); }

    char buf[1024];
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("message received from brodcast: %s\n", buf);
    }

    close(fd);

    return 0;
}

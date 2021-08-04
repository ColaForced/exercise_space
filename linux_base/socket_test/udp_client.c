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
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    char buf[1024];
    char ipbuf[64];
    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);

    int num = 0;
    while(1)
    {
        sprintf(buf, "hello, udp %d....\n", num++);
        sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
        memset(buf, 0, sizeof(buf));
        recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("Client say: %s\n", buf);
        sleep(1);
    }
    
    close(fd);
    return 0;
}

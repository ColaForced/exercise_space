#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char const *argv[])
{
    int fd = socket(AF_INET,SOCK_DGRAM, 0);
    if(fd == -1){ perror("socket"); exit(0); }

    struct in_addr opt;
    inet_pton(AF_INET, "127.0.1.10", &opt.s_addr);
    setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &opt, sizeof(opt));

    char buf[1024];
    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.1.10", &cliaddr.sin_addr.s_addr);

    int num = 0;
    while(1)
    {
        sprintf(buf, "hello, client...%d\n", num++);
        sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&cliaddr, len);
        printf("data to munti-brodcast: %s\n", buf);
        sleep(1);
    }

    close(fd);




    return 0;
}

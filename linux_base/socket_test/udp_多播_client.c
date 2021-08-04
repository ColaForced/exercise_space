#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>


int main(int argc, char const *argv[])
{
    int fd = socket(AF_INET,SOCK_DGRAM, 0);
    if(fd == -1){ perror("socket"); exit(0); }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);    
    addr.sin_addr.s_addr = INADDR_ANY;  
    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(fd == -1){ perror("bind"); exit(0); }

    struct ip_mreqn opt;
    inet_pton(AF_INET, "127.0.1.10", &opt.imr_multiaddr.s_addr);
    opt.imr_address.s_addr = INADDR_ANY;
    opt.imr_ifindex = if_nametoindex("ens33");
    setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &opt, sizeof(opt));

    char buf[1024];
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("message received from broadcast: %s\n", buf);
    }

    close(fd);


    return 0;
}

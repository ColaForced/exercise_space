#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    
    int rfd = open("./testfifo", O_RDONLY);
    if(rfd == -1)
    {
        perror("open");
        exit(0);
    }

    printf("以只读的方式打开成功\n");

    for(int i=0; i<100; i++)
    {
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        int len = read(rfd, buf, sizeof(buf));
        printf("独处的数据：%s\n",buf);
        if(len == 0)
        {
            printf("管道写通道肯已经关闭，我先溜了。\n");
            break;
        }
    }
    close(rfd);
    return 0;
}

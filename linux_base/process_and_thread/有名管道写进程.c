#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    int ret = mkfifo("./testfifo", 0664);
    if(ret == -1)
    {
        perror("mkfifo");
        exit(0);
    }

    printf("有名管道创建成功\n");

    int wfd = open("./testfifo", O_WRONLY);
    if(wfd == -1)
    {
        perror("open");
        exit(0);
    }

    printf("以只写的方式打开成功\n");

    for(int i=0; i<100; i++)
    {
        char buf[1024];
        sprintf(buf, "hello, 写管道...%d\n",i);
        write(wfd, buf, strlen(buf));
        sleep(1);
    }
    close(wfd);
    return 0;
}

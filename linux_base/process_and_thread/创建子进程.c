#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


int main()
{
    pid_t pid = fork();
    printf("当前进程fork的返回值为%d\n", pid);

    if (pid>0)
    {
        printf("父进程，pid=%d\n",getpid());
    }

    else if (pid==0)
    {
        printf("子进程，pid=%d,其父pid=%d\n",getpid(),getppid());
    }
    
    else
    {
        printf("创建子进程失败\n");
    }

    printf("不加判断，父子进程都会执行该语句\n");
    return 0;
}
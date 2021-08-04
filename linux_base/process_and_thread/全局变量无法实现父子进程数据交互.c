#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int number = 10;


int main(int argc, char const *argv[])
{
    printf("最初number=%d\n",number);

    pid_t pid = fork();
    printf("当前进程fork()的返回值: %d\n", pid);

    if (pid>0)
    {
        printf("我是父进程, pid = %d, number = %d\n", getpid(), ++number);
        printf("父进程的父进程(终端进程), pid = %d\n", getppid());
        sleep(1);
    }

    else if (pid == 0)
    {
        number += 10;
        printf("我是子进程, pid = %d, number = %d\n", getpid(), number);
        printf("子进程的父进程, pid = %d\n", getppid());
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 由于子进程休眠，父进程先执行完便退出了，子进程成了孤儿进程。
int main(int argc, char const *argv[])
{
    pid_t pid = fork();

    if (pid > 0)
    {
        printf("father process pid = %d\n", getpid());
    }

    else if (pid == 0)
    {
        sleep(5);
        printf("son process pid = %d, my father process pid = %d\n", getpid(), getppid());
    }
    return 0;
}

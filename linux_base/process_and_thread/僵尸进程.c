#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 子进程已经退出，父进程既不退出也不回收，造成僵尸进程。
int main(int argc, char const *argv[])
{
    pid_t pid = fork();

    if (pid > 0)
    {
       while(1)
       {
            printf("father process pid = %d\n", getpid());
            sleep(1);
       }
    }

    else if (pid == 0)
    {
        printf("son process pid = %d, my father process pid = %d\n", getpid(), getppid());
    }
    return 0;
}

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    // 实际上创建了 7 个子进程
    // for (int i=0; i<3; i++)
    // {
    //     pid_t pid = fork();
    //     printf("当前进程pid为：%d\n",getpid());
    // }


    pid_t pid;
    for (int i=0; i<3; i++)
        {
            pid = fork();
            // 不让子进程执行循环, 直接跳出
            if(pid == 0) break;
        }
    printf("当前进程pid: %d\n", getpid());
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>


void recycle(int num)
{
    printf("捕捉到的信号是：%d\n",num);
    while (1)
    {
        pid_t pid = waitpid(-1, NULL, WNOHANG);
        if(pid>0)
            printf("child died, pid = %d\n", pid);
        else if(pid==0)
            break;
        else if(pid == -1)
        {
            printf("所有子进程都回收完毕了, 拜拜...\n");
            break;
        }
    }
}


int main(int argc, char const *argv[])
{
    sigset_t myset;
    sigemptyset(&myset);
    sigaddset(&myset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &myset, NULL);

    pid_t pid;
    for(int i=0; i<20; i++)
    {
        pid = fork();
        if (pid==0) break;
    }

    if(pid == 0)
    {
        printf("我是子进程, pid = %d\n", getpid());
    }
    else if(pid>0)
    {
        printf("我是父进程, pid = %d\n", getpid());
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = recycle;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);
        sigprocmask(SIG_UNBLOCK, &myset, NULL);
        while (1)
        {
            sleep(1);
        }
    }

    
    
    return 0;
}

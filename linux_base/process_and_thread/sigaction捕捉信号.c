#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


void callback (int arg)
{
    printf("时间：%ld,当前捕捉到的信号是%d\n",time(NULL),arg);
}


int main(int argc, char const *argv[])
{
    sigset_t myset;
    sigemptyset(&myset);

    sigaddset(&myset,SIGINT);
    sigaddset(&myset,SIGQUIT);
    sigaddset(&myset,SIGKILL);

    struct sigaction act;
    act.sa_handler = callback;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
    sigaction(SIGKILL, &act, NULL);

    sigset_t old;
    sigprocmask(SIG_BLOCK, &myset, &old);

    int i = 0;
    while (1)
    {
        sigset_t curset;
        sigpending(&curset);

        for(int j = 1; j<32; j++)
        {
            int ret = sigismember(&curset, i);
            printf("%d", ret);
        }
        printf("\n");
        sleep(1);
        i++;
        if(i == 10)
        {
            sigprocmask(SIG_SETMASK, &old, NULL);
        }
    }
    return 0;
}
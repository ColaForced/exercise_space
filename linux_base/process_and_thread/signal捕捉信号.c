#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

void doing (int arg)
{
    printf("时间：%ld,当前捕捉到的信号是%d\n",time(NULL),arg);
}

int main(int argc, char const *argv[])
{
    signal(SIGALRM,doing);
    struct itimerval newact;
    newact.it_value.tv_sec = 3;
    newact.it_value.tv_usec = 0;
    newact.it_interval.tv_sec = 1;
    newact.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &newact, NULL);

    while (1)
    {
        sleep(1000000);
    }
    

    return 0;
}

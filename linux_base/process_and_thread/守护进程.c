#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>


void writeFile(int num)
{
    time_t seconds = time(NULL);
    struct tm *loc = localtime(&seconds);
    char *curtime = asctime(loc);
    int fd = open("./time.log",O_WRONLY|O_CREAT|O_APPEND,0664);
    write(fd, curtime, strlen(curtime));
    close(fd);
}


int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if(pid>0) exit(0);

    setsid();
    chdir("/home/peng");
    umask(022);

    int fd = open("/dev/null",O_RDWR);
    dup2(fd,STDIN_FILENO);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = writeFile;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM,&act,NULL);

    struct itimerval val;
    val.it_value.tv_sec = 2;
    val.it_value.tv_usec = 0;
    val.it_interval.tv_sec = 2;
    val.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &val, NULL);

    while(1) sleep(100);
    return 0;
}

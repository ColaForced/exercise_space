#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        sleep(1);
        #if 0
            
        #else
                execlp("ps", "title", "aux", NULL);
        #endif
            
                perror("execl");
    }

    else if(pid > 0)

    {
        printf("我是父进程.....\n");
    }

    return 0;
}


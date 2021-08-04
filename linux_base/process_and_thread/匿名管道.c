#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd[2];
    int ret = pipe(fd);

    if (ret == -1)
    {
        perror("pipe");
        exit(0);
    }

    pid_t pid = fork();

    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps","ps","aux", NULL);
        perror("execlp");
    }

    else if (pid>0)
    {
        close(fd[1]);
        char buf[4096];
        while (1)
        {
            memset(buf, 0, sizeof(buf));
            int len = read(fd[0], buf, sizeof(buf));
            if (len == 0) break;
            printf("--------------------------\n");
            printf("%s, len = %d\n", buf, len);
        }
        close(fd[0]);
        wait(NULL);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// int main()
// {
//     pid_t pid;

//     for (int i=0; i<5; i++)
//     {
//         pid = fork();
//         if (pid == 0) break;
//     }

//     if(pid >0)
//     {
//         while(1)
//         {
//             pid_t ret = wait(NULL);
//             if (ret > 0)
//             {
//                 printf("成功回收了子进程资源, 子进程PID: %d\n", ret);
//             }
//             else
//             {
//                 printf("回收失败, 或者是已经没有子进程了...\n");
//                 break;
//             }
//             printf("我是父进程, pid=%d\n", getpid());
//         }
//     }

//     else if (pid == 0)
//     {
//         printf("我是子进程, pid=%d, 父进程ID: %d\n", getpid(), getppid());
//     }
    
//     return 0;
// }



// int main()
// {
//     pid_t pid;
//     // 创建子进程
//     for(int i=0; i<5; ++i)
//     {
//         pid = fork();
//         if(pid == 0)
//         {
//             break;
//         }
//     }

//     if (pid>0)
//     {
//         while(1)
//         {
//             int status;
//             pid_t ret = waitpid(-1, &status, 0);

//             if (ret>0)
//             {
//                 printf("成功回收了子进程资源, 子进程PID: %d\n", ret);
//                 if(WIFEXITED(status))
//                 {
//                     printf("子进程退出时候的状态码: %d\n", WEXITSTATUS(status));
//                 }
//                 if(WIFSIGNALED(status))
//                 {
//                     printf("子进程是被这个信号杀死的: %d\n", WTERMSIG(status));
//                 }
//             }

//             else
//             {
//                 printf("回收失败, 或者是已经没有子进程了...\n");
//                 break;
//             }

//         }
  


//     }
//     else if(pid == 0)
//     {
//         printf("===我是子进程, pid=%d, 父进程ID: %d\n", getpid(), getppid());
//     }
    
//     return 0;
// }



int main()
{
    pid_t pid;
    for(int i=0; i<5; ++i)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }

    if(pid > 0)
    {
        // 需要保证父进程一直在运行
        while(1)
        {
            // 回收子进程的资源
            // 子进程由多个, 需要循环回收子进程资源
            // 子进程退出了就回收, 
            // 没退出就不回收, 返回0
            int status;
            pid_t ret = waitpid(-1, &status, WNOHANG);  // 非阻塞
            if(ret > 0)
            {
                printf("成功回收了子进程资源, 子进程PID: %d\n", ret);
                // 判断进程是不是正常退出
                if(WIFEXITED(status))
                {
                    printf("子进程退出时候的状态码: %d\n", WEXITSTATUS(status));
                }
                if(WIFSIGNALED(status))
                {
                    printf("子进程是被这个信号杀死的: %d\n", WTERMSIG(status));
                }
            }
            else if(ret == 0)
            {
                printf("子进程还没有退出, 不做任何处理...\n");
            }
            else
            {
                printf("回收失败, 或者是已经没有子进程了...\n");
                break;
            }
            printf("我是父进程, pid=%d\n", getpid());
        }
    }
    else if(pid == 0)
    {
        printf("===我是子进程, pid=%d, 父进程ID: %d\n", getpid(), getppid());
    }
    return 0;
}



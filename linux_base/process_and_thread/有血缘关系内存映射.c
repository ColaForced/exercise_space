// !!!!!!!!! mmap: Bad file descriptor

#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


// int main(int argc, char const *argv[])
// {
//     int fd = open("./english.txt", O_RDWR);
//     void* ptr = mmap(NULL, 4000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);


//     if (ptr == MAP_FAILED)
//     {
//         perror("mmap");
//         exit(0);
//     }

//     pid_t pid = fork();
//     if (pid>0)
//     {
//         const char *pt = "I am father process, how about you?";
//         memcpy(ptr, pt, strlen(pt)+1);
//     }
//     else if (pid == 0)
//     {
//         usleep(1);
//         printf("从映射区读出的数据：%s\n", (char*) ptr);
//     }

//     munmap(ptr, 4000);
//     return 0;
// }



int main()
{
    // 1. 打开一个磁盘文件
    int fd = open("./english.txt", O_RDWR);
    // 2. 创建内存映射区
    void* ptr = mmap(NULL, 4000, PROT_READ|PROT_WRITE,
                     MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }

    // 3. 创建子进程
    pid_t pid = fork();
    if(pid > 0)
    {
        // 父进程, 写数据
        const char* pt = "我是你爹, 你是我儿子吗???";
        memcpy(ptr, pt, strlen(pt)+1);
    }
    else if(pid == 0)
    {
        // 子进程, 读数据
        usleep(1);	// 内存映射区不阻塞, 为了让子进程读出数据
        printf("从映射区读出的数据: %s\n", (char*)ptr);
    }

    // 释放内存映射区
    munmap(ptr, 4000);

    return 0;
}


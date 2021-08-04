#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    int fd = open("./test", O_RDWR);
    void* ptr = mmap(NULL, 4000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }

    const char* pt = "I am father process, how about you";
    memcpy(ptr,pt, strlen(pt) + 1);
    munmap(ptr,4000);

    return 0;
}

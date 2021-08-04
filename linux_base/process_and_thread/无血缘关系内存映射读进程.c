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

    printf("从映射区读出的数据: %s\n", (char*)ptr);

    munmap(ptr,4000);

    return 0;
}

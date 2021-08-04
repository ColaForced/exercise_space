#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// 1. 第一个参数 addr 指定为 NULL 即可
// 2. 第二个参数 length 必须要 > 0
// 3. 第三个参数 prot，进程间通信需要对内存映射区有读写权限，因此需要指定为：PROT_READ | PROT_WRITE
// 4. 第四个参数 flags，如果要进行进程间通信, 需要指定 MAP_SHARED
// 5. 第五个参数 fd，打开的文件必须大于0，进程间通信需要文件操作权限和映射区操作权限相同
//      - 内存映射区创建成功之后, 关闭这个文件描述符不会影响进程间通信
// 6. 第六个参数 offset，不偏移指定为0，如果偏移必须是4k的整数倍


// 作者: 苏丙榅
// 链接: https://subingwen.cn/linux/mmap/#1-%E5%88%9B%E5%BB%BA%E5%86%85%E5%AD%98%E6%98%A0%E5%B0%84%E5%8C%BA
// 来源: 爱编程的大丙
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main(int argc, char const *argv[])
{
    int fd1 = open("./english.txt", O_RDWR);
    int size = lseek(fd1, 0, SEEK_END);

    void* ptrA = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd1, 0);
    if(ptrA == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }

    int fd2 = open("./copy_test.txt", O_RDWR|O_CREAT, 0664);

    ftruncate(fd2, size);

    void* ptrB = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd2, 0);
    if(ptrB == MAP_FAILED)
    {
        perror("mmap----");
        exit(0);
    }

    memcpy(ptrB, ptrA, size);

    munmap(ptrA, size);
    munmap(ptrB, size);
    close(fd1);
    close(fd2);


    return 0;
}

#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int shmid = shmget(1000, 0, 0);
    if (shmid == -1)
    {
        perror("shmget error");
        return -1;
    }

    void *ptr = shmat(shmid, NULL, 0);
    if (ptr == (void*) -1)
    {
        perror("shmat error");
        return -1;
    }

    printf("共享内存数据: %s\n", (char*)ptr);
    
    printf("共享内存数据: %s\n", (char*)ptr);

    // 阻塞程序
    printf("按任意键继续, 删除共享内存\n");
    getchar();

    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
    printf("deleted shared memory");

    return 0;
}

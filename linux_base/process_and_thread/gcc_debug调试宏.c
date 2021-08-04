// gcc gcc_debug调试宏.c -D DEBUG


#include <stdio.h>

int main(int argc, char const *argv[])
{
    #ifdef DEBUG
    printf("!!! DEGUG model!!!\n");
    #endif
    return 0;
}

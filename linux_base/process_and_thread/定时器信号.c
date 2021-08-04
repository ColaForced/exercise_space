#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    alarm(1);
    for(int i=0;;i++)
    {
        printf("%d\n", i);
    }
    return 0;
}

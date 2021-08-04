//  将源文件 add.c, div.c, mult.c, sub.c 进行汇编，得到二进制目标文件 add.o, div.o, mult.o, sub.o
//  gcc *.c -c -I ./include/

// rm main.o 移除不相干

// 将生成的目标文件通过 ar 工具打包生成静态库
// ar rcs libcalc.a *.o

// gcc main.c -o main.o -L ./ -l calc -I "./include/"
// -L: 指定库所在的目录(相对或者绝对路径)
// -l: 指定库的名字, 掐头(lib)去尾(.a) ==> calc


#include "head.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
    double a = 1, b = 2;
    printf("%f + %f = %f\n", a, b, add(a,b));
    printf("%f - %f = %f\n", a, b, sub(a,b));
    printf("%f * %f = %f\n", a, b, mult(a,b));
    printf("%f / %f = %f\n", a, b, div(a,b));
    return 0;
}



// 将.c汇编得到.o, 需要额外的参数 -fpic/-fPIC
// gcc *.c -c -fpic -I ./include/

// rm main.o

// 将得到 .o 打包成动态库, 使用gcc , 参数 -shared
// gcc -shared add.o div.o mult.o sub.o -o libcalc.so  

// 编译测试程序
// gcc main.c -o app -L ./ -l calc -I ./include/
// ./app: error while loading shared libraries: libcalc.so: cannot open shared object file: No such file or directory
// gcc 通过指定的动态库信息生成了可执行程序，但是可执行程序运行却提示无法加载到动态库。
// 在 gcc 命令中虽然指定了库路径 (使用参数 -L ), 但是这个路径并没有记录到可执行程序中，只是检查了这个路径下的库文件是否存在。
// 同样对应的动态库文件也没有被打包到可执行程序中，只是在可执行程序中记录了库的名字



// 创建软链接
// sudo ln -s /home/peng/code_space/cpp_space/linux_base/dynamic_lib_test/libcalc.so /usr/lib/libcalc.so

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



线程池CPP版本：
1. 把任务队列用标准库<queue>来维护。
   -    由于queue动态可扩容，没有容量限制，可以去掉一个条件变量。
   -    queue自带入队出队操作，简化worker、manager队列操纵
2. 线程池封装成类
   

编译：   g++ test_pool.cpp -lpthread -std=c++11

    
    


#include <iostream>
#include<cstdio>
#include<unistd.h>
#include<thread>
#include<mutex>//pthread锁  的封装
#include<condition_variable>//pthread 条件变量的封装
#include<atomic>

//class T{
//public:
//    T(const T& ) = delete;
//    T& operator(const T& ) = delete;
//}

//int g_count = 0;
std::atomic_int g_count(0);//

//void ThreadEntry(int x, int y, std::mutex* lock){
//    while(1){
//        //lock->lock();
//        std::lock_guard<std::mutex> guard(*lock);
//       // if(condition){
//       //     break;
//       //     continue;
//       // }
//        printf("In ThreadEntry %d, %d\n", x, y);
//        //lock->unlock();
//        sleep(1);
//    }
//}

void ThreadEntry(){
    for(int i = 0; i < 50000; ++i){
        ++g_count;
    }
}

int main()
{
    int a = 10;
    int b = 20;
    std::mutex lock;
    //std::thread t1(ThreadEntry, a, b, &lock);//可变参数模板函数 C++11的特性  参数必须是可移动的....
    std::thread t1(ThreadEntry);
    std::thread t2(ThreadEntry);
    //t1.detach();
    t1.join();
    t2.join();
    //printf("g_count = %d\n", g_count);
    std::cout<< "g_count"<<g_count<<std::endl;
    return 0;
}

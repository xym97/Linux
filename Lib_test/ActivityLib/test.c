#include"test.h"
#include<stdio.h>
#include<dlfcn.h>

void (*fun)();

int main()
{
    void* handle = dlopen("./libmytest.so",RTLD_LAZY);
    const char* err = dlerror();
    if(NULL != err){
        perror("dlopen");
    }
    fun = dlsym(handle,"Print1");
    fun();
    fun = dlsym(handle,"Print2");
    fun();
    return 0;
}

//int main()
//{
//    Print1();
//    Print2();
//    return 0;
//}


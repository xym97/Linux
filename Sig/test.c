#include<unistd.h>
#include<stdio.h>
#include<signal.h>

void myhandel(int sig){
    printf("hahahhah  %d\n", sig);
}

int Test1()
{
    int a = 1;
    int b = 0;
    int c = 0;
    return a / b;
}

int Test2()
{
    int* ptr = 0;
    *ptr = 100;
    return *ptr;
}

int main()
{
    //typedef void (*sighandler_t)(int);
    // int i = 0;
    // signal(SIGINT, myhandel);
    // while(1){
    //     sleep(1);
    // };
    Test1();
    return 0;
}

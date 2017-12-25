#include <stdio.h>
#include<unistd.h>
#include<signal.h>

size_t g_count = 0;

void MyHandler(int sig){
    printf("count = %d \n", g_count);
    return;
}

int main()
{
    signal(SIGALRM, MyHandler);
    alarm(1);
    while(1){
        ++g_count;
       //printf("count = %d \n", g_count);//每次调用了print("\n");  就访问了一次IO设备
    }
    return 0;
}

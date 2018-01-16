#include <stdio.h>
#include <signal.h>

volatile int g_value = 0;

void MyHandler(int sig)
{
    g_value = 1;
    printf("g_value = %d\n", g_value);
}

int main()
{
    signal(SIGINT, MyHandler);
    while(g_value == 0){
        ;
    }
    printf("process done\n");
    return 0;
}

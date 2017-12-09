#include <stdio.h>
#include<unistd.h>


int g_val = 100;

int main()
{
    int ret = fork();
    if(ret > 0){
        sleep(2);
        printf("father %d,%p, g_val=%d\n",getpid(),&g_val,g_val);
    }else if(ret == 0){
        g_val = 200;
        sleep(1);
        printf("child %d, %p,g_val=%d\n",getpid(),&g_val,g_val);
    }else{
        perror("fork");
    }

    return 0;
}

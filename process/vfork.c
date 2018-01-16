#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int g_val = 0;

int main()
{
    pid_t id = vfork();
    if(id == 0 ){
        g_val = 100;
        sleep(2);
        printf("I am Child pid:%d, ppid:%d,g_val:%d,&g_val:%p \n",\
                       getpid(),getppid(),g_val,&g_val);
        exit(1);
    }else if(id > 0){
        sleep(1);
        printf("I am Father pod:%d, ppid:%d, g_avl:%d, &g_val:%p \n",\
               getpid(), getppid(),g_val,&g_val);
    }else{
        exit(2);
    }
    return 0;
}

#include <stdio.h>
#include<signal.h>

//屏蔽 2号信号  发 2号信号   查未决信号集

void MyHandler(int sig){
    printf("my sig 2\n");
    return;
}

void PrintSignalset(sigset_t * set)
{
    int i = 1;
    for(; i <= 31; ++i){
        if(sigismember(set, i)){
            printf("1 ");
        }else{
            printf("0 ");
        }
    }
    return;
}

int main()
{
    signal(SIGINT, MyHandler);
    sigset_t new_set;
    sigset_t old_set;
    sigemptyset(&new_set);//new_set 是一个定义在栈上的数 需要被初始化 成0否则信号集初始值不确定 对系统危险
    sigaddset(&new_set, SIGINT);
    sigprocmask(SIG_BLOCK, &new_set, &old_set);
    printf("sig block done\n");
    while(1){
        sigset_t pendingset;
        sigpending(&pendingset);
        PrintSignalset(&pendingset);
        sleep(1);
        printf("hahahaha\n");
    }
    return 0;
}


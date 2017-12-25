#include<stdio.h>
#include<signal.h>
#include<stdio.h>

void MyHandler(int sig)
{
    //尽量把MyHandler写成可重入函数  因为用户不知道什么时候会有信号抵达  这时候信号处理函数必须是可重入的。
}

void MySleep(int second)
{
    //1. 使用sigaction ， 注册一个SIGALRM处理函数
    struct sigaction new_action, old_action;
    new_action.sa_handler = MyHandler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;
    sigaction(SIGALRM, &new_action, &old_action);
    //2. 调用alarm函数， N秒之后， 系统会自动发送 SIGALRM
    alarm(second);
    //调用 pause（）；
    pause();
    //恢复之前的信号处理方式
    sigaction(SIGALRM, &old_action, NULL);
    
}

int main()
{
    while(1){
        MySleep(1);
        printf("haha\n");
    }
    return 0;
}


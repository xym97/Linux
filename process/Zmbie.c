#include<stdio.h>
#include<unistd.h>

int main()
{
    int ret = fork();
    if(ret > 0){//ret = child pid
        //father 
        printf("I am father : %d\n",getpid());
        while(1){sleep(1);}
    }else if(ret == 0){// 
        //child
        printf("I am child :%d\n",getpid());
    }else if(ret < 0){//fork 失败的原因  1.内存不足   2.进程的最大数量有限制   3.操作系统正在重启
        perror("fork");//向标准输出打印失败信息
    }
    return 0;
}

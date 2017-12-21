#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<string.h>
#include<ctype.h>
 
int main(){
    while(1){
        printf("[ym@localhost process myshell]$ ");
        fflush(stdout);//刷新输出缓冲区  打印命令行解释器的头部信息
        char buf[1024];//定义一个缓冲区  用来存储从键盘输入的命令
        ssize_t s = read(0,buf,sizeof(buf)-1);
        if(s > 0){
            buf[s-1] = 0;//确保缓冲区最后的‘\0’
            //printf("%s\n", buf);
        }
        char* start = buf;
        char* _argv[32] = {NULL};
        int i = 0;//将存储命了的缓冲区中的命令参数存入_argv[]  空格填上 ‘\0’
        while(*start){
            while(*start && isspace(*start)){
                *start = 0;
                start++;
            }
            _argv[i++] = start;
            while(*start && !isspace(*start)){
                start++;
            }
        }
        _argv[i] = NULL;//_argv[] 要作为execv的参数 所以末尾必须加NULL
        pid_t id = fork();//依照shell的原理创建子进程
        if(id == 0){
            int flag = 0;
            int i = 0;
            for( ; _argv[i] != NULL; ++i ){//寻找 命令行参数中的 ‘>’ 重定向符号
                if(strcmp(">", _argv[i]) == 0){
                    flag = 1;//flag设置为1 表示有重定向符号
                    break;
                }
            }
            int copyfd;
            _argv[i] = NULL;//要作为execv的参数 _argv[i]要设置为 NULL
            if(flag){
                close(1);//关闭标准输出缓冲区
                int fd = open(_argv[i + 1], O_RDWR | O_CREAT, 0755); //此时fd为1
               //copyfd = dup2(1, fd); 
           }
           execvp(_argv[0],_argv);//被替换的程序 如果有重定向 因为PCB没有变 file结构体没有变  文件描述符没有变
           //此时原本默认的输出到文件描述符为1的文件 已经不是显示屏  而是新打开的一个文件
           //if(flag){
           //   close(1);
           //   dup2(copyfd, 1);
           //}
           exit(1);//进程退出时会对自己打开的文件描述符关闭   下一次while（1）的循环开始时 重新创建子进程 默认打开 0 1 2 stdin stdout stderror
       }else{
           pid_t ret = waitpid(id, NULL, 0);
           if(ret > 0){
              // printf("wait child success!\n");
           }
       }
   }
   return 0;
}

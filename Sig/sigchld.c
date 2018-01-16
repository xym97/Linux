#include <stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

void MyHandler(int sig)
{
    //(void )sig;
    printf("wait child!\n");
    //wait(NULL);
    while(1){
        int ret = waitpid(-1, NULL, WNOHANG);
        if(ret <= 0 ){
            break;
        }
    }
}

int main()
{
    signal(SIGCHLD, /*MyHandler*/SIGIGN);
   // int ret = fork();
   // if(ret > 0){
   //     while(1){
   //         sleep(1);
   //     }
   //     
   // }else if(ret == 0){
   //     printf("child %d\n", getpid());
   //     sleep(3);
   // }
    printf("father id :%d\n", getpid());
    int count = 0;
    for(; count < 20; ++count){
        int ret = fork();
        if(ret == 0){
            printf("father id:%d\n", getpid());
            sleep(1);
            exit(0);
            break;
        }
    }
    while(1){
        sleep(1);
    }
    return 0;
}

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int g_val = 0;

int main()
{
    pid_t id = fork();
    if(id == 0 ){
        g_val = 100;
        while(1){
            printf("I am Child pid:%d, ppid:%d,g_val:%d,&g_val:%p \n",\
               getpid(),getppid(),g_val,&g_val);
            sleep(3);
            //exit(123);
        }
        exit(1);
    }else if(id > 0){
        //sleep(2);
        printf("I am Father pod:%d, ppid:%d, g_avl:%d, &g_val:%p \n",\
               getpid(), getppid(),g_val,&g_val);
    }else{
        perror("fork");
    }
    int status = 0;
    do{
        pid_t ret = waitpid(id,&status,WNOHANG);
        if(ret == 0){
            printf("Father doing other things!\n");
            sleep(1);
        }else if(ret > 0){
            if(WIFEXITED(status)){
                printf("child running done exit code : %d \n",WEXITSTATUS(status));
            }else if(WIFSIGNALED(status)){
                printf("child is quit, but it is killed SIG : %d\n",WTERMSIG(status));
            }
            break;
        }else{
            printf("wait failed!\n");
            break;
        }
    }while(1);
   // pid_t ret = waitpid(id,&status,0);
   // if(ret > 0){
   //    printf("ret:%d, status :%d, exit code: %d, sig: %d\n",ret, status, (status >> 8)&0xff, (status)&0xff);             
   //            
   // }
   // pid_t ret = wait(&status);
   // if(ret > 0){
   //     printf(" wait success ret : %d status :%d\n", ret, status);
   // }
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
    pid_t id = fork();
    if(id == 0){
        printf("execl running \n");
        //sleep(1);
        //execl("/bin/ls","ls","-a","-l","-n",NULL);
        //execlp("ls","ls","-a","-l","-n",NULL);
        char* _argv[] = {
            "ls", "-a","-l","-n",NULL
        };
       // execl("/bin/ls","ls","-a","-i","-n",NULL);
        //execv("/bin/ls",_argv);
        //execvp("ls",_argv);
        //execlp("ls","ls","-l","-i",NULL);
        char* _env[] = {"MYENV=/FORTEST/" , NULL};
        execle("./mybin","mybin",NULL,_env);
        exit(1);
    }else{
       pid_t ret =  waitpid(id,NULL,0);
       if(ret > 0){
            printf("waitpid success\n");
       }
    }
    return 0;
}

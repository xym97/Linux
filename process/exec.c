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
        //execl("/bin/ls","ls","-a","-l","-n",NULL);
        //execlp("ls","ls","-a","-l","-n",NULL);
        char* argv[] = {
            "ls", "-a","-l","-n",NULL
        };
       // execv("/bin/ls",argv);
        execvp("ls",argv);
        exit(1);
    }else{
        wait(NULL);
    }
    return 0;
}

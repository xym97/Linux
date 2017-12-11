#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
//    pid_t id = fork();
//    if(id == 0){
//        printf("execl running \n");
//        sleep(1);
//        //execl("/bin/ls","ls","-a","-l","-n",NULL);
//        //execlp("ls","ls","-a","-l","-n",NULL);
//        char* argv[] = {
//            "ls", "-a","-l","-n",NULL
//        };
//        //execl("/bin/ls","ls","-a","-i","-n",NULL);
//        //execv("/bin/ls",argv);
//        //execvp("ls",argv);
//       // execlp("ls","ls","-l","-i",NULL);
//        char* _env[] = {"MYENV=/FORTEST/A/B/C/D/E",NULL,};    
//        execle("./mybin","mybin",NULL,_env);
//        exit(1);
//    }else{
//       pid_t ret =  waitpid(id,NULL,0);
//       if(ret > 0){
//            printf("waitpid success\n");
//       }
//    }
    while(1){
        printf("[ym@localhost process myshell]$ ");
        fflush(stdout);
        char buf[1024];
        ssize_t s = read(0,buf,sizeof(buf)-1);
        if(s > 0){
            buf[s-1] = 0;
            printf("%s\n", buf);
        }
        char* start = buf;
        char* _argv[32];
        _argv[0] = start;
        int i = 1;
        while(*start){
            if(isspace(*start)){
                *start = 0;
                start++;
                _argv[i++] = start;
            }else{
                start++;
            }
        }
        _argv[i] = NULL;
        pid_t id = fork();
        if(id == 0){
            execvp(_argv[0],_argv);
            exit(1);
        }else{
            pid_t ret = waitpid(id, NULL, 0);
            if(ret > 0){
                printf("wait child success!\n");
            }
        }
    }
    return 0;
}

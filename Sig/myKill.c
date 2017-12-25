#include <stdio.h>
#include<stdio.h>

int main(int argc, char* argv[])
{
    if(argc < 3){
        printf("usage myfill signal -number pid");
        return 1;
    }
    int signo = atoi(argv[1]);
    int pid = atoi(argv[2]);
    int ret = kill(pid, signo);
    if(ret < 0){
        perror("kill");
        return 2;
    }
    return 0;
}

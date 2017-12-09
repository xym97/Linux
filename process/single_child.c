#include <stdio.h>
#include<unistd.h>

int main()
{
    int ret = fork();
    if(ret > 0){
        //father
        printf("father %d\n",getpid());
        sleep(3);
    }else if(ret == 0){
        //child
        while(1){
            printf("child: %d. %d, \n",getpid(), getppid());
            sleep(2);
        }
    }else{
        perror("fork");
    }
    return 0;
}

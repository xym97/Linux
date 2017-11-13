#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t ret = fork();
	printf("ret = %d, pid = %d, ppid = %d",ret, getpid(), getppid());
	if(ret > 0){
		printf("I am father: %d\n ", getpid());	
	}else if(ret == 0){
		printf("I am child : %d\n",getpid());
	}else{
		printf("xyxyyx");	
	}
	return 0;
}

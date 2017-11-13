#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int _pipe[2];
	int ret = pipe(_pipe);
	if(-1 == ret){
		printf(" Create pipe error!, error code id %d",ret);
	}
	pid_t pid = fork();
	if(pid < 0){
		perror("fork");
	}else if(0 ==  pid ){
		//Child
		close(_pipe[0]);
		char* masg = NULL;
		int i = 0;
		while( i < 10){
			masg = "I am Child!";
			write(_pipe[1],masg,strlen(masg) + 1);
	        sleep(1); 
    }
     else if( 0 < pid){
        //Father
		close(_pipe[1]);
	    char masg_buf[20]; 	
        int i = 0;
		while( i < 10){
			memset(masg_buf, '\0',sizeof(masg_buf));
			read(_pipe[0],masg_buf,sizeof(masg_buf));
			printf("Child said :%s\n",masg_buf);
			++i;
        }
    }
	return 0;
}

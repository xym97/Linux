#include"comm.h"

int main()
{

	pid_t pid = fork();

    if(pid < 0){
  		perror("fork");
  		return -1;
  	}else if(pid == 0){
	//child
    size_t i = 0;
	while(i < 7){
		usleep(200000);
		printf("A");
		fflush(stdout);
		usleep(500000);
		printf("A");
		fflush(stdout);
		usleep(500000);
		i++;
	 }
	}else {
	//father
	  size_t i = 0;
	  while(i < 7){
	
	    //usleep(200000);
	    printf("B");
	    fflush(stdout);
	    usleep(500000);
	    printf("B");
	    fflush(stdout);
	    usleep(500000);
		i++;
	
	 }
	}
	int ret = waitpid(pid,NULL,0);
	if(ret > 0){
		printf("proc done");
	}
	return 0;
}

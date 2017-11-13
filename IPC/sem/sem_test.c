#include"comm.h"

int main()
{
	int semid = creatSems(1);
	initSems(semid,0,1);
	pid_t pid = fork();

	//initSems(smid,0,1);
    if(pid < 0){
  		perror("fork");
  		return -1;
  	}else if(pid == 0){
	//child
	int semid = getSems();
	size_t i = 0;
	while(i < 7){
		P(semid,0);
		usleep(200000);
		printf("A");
		fflush(stdout);
		usleep(500000);
		printf("A");
		fflush(stdout);
		usleep(500000);
    	i++;
		V(semid,0);
	 }
	}else {
	//father
	  size_t i = 0;
	  while(i < 7){
		P(semid,0);
	    //usleep(200000);
	    printf("B");
	    fflush(stdout);
	    usleep(500000);
	    printf("B");
	    fflush(stdout);
	    usleep(500000);
		i++;
		V(semid,0);

	 }
	}
	int ret = waitpid(pid,NULL,0);
	if(ret > 0){
		printf("proc done");
	}
	destorySems(semid);	
	return 0;
}

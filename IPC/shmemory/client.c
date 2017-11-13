#include"comm.h"


int main()
{
	int shmid = getShm(0);
	char* buf = NULL;
	buf = shmat(shmid, NULL, 0);
	
	int count = 0;
	while(count++  < 15){
		printf("client say :%s\n", buf);
		sleep(1);
	}
	//
	shmdt(buf);
	
	return 0;
}

#include"comm.h"

int main()
{
	int shmid = createShm(4095);
	char *buf = NULL;
	buf = (char*)shmat(shmid,NULL,0);
	
	sleep(5);
	int count = 0;
	while(count < 20){
		buf[count++] = 'a' + count;
		buf[count] = '\0';
		
		sleep(1);
	}

	shmdt(buf);
	destoryShm(shmid);

	return 0;
}

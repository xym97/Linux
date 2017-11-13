#include"comm.h"

int comShm(int size,int flag)
{
	key_t key = ftok(PATH, PROJ_ID);
	if(key < 0){
		perror("ftok");
		return -1;
	}

	int shmid = shmget(key , size, flag);
	if(shmid < 0){
		perror("shmget");
		return -2;
	}
	return shmid;
}

int createShm(int size)
{
	return comShm(size, IPC_CREAT | IPC_EXCL | 0666);
}

int getShm(int size)
{
	return comShm(size, IPC_EXCL);

}

int destoryShm(int shmid)
{
	if(shmctl(shmid, IPC_RMID, NULL) < 0){
		perror("shmctl");
		return -1;
	}
	return 0;
}


#include"comm.h"


static int comSems(int nsems,int semflag)
{
	key_t key = ftok(PATH,PROJ_ID);
	if(key < 0){
		perror("ftok");
		return -1;
	}

	int semid = semget(key, nsems,semflag);
	if( semid < 0){
		perror("semget");
		return -1;
	}
	return semid;
}

int creatSems(int nums)
{
	return comSems(nums,IPC_CREAT | IPC_EXCL | 0666);
}

int getSems()
{
	return comSems(0,IPC_CREAT);
}

int initSems(int semid, int which, int value)
{
	union semun _un;
	_un.val = value;
	int ret = semctl(semid,which,SETVAL,_un);
	if(ret < 0){
		perror("initSems");
		return -1;
	}
	return 0;
}

static int comSemOp(int semid, int which, int op)
{
	struct sembuf _buf;
	_buf.sem_op = op;
	_buf.sem_num = which;
	_buf.sem_flg = 0;
	return semop(semid,&_buf,1);
}

int P(int semid, int which)
{
	return comSemOp(semid,which,-1);
}

int V(int semid, int which)
{
	return comSemOp(semid, which, +1);
}

int destorySems(int semid)
{
	int ret = semctl(semid,0,IPC_RMID,NULL);
	if(ret < 0){
		perror("Destroy:\n");
		return -1;
	}
	return 0;
}


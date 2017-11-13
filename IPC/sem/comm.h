#ifndef _SEM_H_
#define _SEM_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<wait.h>
#include<sys/sem.h>

#define PATH "."
#define PROJ_ID 56

union semun{
	int    val;
	struct semid* buf;
	unsigned short* array;
	struct seminfo* _buf;
};

//struct sembuf{  //该结构体系统内核已定义。
//	unsigned short sem_num;
//	short sem_op;
//	short sem_flg;
//};

int creatSems(int nums);
int destorySems(int semid);
int getSem();
int initSems(int semid, int which,int value);

int P(int semid, int which);
int V(int semid,int which);


#endif


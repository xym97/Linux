#ifndef _COMM_H_
#define _COMM_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/shm.h>

#define PATH "."
#define PROJ_ID 65

int createShm(int size);
int getShm(int size);
int destoryShm(int shmid);

#endif


#ifndef _COMM_H_
#define _COMM_H

#define PATH "."
#define PROJ_ID 0X6666
#define SERVER_TYPE 1
#define CLIENT_TYPE 2

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<stdio.h>

struct msgbuf{
	long mytype;
	char mytext[1024];
};

int CreatMsgQueue();
int DestoryMagQueue(int msgid);
int GetMsgQueue();
int sendMsg(int msgid, int type , char* sendmsg);
int recvMsg(int msgid, int type, char* recvmsg);

#endif

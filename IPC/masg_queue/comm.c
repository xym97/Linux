#include"comm.h"

int ComMsgQueue(int flag)
{
	key_t key = ftok(PATH,PROJ_ID);
	if(key < 0){
		perror("ftok");
		return -1;
	}
	int msgid = msgget(key,flag|0666);
	if(msgid < 0){
		perror("msgget");
		return -2;
	}
	return msgid;
}

int CreatMsgQueue()
{
	return ComMsgQueue(IPC_CREAT|IPC_EXCL);
}

int GetMsgQueue()
{
	return ComMsgQueue(IPC_CREAT);
}

int DestoryMsgQueue(int msgid)
{
	if(msgctl(msgid,IPC_RMID,NULL) < 0){
		perror("msgctl");
		return -1;
	}
	return 0;
}

int sendMsg(int msgid, int type, char* sendmsg)
{
	struct msgbuf _mb;
	_mb.mytype = type;
	strcpy(_mb.mytext,sendmsg);
	if(msgsnd(msgid,&_mb,sizeof(_mb.mytext),0) < 0){
		perror("msgsnd");
		return -1;
	}
	return 0;
}

int recvMsg(int msgid, int type, char*recvmsg)
{
	struct msgbuf _mb;
	if(msgrcv(msgid,&_mb,sizeof(_mb.mytext),type,0) < 0){
		perror("msgrcv");
		return -1;
	}	
	strcpy(recvmsg,_mb.mytext);
	return 0;
}










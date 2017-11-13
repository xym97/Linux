#include"comm.h"

int main()
{
	int msgid = CreatMsgQueue();
	char buf[1024] = {0};
	while(11111111111)
	{
		recvMsg(msgid,CLIENT_TYPE,buf);
		printf("CLIENT SAY :%s\n",buf);	
	    //fflush(stdout);
		memset(buf,0,sizeof(buf));
		ssize_t w = read(0,buf,sizeof(buf) - 1);
		if( w > 0){
			buf[w - 1] = 0;
			sendMsg(msgid,SERVER_TYPE,buf);
			memset(buf,0,sizeof(buf));
		}
				
	}
	DestoryMsgQueue(msgid);
	return 0;
}

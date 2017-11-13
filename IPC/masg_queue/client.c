#include"comm.h"

int main()
{
	int msgid = GetMsgQueue();
	char buf[1024] = {0};
	int i = 0;
	while(1){
		ssize_t w = read(0,buf,sizeof(buf) - 1);
		if( w > 0){
			buf[w - 1] = 0;
			sendMsg(msgid,CLIENT_TYPE,buf);
			memset(buf,0,sizeof(buf));
		}
		recvMsg(msgid, SERVER_TYPE,buf);
		printf("SERVER SAY:%s\n",buf);
		memset(buf,0,sizeof(buf));	
	}
	return 0;
}

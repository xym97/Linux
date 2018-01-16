#include"comm.h"

int main()
{
	int msgid = CreatMsgQueue();
	char buf[1024] = {0};
    int count = 0;
	while(count < 7 )
	{
		int ret = recvMsg(msgid,CLIENT_TYPE,buf);
        if(ret < 0){
            printf("recv failing \n");
            return -1;
        }
		printf("CLIENT SAY :%s\n",buf);	
	    //fflush(stdout);
		memset(buf,0,sizeof(buf));
		ssize_t w = read(0,buf,sizeof(buf) - 1);
		if( w > 0){
			buf[w - 1] = 0;
			sendMsg(msgid,SERVER_TYPE,buf, w);
			memset(buf,0,sizeof(buf));
		}
        count++;
				
	}
	DestoryMsgQueue(msgid);
	return 0;
}

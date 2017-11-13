#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int fd;
	umask(0);
	if(mkfifo("./mypipe",0666 | S_IFIFO) < 0){//在读端创建一个管道文件。
		perror("mkfifo");
		return 1;
	}
	fd = open("./mypipe",O_RDONLY);//以只读阻塞方式打开该文件
   	if( fd  < 0){
		printf("open mypipe fail");
		return 2;		
	}
	char buf[1024];//定义一个输出缓冲区
	while(1){
		ssize_t ret = read(fd,buf,sizeof(buf) - 1);//从管道文件中读取输到输出缓冲区中
		if(ret > 0){
			buf[ret] = 0;
			printf("said: %s\n",buf);
		}
		else if(ret == 0){
			printf("quit");
			break;
		}
		
	}
	close(fd);
	return 0;
}


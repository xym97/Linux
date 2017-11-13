#include<stdio.h>
 #include<sys/types.h>
 #include<sys/stat.h>
 #include<unistd.h>
 #include<fcntl.h>
 #include<string.h>
 int main()
 {
  	 int fd = open("./mypipe",O_WRONLY);//在发出数据的文件中以写阻塞方式打开管道文件
	 if(fd<0)
	 {
	     printf("open file error!\n");
	     return 2;
	 }
	 char buf[1024];//定义输出缓冲区
	 while(1)
	 {
	     printf("please enter # ");
		 fflush(stdout);
		 ssize_t ret = read(0,buf,sizeof(buf)-1);//从标准输入中获取数据
		 if(ret>0)
		 {
		     buf[ret-1] = 0;
			 write(fd,buf,strlen(buf));//把输出缓冲区的数据写给管道文件
	 	 }
     }
	 close(fd);//关闭写端
    return 0;
}

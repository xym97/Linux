#include<stdio.h>
#include<string.h>
#include<sys/types.h>

#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int main()
{
   //const char* msgg = "fwrite, running!\n";
   //printf("printf running ...I\n");
   //const char* msgg1 = "write, running!\n";
   //fwrite(msgg, 1, strlen(msgg), stdout);
   //write(1,msgg1, strlen(msgg1));
   //pid_t id = fork();
   // if(id == 0 ){
   //     printf("I am child!\n");
   // }else{
   //     printf("I am father!\n");
   // }
   //close(2);
   //const char* msg = "helloworld\n";
    
   // int fd = open("./log",O_RDWR|O_CREAT,0755);
   //if(fd < 0){
   //     perror("open");
   //    return 1;
   //}
   // const char* msg = "hello world\n";
   // int count = 10;
   // while(count){
   //     write(fd,msg,strlen(msg));
   //     count--;
   // }
   // close(fd);
   // const char* _msg = "helloo \n";
   // fwrite(_msg, 1, strlen(_msg), stdout);
   //const char* msg = "hello\n";
   //write(1, msg, strlen(msg));
   //int fd = open("./log", O_RDWR);
   //close(1);
   int fd = open("./print_file",O_RDWR|O_CREAT,0755);
   int fd2 = open("./print_file",O_RDWR|O_CREAT,0777);
   printf("fd = %d\n",fd);
   printf("fd2 = %d\n", fd2);
   //printf("helloworld\n");
   //fflush(stdout);
   return 0;
}

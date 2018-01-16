#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>

int main()
{
    int ret  = mkfifo("./myfifo", 0666);
    if(ret < 0){
        perror("mkfifo");
        return 1;
    }
    int fd = open("./myfifo", O_RDWR);
    if(fd < 0){
        perror("open");
        return 2;
    }
    char buf[1024] = {0};
    while(1){
        ssize_t read_size = read(0, buf, sizeof(buf) - 1);
        if(read_size > 0){
            buf[read_size - 1] = 0;
            printf("client say : %s\n", buf);
        }
        else if(read_size == 0){
            printf("client quit!, quit now\n");
            return 4;
        }else if(read_size < 0){
            perror("read");
            return 3; 
        }
    }
    close(fd);
    return 0;
}

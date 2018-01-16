#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main()
{
    int ret = mkfifo("./myfifo", 0666);
    if(ret == 0){
        perror("mkfifo");
        return 1;
    }
    
    int fd = open("./myfifo", O_RDONLY);
    if(fd < 0){
        perror("open");
        return 2;
    }
    while(1){
        char buf[1024] = {0};
        printf("plase enter!:");
        fflush(stdout);
        ssize_t read_size = read(0, buf, sizeof(buf) - 1);
        if(read_size > 0){
            buf[read_size] = 0;
            write(fd, buf, strlen(buf));
        }
        if(read_size <= 0){
            perror("read");
            return 3;
        }
    }
    close(fd);
    return 0;
}

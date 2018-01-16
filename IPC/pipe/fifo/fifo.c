#include <stdio.h>
#include<sys/stat.h>

int main()
{
    int ret = mkfifo("./myfifo",0666);
    if(ret < 0){
        perror("mkfifo");
    }
    return 0;
}



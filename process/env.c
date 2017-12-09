#include <stdio.h>
//#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* argv[], char* env[])
{
    (void) argc;
    (void) argv;
    //for(int i = 0; env[i] != NULL; ++i){
    //    printf("%s\n",env[i]);
    //}
    printf("HOME:%s\n",getenv("HAHA"));
    return 0;
}

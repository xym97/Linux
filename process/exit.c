#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>

void Func()
{
    printf("Func Runing!\n");
    exit(1);
}

void Funcc()
{
    printf("Funcc Done\n");
}

int main()
{
    //Func();
    //atexit(Funcc);//call user self-define clean Func and than  exit process 
    //printf("Func Done!\n");
    printf("main Done!");
    _exit(0);
    //return 0;
}

#include <stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>

void MyHandler(int sig)
{
    printf("sig = %d\n", sig);
}

void* ThreadEntry(void* arg)
{
    (void*) arg;
    int* ptr = 0;
    *ptr = 1;
    while(1){
        printf("thread1 \n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    signal(SIGSEGV, MyHandler);
    pthread_t tid;
    pthread_create(&tid, NULL, ThreadEntry, NULL);
    pthread_detach(tid);
    while(1){
        printf("main thread\n");
        sleep(1);
    }
    return 0;
}

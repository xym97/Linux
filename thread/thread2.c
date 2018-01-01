#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void* ThreadEntry(void* arg)
{
    size_t * count = (size_t *)arg;
    while(1){
        ++(*count);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    size_t count = 0;
    //size_t* ptr = (size_t*)malloc(sizeof(size_t));
    pthread_create(&tid, NULL, ThreadEntry, /*(void*)ptr*/ (void* )&count);
    pthread_detach(tid);
    while(1){
        printf("g_count = %lu\n", /**ptr*/ count);
        sleep(1);
    }
    return 0;
}

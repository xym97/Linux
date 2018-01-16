#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

size_t count = 0;
pthread_mutex_t lock;

void* ThreadEntry(void* arg)
{
    (void*) arg;
    size_t i = 0; 
    for(; i < 50000; i++){
    pthread_mutex_lock(&lock);    
    pthread_mutex_lock(&lock); //当加锁后调用的层层函数中可能会不小心搞一个加锁操作 （死锁情况1）  
        ++count;
    pthread_mutex_unlock(&lock);
    }
    return NULL;
}


int main()
{
    pthread_mutex_init(&lock, NULL);//init mutex
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, ThreadEntry, NULL);
    pthread_create(&tid2, NULL, ThreadEntry, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_mutex_destroy(&lock);
    printf("count = %d\n", count);
    return 0;
}

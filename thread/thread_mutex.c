#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

size_t count = 0;
pthread_mutex_t lock;

void* ThreadEntry(void* arg)
{
    (void*) arg;
    size_t i = 0; 
    for(; i < 500000000; i++){
    pthread_mutex_lock(&lock);    
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
    printf("count = %d\n", count);
    return 0;
}

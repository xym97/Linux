#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>

size_t count = 0;
pthread_mutex_t lock;

void MyHandler(int sig)
{
    pthread_mutex_lock(&lock);
}

void* ThreadEntry(void* arg)
{
    signal(SIGINT,MyHandler);
    (void*) arg;
    size_t i = 0; 
    for(;;){
        pthread_mutex_lock(&lock);
        printf("huhuhuahahah\n");
        printf("xixixix\n");
        sleep(1);
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

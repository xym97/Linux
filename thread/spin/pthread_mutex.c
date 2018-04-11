#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<pthread.h>
#include<sys/time.h>

int num = 0;
int count = 100000;
pthread_mutex_t mulock;

long long getSystemTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000 * 1000 * tv.tv_sec + tv.tv_usec;
}

void* testmutex(void* arg){
    (void)arg;
    pthread_t thread_id = pthread_self();
    printf("this thread id %ld\n", thread_id);
    for(int i = 0 ; i < count ; ++i){
        pthread_mutex_lock(&mulock);
        num++;
        pthread_mutex_unlock(&mulock);
    }
}

int main()
{
    pthread_t tid1;
    pthread_t tid2;
    tid1 = pthread_self();
    printf("this thread is %ld\n", tid1);

    long long Start_time = getSystemTime();
    pthread_create(&tid2, NULL, testmutex, NULL);
    for(int i = 0; i < count; ++i){
        pthread_mutex_lock(&mulock);
        num++;
        pthread_mutex_unlock(&mulock);
    }
    pthread_join(tid2, NULL);
    
    long long End_time = getSystemTime();
    printf("use time is %lld, num is %d\n", End_time - Start_time, num );
    pthread_mutex_destroy(&mulock);
    return 0;
}

    


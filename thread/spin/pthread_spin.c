#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
#include<stdlib.h>
#include<errno.h>

int num = 0;
int count = 100000;
pthread_spinlock_t splock;

long long getSystemTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000* 1000 *tv.tv_sec + tv.tv_usec;
}

void* testSpin(void* arg){
    (void)arg;
    pthread_t thread_id = pthread_self();
    printf("this thread is %ld\n", thread_id);
    int i = 0;
    for(; i < count; ++i){
        pthread_spin_lock(&splock);
        num++;
        pthread_spin_unlock(&splock);
    }
}

int main()
{
    pthread_t tid1;
    pthread_t tid2;
    pthread_spin_init(&splock,PTHREAD_PROCESS_PRIVATE ); 
    tid1 = pthread_self();
    printf("this thread is %ld\n", tid1);

    long long Start_time = getSystemTime();
    
    int ret = pthread_create(&tid2, NULL, testSpin, NULL);
    if(ret != 0){
        perror("pthread_create");
        return -1;
    }
    for(int i = 0 ; i < count; ++i){
        pthread_spin_lock(&splock);
        num++;
        pthread_spin_unlock(&splock);
    }
    
    pthread_join(tid2, NULL);
    long long End_time = getSystemTime();
    printf("use time %lld, num = %d\n", End_time - Start_time , num);
    pthread_spin_destroy(&splock);

    return 0;
}










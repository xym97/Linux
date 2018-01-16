#include <stdio.h>
#include<unistd.h>
#include<pthread.h>

int g_count = 0;

pthread_rwlock_t g_lock;

void* Write(void* arg)
{
    size_t i = (size_t)arg;
    while(1){
        pthread_rwlock_wrlock(&g_lock);
        printf("[%ul] Start Write %d\n",i, g_count);
        g_count++;
        printf("[%ul] Finsh Write %d\n",i, g_count);
        usleep(87654);
        pthread_rwlock_unlock(&g_lock);
    }
    return NULL;
}

void* Read(void* arg)
{
    size_t i = (size_t) arg;
    while(1){
        pthread_rwlock_rdlock(&g_lock);
        printf("[%ul] Start Read %d\n", i, g_count);
        printf("[%ul] Finsh Read %d\n", i, g_count);
        usleep(12345);
        pthread_rwlock_unlock(&g_lock);
    }
    return NULL;
}

int main()
{
    pthread_t tid[8];
    pthread_rwlock_init(&g_lock, NULL);
    size_t i = 0; 
    for(; i < 2; ++i){
        pthread_create(&tid[i], NULL, Write, (void*)i);
    }
    for(i = 2; i < 8; ++i){
        pthread_create(&tid[i], NULL, Read, (void*)i);
    }
    for(i = 0; i < 8 ;++i){
        pthread_join(tid[i], NULL);
    }
    pthread_rwlock_destroy(&g_lock);
    return 0;
}

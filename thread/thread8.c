#include <stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <semaphore.h>

#define QueueMaxSize 1000

typedef struct Queue{
    int data[QueueMaxSize];
    size_t head;
    size_t tail;
    size_t size;
}Queue;

void Init(Queue* q){
    q->head = q->size = q->tail = 0;
}

void QueuePush(Queue* q, int value){
    if(q->size == QueueMaxSize){
        return;
    }
    q->data[q->tail++] = value;
    q->tail %= QueueMaxSize;
    q->size++;
}

void QueuePop(Queue* q, int* value)
{
    if(q->size == 0) return ;
    *value = q->data[q->head++];
    q->head &= (QueueMaxSize - 1);
    q->size--;
}

Queue g_queue;
sem_t g_lock;
sem_t g_data_num;
sem_t g_blank_num;

void* Product(void* arg)
{
    (void)arg;
    int value = 0;
    while(1){
        sem_wait(&g_blank_num);
        sem_wait(&g_lock);
        QueuePush(&g_queue, ++value);
        printf("Product %d\n", value);
        sem_post(&g_lock);
        sem_post(&g_data_num);
        usleep(543211);
    }
    return NULL;
}

void* Consume(void* arg)
{
    (void)arg;
    int value = 0;
    while(1){
        sem_wait(&g_data_num);
        sem_wait(&g_lock);
        QueuePop(&g_queue, &value);
        printf("Consume %d\n", value);
        sem_post(&g_lock);
        sem_post(&g_blank_num);
        usleep(276543);
    }
    return NULL;
}

int main()
{
    sem_init(&g_lock, 0 , 1);
    sem_init(&g_data_num, 0, 0);
    sem_init(&g_blank_num, 0 , QueueMaxSize);
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, Product, NULL);
    pthread_create(&tid2, NULL, Consume, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    sem_destroy(&g_lock);
    sem_destroy(&g_data_num);
    sem_destroy(&g_blank_num);
    return 0;
}

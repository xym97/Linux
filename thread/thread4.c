#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int64_t TimeStamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 * 1000 + tv.tv_usec;
}

//void* Thread4()
//{
//
//}
//
void Calc(int* array, size_t begin, size_t end)
{
    size_t i = begin;
    for(; i < end; ++i){
        int tmp = array[i];
        array[i] = tmp * tmp;
    }
}
//
//int main()
//{
//    const size_t size = 100000000;
//    int* array = (int*)malloc(size* sizeof(int));
//    int64_t begin = TimeStamp();
//    Calc(array, 0 , size);
//    int64_t end = TimeStamp();
//    printf("time: %ld\n", end - begin);
//    //pthread_t tid;
//    //pthread_create(&tid, NULL, Thread4, NULL);
//    //pthread_detach(tid);
//    return 0;
//}

typedef struct Context{
    int* array;
    size_t begin;
    size_t end;
}Context;

void* ThreadEntry(void* arg)
{
    Context* pcontext = (Context*)arg;
    Calc(pcontext->array, pcontext->begin, pcontext->end);
}      

int main()
{
    const int thread_size = 3;
    const size_t size = 100000000;
    int* array = (int*)malloc(size* sizeof(int));
    pthread_t tid[thread_size];
    int i = 0;
    Context context[thread_size];
    
    int64_t begin = TimeStamp();
    size_t index_base = 0;
    for(; i < thread_size; ++i){
        context[i].array = array;
        context[i].begin = index_base;
        context[i].end   = index_base + size / thread_size;
        index_base += size / thread_size;
        pthread_create(&tid[i], NULL , ThreadEntry,&context[i]);
    }
    for(i = 0; i < thread_size; ++i){
        pthread_join(tid[i], NULL);
    }
    int64_t end = TimeStamp();
    printf("time: %ld\n", end - begin);
    return 0;
}

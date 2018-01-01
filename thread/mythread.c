#include <stdio.h>
#include<pthread.h>
#include<unistd.h>

typedef struct Point{
    long int x;
    long int y;
}Point;

void* Pthread_Entry(void* arg)
{
    (void* )arg;
    printf("thread1 start\n");
    sleep(3);
    printf("thread1 finish\n");
    //while(1){
    //    printf("thread 1\n");
    //    sleep(1);
    //}
    //pthread_exit(NULL);
    //while(1){
    //    sleep(1);
    //}
    //int ret = 100;
    Point* ret = (Point*)malloc(sizeof(Point));//一般来讲不会再线程中 malloc  因为malloc了就要free  还不能在线程中free
    ret->x  = 100;
    ret->y = 200;
    return (void*)ret ;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, Pthread_Entry, NULL);
    if(ret != 0){
        printf("pthread_create failed %s\n", strerror(ret));
        return 1;
    }
    //printf("pthread_t id %ul\n", &tid);
    //printf("pthread_t id %il\n", pthread_self());//打印当前线程POSIX ID  
    //sleep(3);
    //pthread_cancel(tid);
    printf("Before wait\n");
    void* thread_ret = NULL;//输出型参数
    pthread_join(tid, &thread_ret);//读取线程返回值   释放线程 PCB空间
    Point* pt = (Point*)thread_ret;
    printf("thread ret %d  %d\n", (int)(pt->x), (int)(pt->y));
    free(pt);
    while(1){
        printf("main thread ! \n");
        sleep(1);
    }
    return 0;
}


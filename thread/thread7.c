#include <stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;



Node* CreateNode(int value)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void Push(Node* head, int value){
    Node* new_node = CreateNode(1);
    new_node->next = head->next;
    head->next = new_node;
}

void Destroy(Node* del){
    free(del);
}

void Pop(Node* head, int value){
    if(head->next == NULL) return;
    Node* del = head->next;
    head->next = head->next->next;
    Destroy(del);
}

void* Init(Node** head){
    *head = CreateNode(-1);
}


Node node;
Node* _head = &node;
Node** head = &_head;
//////////////////////////////////
pthread_cond_t g_cond;
pthread_mutex_t g_lock;

void* ThreadEntry2(void* arg)
{
    (void) arg;
    while(1){
        //Node* pNode = CreateNode(1);
        pthread_mutex_lock(&g_lock);
        Push(*head,1 );
        printf("Push 1\n" );
        pthread_cond_signal(&g_cond);
        usleep(5000);
        pthread_mutex_unlock(&g_lock);
    }
    return NULL;
}

void* ThreadEntry1(void* arg)
{
    (void)arg;
    while(1){
        pthread_mutex_lock(&g_lock);
        pthread_cond_wait(&g_cond, &g_lock);
        Pop(*head, 1);
        printf("Pop 1\n");
        usleep(5000);
        pthread_mutex_unlock(&g_lock);
    }
    return NULL;
}

int main()
{
    Init(head);
    pthread_cond_init(&g_cond, NULL);
    pthread_mutex_init(&g_lock, NULL);
    
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, ThreadEntry1, NULL);
    pthread_create(&tid2, NULL, ThreadEntry2, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_cond_destroy(&g_cond);
    pthread_mutex_destroy(&g_lock);
}

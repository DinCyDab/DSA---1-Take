#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct node{
    int data;
    struct node* next;
}*Node;

typedef struct{
    int data[MAX];
    int front;
    int rear;
}QueueAList;

typedef struct queueLList{
    Node front;
    Node rear;
}*QueueLList;

//Queue Array List
void initA(QueueAList* q);
void enqueueA(QueueAList* q, int data);
bool dequeueA(QueueAList* q);
bool isFullA(QueueAList* q);
bool isEmptyA(QueueAList* q);
void displayA(QueueAList q);

//Queue Link List

void initL(QueueLList* q);
void enqueueL(QueueLList* q, int data);
bool dequeueL(QueueLList* q);
bool isEmptyL(QueueLList* q);
void displayL(QueueLList q);
void freeQueueL(QueueLList q);

int main(){
    // Test Case 1
    // QueueAList q;
    // initA(&q);
    // enqueueA(&q, 5);
    // enqueueA(&q, 6);
    // enqueueA(&q, 7);
    // dequeueA(&q);
    // dequeueA(&q);
    // dequeueA(&q);
    // displayA(q);

    // Test Case 2
    // QueueLList q;
    // initL(&q);
    // enqueueL(&q, 5);
    // enqueueL(&q, 6);
    // enqueueL(&q, 7);
    // displayL(q);
    // freeQueueL(q);
    // free(q);
    return 0;
}

void initL(QueueLList* q){
    *q = (QueueLList)malloc(sizeof(struct queueLList));
    (*q)->front = NULL;
    (*q)->rear = NULL;
}

void enqueueL(QueueLList* q, int data){
    Node newNode = (Node)malloc(sizeof(struct node));
    if(newNode == NULL){
        printf("FULL\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if((*q)->front == NULL){
        (*q)->front = newNode;
        (*q)->rear = newNode;
        return;
    }

    (*q)->rear->next = newNode;
    (*q)->rear = newNode;
}

bool dequeueL(QueueLList* q){
    if(isEmptyL(q)){
        printf("EMPTY\n");
        return false;
    }

    Node temp = (*q)->front;
    (*q)->front = (*q)->front->next;

    if((*q)->front == NULL){
        (*q)->rear = NULL;
    }

    return true;
}

bool isEmptyL(QueueLList* q){
    return (*q)->front == NULL;
}

void displayL(QueueLList q){
    if(isEmptyL(&q)){
        printf("EMPTY\n");
        return;
    }
    Node current = q->front;
    while(current != q->rear){
        printf("[%d] --> ", current->data);
        current = current->next;
    }
    printf("[%d]", q->rear->data);
}

void freeQueueL(QueueLList q){
    Node current = q->front;
    Node next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    q->front = NULL;
    q->rear = NULL;
}

void initA(QueueAList* q){
    q->front = -1;
    q->rear = -1;
}

void enqueueA(QueueAList* q, int data){
    if(isFullA(q)){
        printf("FULL\n");
        return;
    }

    if(q->front == -1){
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = data; 
}

bool dequeueA(QueueAList* q){
    if(isEmptyA(q)){
        printf("EMPTY\n");
        return false;
    }

    q->front = (q->front + 1) % MAX;
    if(q->front > q->rear){
        initA(q);
    }

    return true;
}

bool isFullA(QueueAList* q){
    return q->front == MAX;
}

bool isEmptyA(QueueAList* q){
    return q->front == -1;
}

void displayA(QueueAList q){
    if(isEmptyA(&q)){
        printf("EMPTY\n");
        return;
    }
    int i;
    for(i = q.front; i != q.rear; i = (i + 1) % MAX){
        printf("[%d] --> ", q.data[i]);
    }
    printf("[%d]", q.data[i]);
}
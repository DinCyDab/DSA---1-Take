#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int value;
    struct node* next;
}*Node; 

typedef struct queue{
    Node head;
    Node tail;
}*Queue;

void display(Node head);
void freeQueue(Node head);
void insertSort(Queue q, int data);
Queue initializeQ();
void enqueue(Queue q, Node data);
void dequeue(Queue q);

int main(){
    srand(time(NULL));
    Queue q = initializeQ();

    int i = 0;
    for(i = 0; i < 10; i++){
        insertSort(q, rand() % 10 + 1);
    }

    display(q->head);
    freeQueue(q->head);
    free(q);
    return 0;
}

void insertSort(Queue q, int data){
    Node newNode = (Node)malloc(sizeof(struct node));
    if(newNode == NULL){
        printf("ERROR\n");
        return;
    }

    newNode->value = data;
    newNode->next = NULL;

    //Check for empty head
    if(q->head == NULL){
        q->head = newNode;
        q->tail = newNode;
        return;
    }

    //Check if the new data is bigger than the last value
    //Just put it in the back
    if(data > q->tail->value){
        q->tail->next = newNode;
        q->tail = newNode;
        return;
    }

    q->tail->next = newNode;
    q->tail = newNode;

    //If the data is lesser than the head value
    //Enqueue all of the queue to the back
    if(data < q->head->value){
        Node current = q->head;
        Node next = NULL;
        while(current != newNode){
            next = current->next;
            enqueue(q, current);
            dequeue(q);
            current = next;
        }
        return;
    }

    //If the data is in the middle of the queue
    //Enqueue all of the front data
    //It will stop if the current data is greater than the new data
    Node current = q->head;
    Node next = NULL;
    while(data > current->value){
        next = current->next;
        enqueue(q, current);
        dequeue(q);
        current = next;
    }

    //Enqueue the new data
    //Then enqueue all of the remaining data
    enqueue(q, newNode);
    while(current != newNode){
        next = current->next;
        enqueue(q, current);
        dequeue(q);
        current = next;
    }

    //The current data will stop when it finds the new node
    //Dequeue for last time so that it won't have duplicate
    dequeue(q);
}

//Simple enqueueing
void enqueue(Queue q, Node data){
    Node newNode = (Node)malloc(sizeof(struct node));
    newNode->value = data->value;
    newNode->next = NULL;
    q->tail->next = newNode;
    q->tail = newNode;
}

//Simple dequeueing
void dequeue(Queue q){
    if(q->head == NULL){
        printf("ERROR\n");
        return;
    }

    Node current = q->head;
    q->head = q->head->next;

    if(q->head == NULL){
        q->tail = NULL;
    }

    free(current);
}

Queue initializeQ(){
    Queue q = (Queue)malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void display(Node head){
    Node current = head;
    while(current != NULL){
        printf("%d --> ", current->value);
        current = current->next;
    }
    printf("NULL");
}

void freeQueue(Node head){
    Node current = head;
    Node next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}
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
void enqueue(Queue q, int data);

int main(){
    srand(time(NULL));
    Node main = NULL;
    Queue q = initializeQ();

    for(int i = 0; i < 10; i++){
        insertSort(q, rand() % 10);
    }


    display(q->head);
    freeQueue(q->head);
    free(q);
    return 0;
}

void insertSort(Queue q, int data){
    if(q->head == NULL){
        enqueue(q, data);
        return;
    }

    Node newNode = (Node)malloc(sizeof(struct node));
    Node tail_holder = q->tail;
    newNode->value = data;
    newNode->next = NULL;
    
    q->tail->next = newNode;
    q->tail = newNode;

    if(tail_holder->value < newNode->value){
        //No need to insert as the newNode value is greater than the last value
        return;
    }

    Queue temp = initializeQ();
    Node current = q->head;
    Node next = NULL;

    while(newNode->value > current->value){
        next = current->next;
        if(temp->head == NULL){
            temp->head = current;
            temp->tail = current;
        }
        else{
            // temp->tail->next = current;
            temp->tail = current;
        }
        current = next;
    }

    //Double check
    if(next == NULL){
        newNode->next = current;
        q->head = newNode;
        tail_holder->next = NULL;
        q->tail = tail_holder;
        return;
    }

    temp->tail->next = newNode;
    newNode->next = next;
    
    if(next == tail_holder){
        next->next = NULL;
        q->tail = next;
    }

    //Double Check
    tail_holder->next = NULL;


    q->tail = tail_holder;

    free(temp);
}

void enqueue(Queue q, int data){
    Node newNode = (Node)malloc(sizeof(struct node));
    newNode->value = data;
    newNode->next = NULL;
    if(q->head == NULL){
        q->head = newNode;
        q->tail = newNode;
    }
    else{
        q->tail->next = newNode;
        q->tail = newNode;
    }
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
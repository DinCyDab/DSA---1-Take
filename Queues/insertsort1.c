#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int value;
    struct node* next;
}*Node;

typedef struct queue{
    Node front;
    Node tail;
}*Queue;

void enqueue(Queue q, int value);
void insertSort(Queue q, int value);
void freeQueue(Queue q);
void printQueue(Queue q);
Queue init();

int main() {
    srand(time(NULL));
    Queue q = init();

    for (int i = 0; i < 10; i++) {
        insertSort(q, rand() % 10);
    }

    printQueue(q);
    freeQueue(q);
    free(q);
    return 0;
}

void insertSort(Queue q, int value) {
    Node newNode = (Node)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("MEMORY ALLOC FAILED");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;

    //If queue is empty, front and back point to the newNode
    if (q->front == NULL) {
        q->front = newNode;
        q->tail = newNode;
        return;
    }

    //If value is less than the front value insert first
    if (value < q->front->value) {
        newNode->next = q->front;
        q->front = newNode;
        return;
    }

    //If value is greater than or equal to the last queue value, insert last
    if (value >= q->tail->value) {
        q->tail->next = newNode;
        q->tail = newNode;
        return;
    }

    //Else traverse to the whole array and find the spot to insert the newnode
    Node current = q->front;
    Node prev = NULL;

    //While the queue has not ended and the current value of queue is less or EQUAL than the value
    //Continue traversing
    while (current != NULL && current->value <= value) {
        prev = current;
        current = current->next;
    }

    //After traversing, we have found where to insert the value
    //Using pointer prev, make the prev next points to new node
    //and make the newnode next points to the current node
    prev->next = newNode;
    newNode->next = current;
}

void enqueue(Queue q, int value) {
    Node newNode = (Node)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("MEMORY ALLOC FAILED");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;

    if (q->front == NULL) {
        q->front = newNode;
        q->tail = newNode;
        return;
    }

    q->tail->next = newNode;
    q->tail = newNode;
}

Queue init() {
    Queue q = (Queue)malloc(sizeof(struct queue));
    if (q == NULL) {
        printf("MEMORY ALLOC FAILED");
        exit(EXIT_FAILURE);
    }
    q->front = NULL;
    q->tail = NULL;
    return q;
}

void freeQueue(Queue q) {
    Node current = q->front;
    Node next = NULL;
    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    q->front = NULL;
    q->tail = NULL;
}

void printQueue(Queue q) {
    Node current = q->front;
    while(current != NULL) {
        printf("%d --> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

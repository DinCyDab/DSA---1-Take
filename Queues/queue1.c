// Problem: Queue Implementation Using Linked List
// You are required to implement a queue data structure using a linked list in C. A queue follows the First In, First Out (FIFO) principle, meaning that the first element inserted is the first one to be removed.

// Requirements:
// Define a Node Structure:

// Use a typedef struct to define a node that holds an integer data and a pointer to the next node.
// Define a Queue Structure:

// Use another typedef struct to define the queue, which contains pointers to the front and rear nodes.
// Functions to Implement:

// void enqueue(Queue* queue, int value): Adds a new value to the rear of the queue.
// int dequeue(Queue* queue): Removes and returns the front value from the queue. If the queue is empty, return an appropriate error code (like -1).
// int front(const Queue* queue): Returns the front value of the queue without removing it. If the queue is empty, return an appropriate error code.
// int isEmpty(const Queue* queue): Returns 1 if the queue is empty, 0 otherwise.
// void display(const Queue* queue): Prints all the values in the queue from front to rear.
// void freeQueue(Queue* queue): Frees all nodes in the queue and sets the queue pointers to NULL.

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} Node;

typedef struct queue {
    Node* front;
    Node* rear;
} Queue;

// Function declarations
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int front(const Queue* queue);
int isEmpty(const Queue* queue);
void display(const Queue* queue);
void freeQueue(Queue* queue);

int main() {
    Queue queue = {NULL, NULL}; // Initialize an empty queue

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    display(&queue); // Should display: 10 -> 20 -> 30 -> NULL

    printf("Dequeued: %d\n", dequeue(&queue)); // Should display: Dequeued: 10

    display(&queue); // Should display: 20 -> 30 -> NULL

    printf("Front: %d\n", front(&queue)); // Should display: Front: 20

    printf("Is Empty: %d\n", isEmpty(&queue)); // Should display: Is Empty: 0

    freeQueue(&queue); // Free the queue memory
    return 0;
}

void enqueue(Queue* queue, int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    if(queue->front == NULL){
        queue->front = newNode;
        queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

int dequeue(Queue* queue){
    if(queue->front == NULL){
        return -1;
    }
    int value_holder = queue->front->value;
    Node* current = queue->front;

    queue->front = queue->front->next;
    free(current);

    return value_holder;
}

int front(const Queue* queue){
    if(queue->front == NULL){
        return -1;
    }
    return queue->front->value;
}

int isEmpty(const Queue* queue){
    return queue->front == NULL;
}

void display(const Queue* queue){
    Node* current = queue->front;
    while(current != NULL){
        printf("%d --> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void freeQueue(Queue* queue){
    Node *current = queue->front;
    Node *next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    queue->front = NULL;
    queue->rear = NULL;
}
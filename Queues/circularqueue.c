// Problem: Circular Queue Implementation Using Array
// You are required to implement a circular queue data structure using an array in C. A circular queue follows the First In, First Out (FIFO) principle, but unlike a regular queue, it wraps around when it reaches the end of the array, making efficient use of storage.

// Requirements:
// Define a Circular Queue Structure:

// Use a typedef struct to define a circular queue that holds:
// An integer array to store queue elements.
// Two integers, front and rear, to track the front and rear positions.
// An integer to track the maximum capacity of the queue.
// An integer to track the current size of the queue.
// Functions to Implement:

// void initializeQueue(CircularQueue* queue, int capacity): Initializes the queue with the given capacity.
// void enqueue(CircularQueue* queue, int value): Adds a new value to the rear of the circular queue.
// int dequeue(CircularQueue* queue): Removes and returns the front value from the queue. If the queue is empty, return an appropriate error code (like -1).
// int front(const CircularQueue* queue): Returns the front value of the queue without removing it. If the queue is empty, return an appropriate error code.
// int isFull(const CircularQueue* queue): Returns 1 if the queue is full, 0 otherwise.
// int isEmpty(const CircularQueue* queue): Returns 1 if the queue is empty, 0 otherwise.
// void display(const CircularQueue* queue): Prints all the values in the queue from front to rear.

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 5

typedef struct circularQueue {
    int *arr;
    int front;
    int rear;
    int size;
    int capacity;
} CircularQueue;

// Function declarations
void initializeQueue(CircularQueue* queue, int capacity);
void enqueue(CircularQueue* queue, int value);
int dequeue(CircularQueue* queue);
int front(const CircularQueue* queue);
int isFull(const CircularQueue* queue);
int isEmpty(const CircularQueue* queue);
void display(const CircularQueue* queue);
void freeQueue(CircularQueue* queue);

int main() {
    CircularQueue queue;
    initializeQueue(&queue, QUEUE_CAPACITY); // Initialize a circular queue with a capacity of 5

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);
    enqueue(&queue, 50);

    display(&queue); // Should display: 10, 20, 30, 40, 50

    printf("Dequeued: %d\n", dequeue(&queue)); // Should display: Dequeued: 10

    display(&queue); // Should display: 20, 30, 40, 50

    printf("Front: %d\n", front(&queue)); // Should display: Front: 20

    enqueue(&queue, 60); // Should add 60 to the queue since it's a circular queue

    display(&queue); // Should display: 20, 30, 40, 50, 60

    printf("Is Full: %d\n", isFull(&queue)); // Should display: Is Full: 1

    freeQueue(&queue); // Free the queue memory
    return 0;
}

void initializeQueue(CircularQueue* queue, int capacity){
    queue->arr = (int*)calloc(capacity, sizeof(int));
    if(queue->arr == NULL){
        printf("ERROR, MEMORY ALLOCATION FAILED\n");
        exit(EXIT_FAILURE);
    }
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->size = 0;
}

void enqueue(CircularQueue* queue, int value){
    if(isFull(queue)){
        printf("Cannot Enqueue, Queue is FULL\n");
        return;
    }
    
    if(queue->front == -1){
        queue->front = 0;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = value;
    queue->size++;
}

int dequeue(CircularQueue* queue){
    if(isEmpty(queue)){
        printf("Cannot Dequeue, Empty Queue\n");
        return -1;
    }
    int value_holder = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    
    if(isEmpty(queue)){
        queue->front = -1;
        queue->rear = -1;
    }

    return value_holder;
}

int front(const CircularQueue* queue){
    if(isEmpty(queue)){
        printf("No Front, Empty queue");
        return -1;
    }
    return queue->arr[queue->front];
}

int isFull(const CircularQueue* queue){
    return queue->size == queue->capacity;
}

int isEmpty(const CircularQueue* queue){
    return queue->size == 0;
}

void display(const CircularQueue* queue){
    if(isEmpty(queue)){
        printf("Empty queue, no need to display\n");
        return;
    }

    for(int i = queue->front; i != queue->rear; i = (i+1) % queue->capacity){
        printf("%d --> ", queue->arr[i]);
    }
    printf("%d --> ", queue->arr[queue->rear]);
    printf("NULL\n");
}

void freeQueue(CircularQueue* queue){
    free(queue->arr);
    queue = NULL;
}
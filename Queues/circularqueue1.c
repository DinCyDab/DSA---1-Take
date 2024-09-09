// A Circular Queue is a linear data structure that follows the First In First Out (FIFO) principle but connects the end of the queue back to the front, forming a circle. It is useful in scenarios where fixed-size buffer management is needed, such as in CPU scheduling and buffering in real-time data streaming.

// Requirements:
// Define a Circular Queue Structure:

// Use a typedef struct to define a circular queue that holds:
// An array to store queue elements.
// An integer to keep track of the front index.
// An integer to keep track of the rear index.
// An integer to store the maximum capacity of the queue.
// An integer to keep the current size of the queue.
// Functions to Implement:

// CircularQueue* createQueue(int capacity): Dynamically allocates and initializes a circular queue with the given capacity.
// int isFull(const CircularQueue* queue): Returns 1 if the queue is full, 0 otherwise.
// int isEmpty(const CircularQueue* queue): Returns 1 if the queue is empty, 0 otherwise.
// void enqueue(CircularQueue* queue, int value): Adds a new value at the rear of the queue. If the queue is full, print a message and do nothing.
// int dequeue(CircularQueue* queue): Removes the front element from the queue and returns it. If the queue is empty, print a message and return -1.
// int front(const CircularQueue* queue): Returns the front element of the queue without removing it. If the queue is empty, print a message and return -1.
// int rear(const CircularQueue* queue): Returns the rear element of the queue without removing it. If the queue is empty, print a message and return -1.
// void displayQueue(const CircularQueue* queue): Prints all the elements in the queue from front to rear.
// void freeQueue(CircularQueue* queue): Frees the memory allocated for the queue.

#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 5

typedef struct{
    int* arr;
    int front;
    int rear;
    int capacity;
    int size;
}CircularQueue;

CircularQueue* createQueue(int capacity);
int isFull(const CircularQueue* queue);
int isEmpty(const CircularQueue* queue);
void enqueue(CircularQueue* queue, int value);
int dequeue(CircularQueue* queue);
int front(const CircularQueue* queue);
int rear(const CircularQueue* queue);
void displayQueue(const CircularQueue* queue);
void freeQueue(CircularQueue* queue);

int main(){
    CircularQueue* queue = createQueue(5); // Create a queue with capacity 5

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);

    displayQueue(queue); // Should display: 10, 20, 30, 40, 50

    printf("Dequeued: %d\n", dequeue(queue)); // Should display: Dequeued: 10
    printf("Front: %d\n", front(queue));      // Should display: Front: 20
    printf("Rear: %d\n", rear(queue));        // Should display: Rear: 50

    enqueue(queue, 60); // This should display a message indicating the queue is full

    displayQueue(queue); // Should display: 20, 30, 40, 50

    freeQueue(queue); // Free the queue memory
    return 0;
}

void enqueue(CircularQueue* queue, int value){
    if(isFull(queue)){
        printf("ERROR, Full Queue\n");
        return;
    }

    if(isEmpty(queue)){
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = value;
    queue->size++;
}

int dequeue(CircularQueue* queue){
    if(isEmpty(queue)){
        printf("ERROR, No queue\n");
        return -1;
    }

    int value = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    if(queue->size == 0){
        queue->front = -1;
        queue->rear = -1;
    }
    return value;
}

CircularQueue* createQueue(int capacity){
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    if(queue == NULL){
        printf("Memory Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    queue->arr = (int*)calloc(capacity, sizeof(int));
    if(queue->arr == NULL){
        printf("Memory Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

int isFull(const CircularQueue* queue){
    return queue->size == queue->capacity;
}

int isEmpty(const CircularQueue* queue){
    return queue->size == 0;
}

int front(const CircularQueue* queue){
    if(isEmpty(queue)){
        return -1;
    }
    return queue->arr[queue->front];
}

int rear(const CircularQueue* queue){
    if(isEmpty(queue)){
        return -1;
    }
    return queue->arr[queue->rear];
}

void displayQueue(const CircularQueue* queue){
    if(isEmpty(queue)){
        return;
    }
    for(int i = queue->front; i != queue->rear; i = (i + 1) % queue->capacity){
        printf("%d, ", queue->arr[i]);
    }
    printf("%d\n", queue->arr[queue->rear]);
}

void freeQueue(CircularQueue* queue){
    free(queue->arr);
    free(queue);
}
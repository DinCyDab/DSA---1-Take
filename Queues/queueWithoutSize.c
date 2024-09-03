#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct{
	int items[MAX_SIZE];
	int front;
	int back;
}queue_T;

queue_T queue;

void enqueue(int value);
void init();
void dequeue();
bool isEmpty();
bool isFull();
void printQueue();

int main(){
	init();
	enqueue(5);
	enqueue(4);
	enqueue(3);
	enqueue(5);
	enqueue(4);
	enqueue(4);
	enqueue(4);
	enqueue(4);
	enqueue(4);
	enqueue(4);
	enqueue(4);
	dequeue();
	enqueue(4);
	enqueue(4);
	printf("CURRENT FRONT: %d\n", queue.front);
	printf("CURRENT BACK: %d\n", queue.back);
	printQueue();
	return 0;
}

void init(){
	queue.front = -1;
	queue.back = -1;
}

void enqueue(int value){
	if(isFull()){
		printf("ERROR, FULL QUEUE\n");
		return;
	}
	if(queue.front == -1){
		queue.front++;
	}
	
	//Same logic Dequeue
	queue.back = (queue.back + 1) % MAX_SIZE;
	queue.items[queue.back] = value;
}

void dequeue(){
	if(isEmpty()){
		printf("ERROR, EMPTY QUEUE\n");
		return;
	}
	
	//Same Logic Enqueue
	queue.items[queue.front] = 0;
	queue.front = (queue.front + 1) % MAX_SIZE;
	
	if(queue.front > queue.back){
		queue.front = -1;
		queue.back = -1;
	}
}

bool isFull(){
	return (queue.front == (queue.back + 1) % MAX_SIZE);
}

bool isEmpty(){
	if(queue.front == -1){
		return true;
	}
	else{
		return false;
	}
}

void printQueue(){
	printf("CURRENT QUEUE:\n");
	int i;
	for(i = 0; i < MAX_SIZE/2; i++){
		printf("[%-.4d]", queue.items[i]);
		if(i < (MAX_SIZE / 2) - 1){
			printf("<--");
		}
	}
	printf("\n");
	printf("|\t\t\t\t\t^\n");
	printf("v\t\t\t\t\t|\n");
	for(i = MAX_SIZE - 1; i >= MAX_SIZE / 2; i--){
		printf("[%-.4d]", queue.items[i]);
		if(i > (MAX_SIZE / 2)){
			printf("-->");
		}
	}
	printf("\n\n");
}

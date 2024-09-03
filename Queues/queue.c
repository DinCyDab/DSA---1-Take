#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct{
	int items[MAX_SIZE];
	int front;
	int back;
	int size;
}queue_t;

queue_t queue;

void init();
void enqueue(int value);
void dequeue();
bool isFull();
bool isEmpty();
void printQueue();

int main(){
	init();
	while(1){
		system("cls");
		int choice, value;
		printf("CURRENT FRONT INDEX: %d\n", queue.front);
		printf("CURRENT BACK INDEX: %d\n", queue.back);
		printf("CURRENT SIZE: %d\n", queue.size);
		printQueue();
		printf("Enter your choice:\n");
		printf("1.)Enqueue()\n");
		printf("2.)Dequeue()\n");
		printf("3.)Exit\n");
		printf("Enter your choice:");
		scanf("%d", &choice);

		switch(choice){
		case 1:
			printf("Enter value: ");
			scanf("%d", &value);
			enqueue(value);
			break;
		case 2:
			dequeue();
			break;
		case 3:
			exit(1);
			break;
		default:
			printf("Enter a correct value");
			break;
		}
		system("pause");
	}
	return 0;
}

void init(){
	queue.front = -1;
	queue.back = -1;
	queue.size = 0;
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

void enqueue(int value){
	if(isFull()){
		printf("ERROR, FULL QUEUE\n");
		return;
	}
	if(queue.size == 0){
		queue.front++;
	}
	queue.back = (queue.back + 1) % MAX_SIZE;
	queue.items[queue.back] = value;
	queue.size++;
}

void dequeue(){
	//Check if the queue is empty, don't run the other code if true
	if(isEmpty()){
		printf("ERROR, EMPTY QUEUE\n");
		return;
	}

	//Makes the item to 0
	//Iterate the front to 1 but with % MAX_SIZE as this will act like a loop
	//Whenever the front reaches MAX_SIZE then front will go back to 0
	//e.g. (6 + 1) % 10 = 7, another one (9 + 1) % 10 = 0
	//Decrement size afterwards
	queue.items[queue.front] = 0;
	queue.front = (queue.front + 1) % MAX_SIZE;
	queue.size--;

	//Checks if the size is 0
	//If size is 0 then the back and front will reset to default
	if(queue.size == 0){
		queue.back = -1;
		queue.front = -1;
	}
}

bool isFull(){
	if(queue.size < MAX_SIZE){
		return false;
	}
	else{
		return true;
	}
}

bool isEmpty(){
	if(queue.size <= 0){
		return true;
	}
	else{
		return false;
	}
}


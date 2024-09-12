#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int value;
	struct node* next;	
}*Node;

typedef struct queue{
	Node front;
	Node rear;
}*Queue;

Queue createQueue();
void enqueue(Queue q, int value);
void printQueue(Queue q);
void freeQueue(Queue q);

int main(){
    Queue q = createQueue();
    
    enqueue(q, 5);
    enqueue(q, 6);
    enqueue(q, 1);
    enqueue(q, 7);
	printQueue(q);
	freeQueue(q);
	free(q);
    return 0;
}

void enqueue(Queue q, int value){
	Node newNode = (Node)malloc(sizeof(struct node));
	if(newNode == NULL){
		printf("MEMORY ALLOC FAILED\n");
		return;
	}
	
	newNode->value = value;
	newNode->next = NULL;
	
	//This will only run at the first time as it will only check if front is null
	if(q->front == NULL){
		q->front = newNode;
		q->rear = newNode;
		return;
	}
	
	//Insert first as the newnode value is less than the front value
	if(value < q->front->value){
		newNode->next = q->front;
		q->front = newNode;
		return;
	}
	
	//Insert last as the new node value is greater than the rear value
	if(value > q->rear->value){
		q->rear->next = newNode;
		q->rear = newNode;
		return;
	}
	
	//Node traversal logic here
}

Queue createQueue(){
	Queue q = (Queue)malloc(sizeof(struct queue));
	q->front = NULL;
	q->rear = NULL;
	return q;
}

void printQueue(Queue q){
	Node current = q->front;
	while(current != NULL){
		printf("%d --> ", current->value);
		current = current->next;
	}
	printf("NULL\n");
}

void freeQueue(Queue q){
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

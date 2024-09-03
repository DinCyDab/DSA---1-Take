#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	int value;
	struct node* next;
}*Link;

typedef struct Queue{
	Link front;
	Link back;
}*Queue;

void freeList(Link head);
void printList(Link head);
void enqueue(Link* head, int value, Queue* a);
void dequeue(Link* head, Queue* a);
int front(Link head);
int last(Link head);
bool isFull(Link head);
bool isEmpty(Link head);

int main(){
	Link queue = NULL;
	Queue a = (Queue)malloc(sizeof(struct Queue));
	a->front = queue;
	enqueue(&queue, 5, &a);
	enqueue(&queue, 10, &a);
	enqueue(&queue, 15, &a);
	dequeue(&queue, &a);
	dequeue(&queue, &a);
	dequeue(&queue, &a);
	if(a->front != NULL){
		printf("Front: %d\n", a->front->value);
	}
	if(a->back != NULL){
		printf("Last: %d\n", a->back->value);
	}
	printList(queue);
	freeList(queue);
	free(a);
	return 0;
}

int front(Link head){
	return head->value;
}

int last(Link head){
	Link current = head;
	while(current->next != NULL){
		current = current->next;
	}
	return current->value;
}

bool isEmpty(Link head){
	if(head == NULL){
		return true;
	}
	else{
		return false;
	}
}

bool isFull(Link head){
	Link dummy = (Link)malloc(sizeof(struct node));
	if(dummy == NULL){
		return true;
	}
	free(dummy);	
	return false;
}

void dequeue(Link* head, Queue* a){
	if(isEmpty(*head)){
		printf("Cannot Dequeue, Empty Queue\n");
		return;
	}
	Link current = *head;
	*head = current->next;
	(*a)->front = current->next;
	if((*a)->front == NULL){
		(*a)->back = NULL;
	}
	
	free(current);
}

void enqueue(Link* head, int value, Queue* a){
	if(isFull(*head)){
		printf("Cannot Enqueue, Full Queue\n");
		return;
	}
	Link newNode = (Link)malloc(sizeof(struct node));
	newNode->value = value;
	newNode->next = NULL;
	if(*head == NULL){
		*head = newNode;
		(*a)->front = *head;
		(*a)->back = *head;
	}
	else{
		Link trav = *head;
		while(trav->next != NULL){
			trav = trav->next;
		}
		trav->next = newNode;
		(*a)->back = newNode;
	}
	
}

void printList(Link head){
	printf("\nCurrent Queue\n");
	Link current = head;
	while(current != NULL){
		printf("%d->", current->value);
		current = current->next;
	}
	printf("NULL");
}

void freeList(Link head){
	Link current = head;
	Link next = NULL;
	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
}

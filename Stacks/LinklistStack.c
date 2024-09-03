#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	int value;
	struct node* next;
}*Link;

void freeList(Link head);
void printList(Link head);
void push(Link* head, int value);
void pop(Link* head);
bool isFull(Link head);
bool isEmpty(Link head);

int main(){
	Link stack = NULL;
	push(&stack, 1);
	push(&stack, 2);
	push(&stack, 3);
	push(&stack, 4);
	push(&stack, 5);
	push(&stack, 6);
	pop(&stack);
	pop(&stack);
	pop(&stack);
	printList(stack);
	freeList(stack);
	return 0;
}

void push(Link* head, int value){
	if(isFull(*head)){
		printf("Full Stack, Cannot Push\n");
		return;
	}
	Link newNode = (Link)malloc(sizeof(struct node));
	newNode->value = value;
	newNode->next = NULL;
	if(*head == NULL){
		*head = newNode;
	}
	else{
		Link trav = *head;
		while(trav->next != NULL){
			trav = trav->next;
		}
		trav->next = newNode;
	}
}

bool isFull(Link head){
	Link Node = (Link)malloc(sizeof(struct node));
	
	if(Node == NULL){
		return true;
	}
	else{
		return false;
	}
}

bool isEmpty(Link head){
	if(head == NULL){
		return true;
	}
	else{
		return false;
	}
}

void pop(Link* head){
	if(isEmpty(*head)){
		printf("Empty Stack, Cannot Pop\n");
		return;
	}
	Link trav = *head;
	Link prev = NULL;
	while(trav->next != NULL){
		prev = trav;
		trav = trav->next;
	}
	
	if(prev != NULL){
		prev->next = trav->next;
	}
	else{
		*head = trav->next;
	}
	free(trav);
}

void printList(Link head){
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

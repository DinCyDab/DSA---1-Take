#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 8
#define ERROR -1

typedef struct{
	int top;
	int arr_stack[MAX_SIZE];
}stack_t;

stack_t stack;

void push(int value);
void pop();
bool isFull();
bool isEmpty();
int top();
void init();
void printStack();

int main(){
	init();
	
	while(1){
		system("cls");
		int choice;
		int value;
		printf("1.)Push()\n");
		printf("2.)Pop()\n");
		printf("3.)Top()\n");
		printf("4.)Exit\n");
		printf("Enter your choice: ");
		printStack();
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				printf("Enter value: ");
				scanf("%d", &value);
				push(value);
				break;
			case 2:
				pop();
				break;
			case 3:
				value = top();
				if(value == -1){
					printf("ERROR\n");
				}
				else{
					printf("The top is %d\n", value);
				}
				break;
			case 4:
				exit(1);
			default:
				printf("Please choose a correct option\n");
				break;
		}
		system("pause");
	}
	
	
}

void push(int value){
	if(isFull()){
		printf("ERROR, FULL STACK\n");
		return;
	}
	stack.top++;
	stack.arr_stack[stack.top] = value;
}

void pop(){
	if(isEmpty()){
		printf("ERROR, EMPTY STACK\n");
		return;
	}
	stack.arr_stack[stack.top] = 0;
	stack.top--;
}

bool isFull(){
	if(stack.top < MAX_SIZE - 1){
		return false;
	}
	else{
		return true;
	}
}

void init(){
	stack.top = -1;
}

bool isEmpty(){
	if(stack.top >= 0){
		return false;
	}
	else{
		return true;
	}
}

int top(){
	if(isEmpty()){
		return ERROR;
	}
	return stack.arr_stack[stack.top];
}

void printStack(){
	printf("CURRENT STACK\n");
	int i;
	for(i = 0; i < MAX_SIZE - stack.top - 1; i++){
		printf("[___]\n");
	}
	for(i = stack.top; i >= 0; i--){
		printf("[_%d_]\n", stack.arr_stack[i]);
	}
}

// Problem: Stack Implementation Using Linked List
// You are required to implement a stack data structure using a linked list in C. A stack follows the Last In, 
// First Out (LIFO) principle, meaning that the last element inserted is the first one to be removed.

// Requirements:
// Define a Node Structure: Use a typedef struct to define a node that holds an integer data and a pointer to the next node.

// Define a Stack Structure: Use another typedef struct to define the stack, which contains a pointer to the top node.

// Functions to Implement:

// push(Stack* stack, int value): Adds a new value to the top of the stack.
// int pop(Stack* stack): Removes and returns the top value from the stack.
// If the stack is empty, return an appropriate error code (like -1).
// int peek(const Stack* stack): Returns the top value of the stack without removing it. 
// If the stack is empty, return an appropriate error code.
// int isEmpty(const Stack* stack): Returns 1 if the stack is empty, 0 otherwise.
// void display(const Stack* stack): Prints all the values in the stack from top to bottom.

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
}*Stack;

void push(Stack* stack, int value);
int pop(Stack* stack);
int peek(const Stack stack);
int isEmpty(const Stack stack);
void display(const Stack stack);
void freeStack(Stack* stack);
void initialize(Stack* stack);

int main(){
    Stack stack;
    initialize(&stack); // Assume this initializes the stack

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    display(stack); // Should display: 30 20 10

    int top = pop(&stack);
    printf("Popped: %d\n", top); // Should display: Popped: 30

    display(stack); // Should display: 20 10

    printf("Peek: %d\n", peek(stack)); // Should display: Peek: 20

    printf("Is Empty: %d\n", isEmpty(stack)); // Should display: Is Empty: 0

    freeStack(&stack);
    return 0;
}

void push(Stack* stack, int value){
    Stack newNode = (Stack)malloc(sizeof(struct node));
    if(newNode == NULL){
        printf("MEMORY ALLOCATION FAILED");
        return;
    }
    
    newNode->value = value;
    newNode->next = *stack;
    *stack = newNode;
}

int pop(Stack* stack){
    if(isEmpty(*stack)){
        return -1;
    }
    Stack dummy = *stack;
    int value_holder = (*stack)->value;

    *stack = (*stack)->next;
    
    free(dummy);
    return value_holder;
}

int peek(const Stack stack){
    if(isEmpty(stack)){
        return -1;
    }
    return stack->value;
}

int isEmpty(const Stack stack){
    return stack == NULL;
}

void display(const Stack stack){
    Stack current = stack;
    while(current != NULL){
        printf("%d --> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void freeStack(Stack* stack){
    Stack current = *stack;
    Stack next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    *stack = NULL;
}

void initialize(Stack* stack){
    *stack = NULL;
}


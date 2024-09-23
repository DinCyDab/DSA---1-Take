#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node* next;
}*Node;

typedef struct stack{
    Node top;
    int count;
}*Stack;

Stack init();
void freeStack(Stack s);
void printStack(Stack s);
bool push(Stack s, int data);
bool pop(Stack s);
bool isEmpty(Stack s);
bool insertSort(Stack s, int data);

int main(){
    Stack s = init();

    insertSort(s, 1);
    insertSort(s, 4);
    insertSort(s, 3);
    insertSort(s, 2);
    insertSort(s, 1);
    insertSort(s, 4);
    insertSort(s, 3);
    insertSort(s, 2);

    printStack(s);
    freeStack(s);
    free(s);
    return 0;
}

bool insertSort(Stack s, int data){
    if(isEmpty(s)){
        push(s, data);
        return true;
    }

    if(data < s->top->data){
        push(s, data);
        return true;
    }

    Stack temp = init();

    while(s->top != NULL && s->top->data < data){
        push(temp, s->top->data);
        pop(s);
    }

    push(s, data);

    while(temp->top != NULL){
        push(s, temp->top->data);
        pop(temp);
    }

    return true;
}

bool push(Stack s, int data){
    Node newNode = (Node)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    if(isEmpty(s)){
        s->top = newNode;
        s->count++;
        return true;
    }

    newNode->next = s->top;
    s->top = newNode;
    s->count++;
    return true;
}

bool pop(Stack s){
    if(isEmpty(s)){
        printf("Cannot Pop\n");
        return false;
    }

    Node temp = s->top;
    s->top = s->top->next;
    s->count--;
    free(temp);

    return true;
}

bool isEmpty(Stack s){
    return s->top == NULL;
}

Stack init(){
    Stack s = (Stack)malloc(sizeof(struct stack));
    s->count = 0;
    s->top = NULL;
    return s;
}

void freeStack(Stack s){
    Node current = s->top;
    Node next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    s->top = NULL;
}

void printStack(Stack s){
    Node current = s->top;
    while(current != NULL){
        printf("[%d] --> ", current->data);
        current = current->next;
    }
    printf("NULL");
}
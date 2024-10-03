#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct node{
    int data;
    struct node* next;
}*Node;

typedef struct{
    int arr[MAX];
    int top;
    int max;
}StackAList;

typedef struct stackLList{
    Node top;
}*StackLList;

// StackAList
void init(StackAList* s);
void push(StackAList* s, int data);
bool pop(StackAList* s);
bool isEmpty(StackAList* s);
bool isFull(StackAList* s);
void displayStack(StackAList s);

// StackLList
void initL(StackLList* s);
void pushL(StackLList* s, int data);
bool popL(StackLList* s);
bool isEmptyL(StackLList* s);
void displayStackL(StackLList s);
void freeStackL(StackLList s);

int main(){
    // Test Case 1
    // StackAList sA;
    // init(&sA);
    // push(&sA, 5);
    // push(&sA, 6);
    // push(&sA, 7);
    // pop(&sA);
    // displayStack(sA);

    // Test Case 2
    StackLList sL;
    initL(&sL);
    pushL(&sL, 5);
    pushL(&sL, 6);
    pushL(&sL, 7);
    popL(&sL);
    displayStackL(sL);
    freeStackL(sL);
    return 0;
}

// StackLList
void initL(StackLList* s){
    *s = (StackLList)malloc(sizeof(struct stackLList));
    (*s)->top = NULL;
}

void pushL(StackLList* s, int data){
    Node newNode = (Node)malloc(sizeof(struct node));
    if(newNode == NULL){
        printf("FULL\n");
        return;
    }
    newNode->data = data;
    newNode->next = (*s)->top;
    (*s)->top = newNode;
}

bool popL(StackLList* s){
    if(isEmptyL(s)){
        printf("EMPTY\n");
        return false;
    }

    Node temp = (*s)->top;
    (*s)->top = (*s)->top->next;
    free(temp);
    return true;
}

bool isEmptyL(StackLList* s){
    return (*s)->top == NULL;
}

void displayStackL(StackLList s){
    Node current = s->top;
    while(current != NULL){
        printf("[%d]\n", current->data);
        current = current->next;
    }
}

void freeStackL(StackLList s){
    Node current = s->top;
    Node next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    s->top = NULL;
}

// StackAList
void init(StackAList* s){
    s->max = MAX;
    s->top = -1;
}

void push(StackAList* s, int data){
    if(isFull(s)){
        printf("FULL\n");
        return;
    }

    s->top++;
    s->arr[s->top] = data;
}

bool pop(StackAList* s){
    if(isEmpty(s)){
        printf("EMPTY\n");
        return false;
    }
    
    s->top--;
    return true;
}

bool isEmpty(StackAList* s){
    return s->top == -1;
}

bool isFull(StackAList* s){
    return s->top == s->max;
}

void displayStack(StackAList s){
    for(int i = s.top; i >= 0; i--){
        printf("[%d]\n", s.arr[i]);
    }
}
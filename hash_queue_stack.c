#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CLOSE_MAX 10
#define OPEN_MAX 3

typedef struct node{
	char data[20];
	struct node *next;
} NodeType, *NodePtr;

typedef struct queue{
	NodePtr head[OPEN_MAX];
	NodePtr tail[OPEN_MAX];
} *Queue;

typedef Queue dictQueue[CLOSE_MAX];

typedef struct stack{
	NodePtr top[OPEN_MAX];
} *Stack;

typedef Stack dictStack[CLOSE_MAX];

typedef struct{
	dictStack openStack;
	dictQueue openQueue;
	int max;
	int count;
} CloseDict;

void initDictionary(CloseDict *d);

bool push(CloseDict* d, char* value);
bool pop(CloseDict *d, int stackRow, int stackTop);
bool isEmptyS(Stack s, int stackTop);
void displayS(CloseDict d);
void freeS(CloseDict *d);

bool enqueue(CloseDict *d, char* value);
bool dequeue(CloseDict *d, int queueRow, int queueFront);
bool isEmptyQ(Queue q, int queueFront);
void displayQ(CloseDict d);
void freeQ(CloseDict *d);

int hashClose(char* str);
int hashOpen(char* str);

int main(){
    CloseDict d;
    initDictionary(&d);

    // enqueue(&d, "Dino");
    // enqueue(&d, "Jacques");
    // dequeue(&d, 0, 0);
    // displayQ(d);

    enqueue(&d, "Alpha");
    enqueue(&d, "Bravo");
    dequeue(&d, 0, 0);
    dequeue(&d, 0, 0);
    displayQ(d);

    // push(&d, "Dino");
    // push(&d, "Jacques");
    // pop(&d, 0, 0);
    // displayS(d);

    freeS(&d);
    freeQ(&d);

    
    return 0;
}

bool enqueue(CloseDict *d, char* value){
    int indexClose = hashClose(value);
    int indexOpen = hashOpen(value);

    NodePtr newNode = (NodePtr)malloc(sizeof(struct node));
    strcpy(newNode->data, value);
    newNode->next = NULL;

    if(d->openQueue[indexClose]->head[indexOpen] == NULL){
        d->openQueue[indexClose]->head[indexOpen] = newNode;
        d->openQueue[indexClose]->tail[indexOpen] = newNode;
    }
    else{
        d->openQueue[indexClose]->tail[indexOpen]->next = newNode;
        d->openQueue[indexClose]->tail[indexOpen] = newNode;
    }

    return true;
}

bool dequeue(CloseDict *d, int queueRow, int queueFront){
    if(isEmptyQ(d->openQueue[queueRow], queueFront)){
        return false;
    }

    NodePtr* front = &(d->openQueue[queueRow]->head[queueFront]);
    NodePtr temp = d->openQueue[queueRow]->head[queueFront];

    *front = (*front)->next;
    free(temp);

    if(*front == NULL){
        d->openQueue[queueRow]->tail[queueFront] = NULL;
    }
    return true;
}

bool isEmptyQ(Queue q, int queueFront){
    return q->head[queueFront] == NULL;
}

void displayQ(CloseDict d){
    printf("Queue:\n");
    for(int i = 0; i < CLOSE_MAX; i++){
        printf("    [%d]\n", i);
        for(int j = 0; j < OPEN_MAX; j++){
            printf("[%d] --> ", j);
            NodePtr current = d.openQueue[i]->head[j];
            while(current != NULL){
                printf("[%s] --> ", current->data);
                current = current->next;
            }
            printf("NULL\n");
        }
        printf("\n");
    }
}

void freeQ(CloseDict *d){
    for(int i = 0; i < CLOSE_MAX; i++){
        for(int j = 0; j < OPEN_MAX; j++){
            NodePtr current = d->openQueue[i]->head[j];
            NodePtr next = NULL;
            while(current != NULL){
                next = current->next;
                free(current);
                current = next;
            }
        }
        free(d->openQueue[i]);
    }
}

bool push(CloseDict* d, char* value){
    int closeIndex = hashClose(value);
    int openIndex = hashOpen(value);

    NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));

    if(newNode == NULL){
        return false;
    }

    strcpy(newNode->data, value);
    newNode->next = d->openStack[closeIndex]->top[openIndex];
    d->openStack[closeIndex]->top[openIndex] = newNode;
    return true;
}

bool pop(CloseDict *d, int stackRow, int stackTop){
    if(isEmptyS(d->openStack[stackRow], stackTop)){
        return false;
    }

    NodePtr temp = d->openStack[stackRow]->top[stackTop];
    d->openStack[stackRow]->top[stackTop] = d->openStack[stackRow]->top[stackTop]->next;
    free(temp);
    return true;
}

bool isEmptyS(Stack s, int stackTop){
    return s->top[stackTop] == NULL;
}

void initDictionary(CloseDict *d) {
    for (int i = 0; i < CLOSE_MAX; i++) {
        d->openQueue[i] = (Queue)malloc(sizeof(struct queue));
        d->openStack[i] = (Stack)malloc(sizeof(struct stack));

        for (int j = 0; j < OPEN_MAX; j++) {
            d->openQueue[i]->head[j] = NULL;
            d->openQueue[i]->tail[j] = NULL;
            d->openStack[i]->top[j] = NULL;
        }
    }
}

void displayS(CloseDict d){
    printf("Stack\n");
    for(int i = 0; i < CLOSE_MAX; i++){
        printf("    [%d]\n", i);
        for(int j = 0; j < OPEN_MAX; j++){
            NodePtr current = d.openStack[i]->top[j];
            printf("[%d] --> ", j);
            while(current != NULL){
                printf("[%s] --> ", current->data);
                current = current->next;
            }
            printf("[NULL]\n");
        }
        printf("\n");
    }
}

void freeS(CloseDict *d){
    for(int i = 0; i < CLOSE_MAX; i++){
        for(int j = 0; j < OPEN_MAX; j++){
            NodePtr current = d->openStack[i]->top[j];
            NodePtr next = NULL;
            while(current != NULL){
                next = current->next;
                free(current);
                current = next;
            }
        }
        free(d->openStack[i]);
    }
}

int hashClose(char* str){
    int sum = 0;
    for(int i = 0; str[i] != '\0'; i++){
        sum += (int) str[i];
    }
    return sum % CLOSE_MAX;
}

int hashOpen(char* str){
    int sum = 0;
    for(int i = 0; i < 3 && str[i] != '\0'; i++){
        sum += (int) str[i];
    }
    return sum % OPEN_MAX;
}
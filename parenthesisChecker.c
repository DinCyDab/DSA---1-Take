#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 20

typedef struct stack{
    char array[MAX_SIZE];
    int count;
}*Stack;

void isBalance(Stack s, char* str);
void push(Stack s, char c);
void pop(Stack s, char c);
bool isEmpty(Stack s);
bool isFull(Stack s);

int main(){
    Stack stack = (Stack)malloc(sizeof(struct stack));
    stack->count = 0;

    char string[] = "([])[]()";

    isBalance(stack, string);

    printf(stack->count == 0? "Balance" : "Inbalance");

    free(stack);
    return 0;
}

void isBalance(Stack s, char* str){
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == '(' || str[i] == '['){
            push(s, str[i]);
        }

        if(str[i] == ')' || str[i] == ']'){
            pop(s, str[i]);
        }
    }
}

void push(Stack s, char c){
    
    s->array[s->count] = c;
    s->count++;
}

bool isEmpty(Stack s){
    return s->count == 0;
}

bool isFull(Stack s){
    return s->count == MAX_SIZE - 1;
}

void pop(Stack s, char c){
    if(isEmpty(s)){
        printf("Inbalance");
        exit(EXIT_SUCCESS);
    }

    char g;

    switch(c){
        case ')':
            g = '(';
            break;
        case ']':
            g = '[';
            break;
        default:
            printf("Inbalance");
            exit(EXIT_SUCCESS);
    }

    if(s->array[s->count - 1] != g){
        printf("Inbalance\n");
        exit(EXIT_SUCCESS);
    }

    s->count--;
}
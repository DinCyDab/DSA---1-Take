#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

typedef struct stack{
    int data[MAX];
    int count;
    int max;
    int secondMax;
}*Stack;

void push(Stack s, int data);
void pop(Stack s);
int findSecondMax(Stack s, int* arr);
bool isEmpty(Stack s);
bool isFull(Stack s);
Stack init();

int main(){
    srand(time(NULL));
    Stack s = init();
    int arr[MAX];
    
    for(int i = 0; i < MAX; i++){
        arr[i] = rand() % 10;
    }
    
    printf("%d\n", findSecondMax(s, arr));
    
    for(int i = 0; i < MAX; i++){
        printf("%d ", arr[i]);
    }
    
    return 0;
}

int findSecondMax(Stack s, int* arr){
    for(int i = 0; i < MAX; i++){
        push(s, arr[i]);
    }
    return secondMax(s);
}

int secondMax(Stack s){
    return s->secondMax;
}

void push(Stack s, int data){
    if(isFull(s)){
        return;
    }
    
    s->data[s->count] = data;
    
    // if(s->count == 0){
    //     s->max = data;
    //     s->secondMax = data;
    //     s->count++;
    //     return;
    // }
    
    if(data > s->max){
        s->secondMax = s->max;
        s->max = data;
    }
    else if(data > s->secondMax && data < s->max){
        s->secondMax = data;
    }
    
    s->count++;
}
void pop(Stack s){
    if(isEmpty(s)){
        return;
    }
    
    s->count--;
}
bool isEmpty(Stack s){
    return s->count == 0;
}
bool isFull(Stack s){
    return s->count == MAX;
}
Stack init(){
    Stack s = (Stack)malloc(sizeof(struct stack));
    s->count = 0;
    s->max = -1;
    s->secondMax = -1;
    return s;
}
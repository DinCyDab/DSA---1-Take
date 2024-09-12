#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    int array[10];
    int count;
}*Set;

void addElement(Set s, int data){
    if(isElement(s, data)){
        printf("%d is inside set\n", data);
        return;
    }
    //Logic code here for adding data
}

bool isElement(Set s, int data){
    int i;
    for(i = 0; i < s->count && s->array[i] != data; i++);
    return i != s->count;
}

int main(){

    return 0;
}


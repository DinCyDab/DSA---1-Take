#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 10

typedef struct set{
    int* array;
    int* index_holder;
    int count;
    int max;
}*Set;

Set init();
int cardinality(Set s);
void addElement(Set s, int data);
bool isElement(Set s, int data);
void printSet(Set s);
bool isSubset(Set a, Set b);

int main(){
    Set s = init();
    Set z = init();

    addElement(s, 1);
    addElement(s, 2);
    addElement(z, 2);
    addElement(z, 1);
    addElement(z, 3);
    
    
    // addElement(z, 4);
    
    printf("S: ");
    printSet(s);

    printf("Z: ");
    printSet(z);
    printf("\n");
    printf(isSubset(z, s)? "S is subset of Z" : "Z is a superset of S");

    free(s->array);
    free(s->index_holder);
    free(s);
    
    free(z->array);
    free(z->index_holder);
    free(z);

    return 0;
}

bool isSubset(Set a, Set b){
    //Early return if b has a greater size of a, making it O(1)
    if(b->count > a->count){
        return 0;
    }

    int i;
    //O(n), sad
    for(i = 0; i < b->count && isElement(a, b->array[b->index_holder[i]]) == 0; i++);

    return i == b->count;
}

Set init(){
    Set set = (Set)malloc(sizeof(struct set));
    set->array = (int*)calloc(MAX, sizeof(int));
    set->index_holder = (int*)calloc(MAX, sizeof(int));
    set->count = 0;
    set->max = MAX;
    return set;
}

int cardinality(Set s){
    return s->count;
}

void addElement(Set s, int data){
    if(isElement(s, data) == 0){
        printf("%d is inside set\n", data);
        return;
    }

    s->array[data] = data;
    s->index_holder[s->count] = data;
    s->count++;
}

bool isElement(Set s, int data){
    return data >= 0 && s->array[data] != data && data < s->max;
}

void printSet(Set s){
    for(int i = 0; i < s->count; i++){
        printf("%d --> ", s->array[s->index_holder[i]]);
    }
    printf("NULL\n");
}
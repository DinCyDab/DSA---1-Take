#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5
#define EMPTY -1
#define DELETED -2

typedef int DICTIONARY[MAX];

typedef struct node {
  DICTIONARY A;
  int count;
} SET, *SETptr;

void initDictionary(DICTIONARY main);
int hash(DICTIONARY main, int elem);
int isMember(DICTIONARY main, int find);
void insert(DICTIONARY main, int newData);
void display(DICTIONARY main);
void delete(DICTIONARY main, int delete);
DICTIONARY* insertSorted(DICTIONARY main);

int main(){
    SET set;
    set.count = 0;
    initDictionary(set.A);
    insert(set.A, 25);
    insert(set.A, 20);
    insert(set.A, 15);
    insert(set.A, 10);
    insert(set.A, 5);
    // delete(set.A, 25);
    // insert(set.A, 30);


    DICTIONARY* temp = insertSorted(set.A);
    display(*temp);

    free(temp);
    return 0;
}

DICTIONARY* insertSorted(DICTIONARY main){
    DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
    initDictionary(*d);

    for(int i = 0; i < MAX; i++){
        int temp = main[i];
        int index = i;
        for(int j = i + 1; j < MAX; j++){
            if(temp > main[j]){
                temp = main[j];
                index = j;
            }
        }

        // If the temp is not the same as the initial index
        // Swap
        if(temp != main[i]){
            int temp = main[i];
            main[i] = main[index];
            main[index] = temp;
        }

        // Idea is just like push and pop
        if(temp != EMPTY && temp != DELETED){
            insert(*d, temp);
            delete(main, temp);
        }
    }

    return d;
}

void delete(DICTIONARY main, int delete){
    int index = hash(main, delete);
    int i;
    for(i = 0; i < MAX && main[index] != delete && main[index] != EMPTY; index = (index + 1) % MAX, i++);

    if(main[index] == delete){
        main[index] = DELETED;
    }
}

int isMember(DICTIONARY main, int find){
    int index = hash(main, find);
    int i;
    for(i = 0; i < MAX && main[index] != find && main[index] != EMPTY; index = (index + 1) % MAX, i++);

    if(main[index] == find){
        return index;
    }

    return 0;
}

void display(DICTIONARY main){
    for(int i = 0; i < MAX; i++){
        printf((main[i] != EMPTY && main[i] != DELETED) ? "[%d]" : "[ ]", main[i]);
        printf((i < MAX - 1)? " --> " : "");
    }
}

void insert(DICTIONARY main, int newData){
    if(newData < 0){
        printf("ENTER POSITIVE VALUE\n");
        return;
    }
    int index = hash(main, newData);
    int i = 0;

    for(i = 0; i < MAX && main[index] != EMPTY && main[index] != newData && main[index] != DELETED; index = (index + 1) % MAX, i++);

    if((main[index] == EMPTY || main[index] == DELETED) && i < MAX && main[index] != newData){
        main[index] = newData;
    }
    else{
        printf("ERROR INSERTION\n");
    }
}

void initDictionary(DICTIONARY main){
    for(int i = 0; i < MAX; i++){
        main[i] = EMPTY;
    }
}

int hash(DICTIONARY main, int elem){
    int sum = 0;
    while(elem != 0){
        sum += (elem % 10);   
        elem /= 10;
    }
    return sum % MAX;
}
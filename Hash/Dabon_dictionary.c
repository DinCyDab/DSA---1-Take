#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct Pair{
    int unhashedKey;
    char value;
    struct Pair* next;
}*Pair;

typedef Pair Dictionary[TABLE_SIZE];

void init(Dictionary* d);
void insert(Dictionary* d, int key, char value);
bool find(Dictionary* d, int key, char value);
bool delete(Dictionary* d, int key, char value);
int getIndex(int key, char value);

//Helper Functions
void freeD(Dictionary* d);
void printD(Dictionary* d);

int main(){
    Dictionary d;
    init(&d);

    for (int i = 30; i >= 0; i--) {
        insert(&d, i, 'A' + i);
        insert(&d, i, 'A' + i);
    }
    //Before Delete
    printD(&d);

    printf(find(&d, 21, 'V')? "Found\n" : "Not Found\n");
    printf(delete(&d, 21, 'V')? "Deleted\n" : "Not Deleted\n");

    //After Delete
    printD(&d);

    freeD(&d);
    return 0;
}

//Descending
// Find the index to insert
//Insert sorted within the dictionary on a specific index
// If the element is bigger than the current front hashed key, insert first
// Else traverse and find that specific position to insert the element to be inserted
void insert(Dictionary* d, int key, char value){
    int index = getIndex(key, value);
    Pair newNode = (Pair)malloc(sizeof(struct Pair));
    if(newNode == NULL){
        printf("ERROR");
        return;
    }

    newNode->unhashedKey = key;
    newNode->value = value;
    newNode->next = NULL;

    Pair temp = (*d)[index];
    if(temp == NULL || temp->unhashedKey <= key){
        newNode->next = temp;
        (*d)[index] = newNode;
        return;
    }

    Pair prev = NULL;
    while(temp != NULL && temp->unhashedKey > key){
        prev = temp;
        temp = temp->next;
    }

    prev->next = newNode;
    newNode->next = temp;
    
}

// Finding an element inside the dictionary
// Traverses inside the hashed index
// If found return true else return false
bool find(Dictionary* d, int key, char value){
    int index = getIndex(key, value);

    Pair temp = (*d)[index];
    while(temp != NULL && temp->unhashedKey != key){
        temp = temp->next;
    }

    return temp != NULL;
}

//Deletes an element inside the diction
// Traverses inside the hashed index
// if found, free the found element and return true
// else return false
bool delete(Dictionary* d, int key, char value){
    int index = getIndex(key, value);

    Pair temp = (*d)[index];

    Pair prev = NULL;
    while(temp != NULL && temp->unhashedKey != key){
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL){
        return false;
    }

    if(prev == NULL){
        (*d)[index] = (*d)[index]->next;
    }
    else{
        prev->next = temp->next;
    }
    free(temp);

    return true;
}

// Indexing the key and value of the character
// Formula:
// sum = value + (key % 10) then key /= 10
int getIndex(int key, char value){
    int sum = (int) value;
    while(key != 0){
        sum = (key % TABLE_SIZE + 1) + sum;
        key /= TABLE_SIZE + 1;
    }
    return sum % TABLE_SIZE;
}

// Simple freeing of the memory allocated
void freeD(Dictionary* d){
    for(int i = 0; i < TABLE_SIZE; i++){
        Pair current = (*d)[i];
        Pair next = NULL;
        while(current != NULL){
            next = current->next;
            free(current);
            current = next;
        }
        (*d)[i] = NULL;
    }
}

//Traverses to the whole dictionary
//Check for NULL
//Prints the output
void printD(Dictionary* d){
    for(int i = 0; i < TABLE_SIZE; i++){
        Pair current = (*d)[i];
        printf("[%d] --> ", i);
        while(current != NULL){
            printf("[%d : %c] --> ", current->unhashedKey, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Simple initialization
void init(Dictionary* d){
    for(int i = 0; i < TABLE_SIZE; i++){
        (*d)[i] = NULL;
    }
}
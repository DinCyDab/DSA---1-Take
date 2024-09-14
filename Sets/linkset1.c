#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10
#define MAX_NAME 20

typedef struct node{
    char name[MAX_NAME];
    struct node* next;
}*Node;

typedef struct set{
    Node data[MAX];
}*Set;

void freeSet(Set s);
void printSet(Set s);
int getIndex(char* name);
void append(Set s, char* name);
bool isElement(Set s, char* name);
Set init();

int main(){
    Set s = init();

    append(s, "Dino");
    append(s, "Jacques");
    append(s, "Alice");
    append(s, "In");
    append(s, "Borderland");
    append(s, "Cyrano");
    append(s, "Azucenas");
    append(s, "Dabon");
    append(s, "Dalila");
    append(s, "Gail");
    append(s, "Alrik");
    append(s, "Halona");
    append(s, "Neva");

    printSet(s);
    freeSet(s);
    s = NULL;
    return 0;
}

bool isElement(Set s, char* name){
    int index = getIndex(name);
    Node current = s->data[index];
    while(current != NULL){
        if(strcmp(current->name, name) == 0){
            return true;
        }
        current = current->next;
    }
    return false;
}

void append(Set s, char* name){
    if(isElement(s, name)){
        printf("%s is already inside the set\n", name);
        return;
    }

    Node newNode = (Node)malloc(sizeof(struct node));
    strcpy(newNode->name, name);
    newNode->next = NULL;

    int index = getIndex(name);

    if(s->data[index] == NULL){
        s->data[index] = newNode;
        return;
    }

    Node trav = s->data[index];
    while(trav->next != NULL){
        trav = trav->next;
    }
    trav->next = newNode;

}

int getIndex(char* name){
    int i, sum = 0;
    for(i = 0; name[i] != '\0'; i++){
        sum += (int) name[i];
    }
    return sum % MAX;
}

Set init(){
    Set s = (Set)malloc(sizeof(struct set));

    if(s == NULL){
        // ERROR
    }

    for(int i = 0; i < MAX; i++){
        s->data[i] = NULL;
    }

    return s;
}

void freeSet(Set s){
    for(int i = 0; i < MAX; i++){
        Node current = s->data[i];
        Node next = NULL;
        while(current != NULL){
            next = current->next;
            free(current);
            current = next;
        }
        s->data[i] = NULL;
    }
    free(s);
}

void printSet(Set s){
    for(int i = 0; i < MAX; i++){
        Node current = s->data[i];
        printf("[%d] --> ", i);
        while(current != NULL){
            printf("%s --> ", current->name);
            current = current->next;
        }
        printf("NULL\n");
    }
}
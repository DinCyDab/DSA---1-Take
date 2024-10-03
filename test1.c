#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10
#define SIZE 10

typedef char String[16];

typedef struct{
    String city;
    int zip;
}Address;

typedef struct{
    int id;
    String name;
    Address add;
}Person;

typedef struct{
    Person* list;
    int count;
    int max;
}PersonList, StackAList, PersonCloseDict;

typedef struct{
    Person list[MAX];
    int front;
    int rear;
}QueueAList;

typedef struct node{
    Person p;
    struct node* link;
}NodeType, *NodePtr, *StackLList;

typedef struct{
    NodePtr list[SIZE];
    int count;
}PersonOpenDict;

typedef struct{
    NodePtr head;
    NodePtr tail;
}QueuePersonLList;

StackLList getVoters(PersonList vlist, String city);
String* getNames(PersonOpenDict d, String city);
// void getVoters(PersonList vlist, StackLList* v, String city);
QueuePersonLList getUniqueVoters(StackLList vlist);

void addVoter(PersonList* vlist, Person info);

Person createPerson(int id, String name, Address add);
Address createAddress(String city, int zip);

void initList(PersonList* vlist);
void displayList(PersonList vlist);

void displayLista(StackLList list);

void addVoterOpenDict(PersonOpenDict* d, Person info);
int getHash(Person info);
void printNames(String* names);

void initOpenDict(PersonOpenDict* vlist);
void displayListOpen(PersonOpenDict d);

void displayUnique(QueuePersonLList uniqueVoters);

int main(){
    // Test Case 1
    // PersonList vlist;
    // initList(&vlist);
    // addVoter(&vlist, createPerson(50, "Dino", createAddress("Maguikay", 6000)));
    // addVoter(&vlist, createPerson(100, "Jacques", createAddress("Anitas", 6000)));
    // addVoter(&vlist, createPerson(150, "Alrik", createAddress("Maguikay", 6000)));
    // StackLList lista = getVoters(vlist, "Maguikay");
    // displayLista(lista);
    // free(vlist.list);

    // Test Case 2
    // PersonOpenDict d;
    // initOpenDict(&d);
    // addVoterOpenDict(&d, createPerson(50, "Dino", createAddress("Maguikay", 6000)));
    // addVoterOpenDict(&d, createPerson(100, "Jacques", createAddress("Anitas", 6000)));
    // addVoterOpenDict(&d, createPerson(99, "Alrik", createAddress("Maguikay", 6000)));
    // displayListOpen(d);
    // String* names = getNames(d, "Maguikay");
    // printNames(names);
    // free(names);

    //Test Case 3
    // PersonOpenDict d;
    // initOpenDict(&d);
    // addVoterOpenDict(&d, createPerson(50, "Dino", createAddress("Maguikay", 6000)));
    // addVoterOpenDict(&d, createPerson(100, "Jacques", createAddress("Anitas", 6000)));
    // addVoterOpenDict(&d, createPerson(100, "Jacques", createAddress("Anitas", 6000)));
    // addVoterOpenDict(&d, createPerson(100, "Jacques", createAddress("Anitas", 6000)));
    // addVoterOpenDict(&d, createPerson(99, "Alrik", createAddress("Maguikay", 6000)));
    // QueuePersonLList uniqueVoters = getUniqueVoters(d.list[1]);
    // displayUnique(uniqueVoters);
    return 0;
}

void displayUnique(QueuePersonLList uniqueVoters){
    NodePtr current = uniqueVoters.head;
    while(current != NULL){
        printf("ID: %d, ", current->p.id);
        printf("Name: %s\n", current->p.name);
        printf("Address:\n");
        printf("City: %s, ", current->p.add.city);
        printf("ZIP: %d --> ", current->p.add.zip);
        current = current->link;
    }
}

void displayListOpen(PersonOpenDict d){
    for(int i = 0; i < SIZE; i++){
        printf("[%d] --> ", i);
        NodePtr current = d.list[i];
        while(current != NULL){
            printf("ID: %d, ", current->p.id);
            printf("Name: %s\n", current->p.name);
            printf("Address:\n");
            printf("City: %s, ", current->p.add.city);
            printf("ZIP: %d --> ", current->p.add.zip);
            current = current->link;
        }
        printf("NULL\n\n");
    }
}

void initOpenDict(PersonOpenDict* vlist){
    for(int i = 0; i < SIZE; i++){
        vlist->list[i] = NULL;
    }
}

void printNames(String* names){
    for(int i = 0; strcmp(names[i], "") != 0; i++){
        printf("%s\n", names[i]);
    }
}

void addVoterOpenDict(PersonOpenDict* d, Person info){
    int index = getHash(info);
    NodePtr current = d->list[index];
    while(current != NULL && current->p.id != info.id){
        current = current->link;
    }

    // if(current == NULL){
        NodePtr newNode = (NodePtr)malloc(sizeof(struct node));
        newNode->p = info;
        newNode->link = d->list[index];
        d->list[index] = newNode;
        d->count++;
    // }
    // else{
    //     //Duplicate ID
    //     printf("Data is already inside the dictionary\n");
    // }
    
}

int getHash(Person info){
    int sum = 0;
    for(int i = 0; i < 3 && info.name[i] != '\0' && info.id != 0 && info.add.city[i] != '\0'; i++, info.id /= 10){
        sum += ((int) info.name[i]) + (info.id % 10) + ((int) info.add.city[i]);
    }
    return sum % SIZE;
}

void displayLista(StackLList list){
    NodePtr current = list;
    while(current != NULL){
        printf("ID: %d, ", current->p.id);
        printf("Name: %s\n", current->p.name);
        printf("Address:\n");
        printf("City: %s, ", current->p.add.city);
        printf("ZIP: %d\n\n", current->p.add.zip);
        current = current->link;
    }
}

void addVoter(PersonList* vlist, Person info){
    if(vlist->count == vlist->max){
        printf("List is FULL");
        return;
    }

    vlist->count++;
    vlist->list[vlist->count] = info;
}

void initList(PersonList* vlist){
    vlist->list = (Person*)calloc(MAX, sizeof(Person));
    vlist->count = -1;
    vlist->max = MAX;
}

void displayList(PersonList vlist){
    for(int i = 0; i <= vlist.count; i++){
        printf("ID: %d, ", vlist.list[i].id);
        printf("Name: %s\n", vlist.list[i].name);
        printf("Address:\n");
        printf("City: %s, ", vlist.list[i].add.city);
        printf("ZIP: %d\n\n", vlist.list[i].add.zip);
    }
}

Person createPerson(int id, String name, Address add){
    Person p;
    p.id = id;
    strcpy(p.name, name);
    p.add = add;
    return p;
}

Address createAddress(String city, int zip){
    Address a;
    strcpy(a.city, city);
    a.zip = zip;
    return a;
}

QueuePersonLList getUniqueVoters(StackLList vlist){
    QueuePersonLList uniqueVoters;
    uniqueVoters.head = NULL;
    uniqueVoters.tail = NULL;
    NodePtr current = vlist;
    while(current != NULL){
        NodePtr temp = uniqueVoters.head;
        while(temp != NULL && temp->p.id != current->p.id){
            temp = temp->link;
        }

        if(temp == NULL){
            NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));
            newNode->p = current->p;
            newNode->link = NULL;
            
            if(uniqueVoters.head == NULL){
                uniqueVoters.head = uniqueVoters.tail = newNode;
            }
            else{
                uniqueVoters.tail->link = newNode;
                uniqueVoters.tail = newNode;
            }
        }
        current = current->link;
    }
    return uniqueVoters;
}

String* getNames(PersonOpenDict d, String city){
    String* names = (String*)calloc(MAX, sizeof(String));
    int count = 0;
    for(int i = 0; i < SIZE; i++){
        NodePtr current = d.list[i];
        while(current != NULL){
            if(current->p.id >= 1 && current->p.id <= 100 && strcmp(current->p.add.city, city) == 0){
                strcpy(names[count], current->p.name);
                count++;
            }
            current = current->link;
        }
    }
    strcpy(names[count], "");
    return names;
}

StackLList getVoters(PersonList vlist, String city){
    StackLList head = NULL;
    for(int i = 0; i < vlist.max; i++){
        if(strcmp(vlist.list[i].add.city, city) == 0){
            NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));
            newNode->p = vlist.list[i];
            newNode->link = head;
            head = newNode;
        }
    }
    return head;
}
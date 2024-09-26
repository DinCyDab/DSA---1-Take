#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char f_name[20];
    char l_name[20];
    char m_i;
}Name;

typedef struct{
    int day;
    int month;
    int year;
}Date;

typedef struct{
    Name full_name;
    Date birthdate;
}Person;

typedef struct node{
    Person data;
    struct node* next;
}*Node;

typedef struct queue{
    Node front;
    Node rear;
    int count;
}*Queue;

// Function prototype
void insertSort(Queue q, Person data);
void enqueue(Queue q, Person data);
void dequeue(Queue q);
bool isEmpty(Queue q);
Person frontValue(Queue q);

// Helper functions
Queue init();
void freeQueue(Queue q);
void printQueue(Queue q);
Name createName(char* f_name, char* l_name, char m_i);
Date createDate(int day, int month, int year);
Person createPerson(Name full_name, Date birthdate);
int nameDifference(Name name1, Name name2);
int nameInNumbers(char* str1);
Queue sortQueue(Queue q);

// Insert by last name

int main(){
    Queue q = init();
    
    enqueue(q, createPerson(createName("Dino Cyrano", "Aabon", 'D'), createDate(24, 9, 2000)));
    enqueue(q, createPerson(createName("Dino Cyrana", "Dabon", 'A'), createDate(24, 9, 2000)));
    enqueue(q, createPerson(createName("Dino Cyrano", "Babon", 'D'), createDate(24, 9, 2000)));
    enqueue(q, createPerson(createName("Dino Cyrano", "Cabon", 'E'), createDate(24, 9, 2000)));
    
    insertSort(q, createPerson(createName("Dino Cyrano", "Dabon", 'Z'), createDate(24, 9, 2000)));
    enqueue(q, createPerson(createName("Dino Cyrano", "Eabon", 'C'), createDate(24, 9, 2000)));
    enqueue(q, createPerson(createName("Dino Cyrano", "Cabon", 'F'), createDate(24, 9, 2000)));
    
    q = sortQueue(q);
    
    printQueue(q);
    freeQueue(q);
    free(q);
    return 0;
}

Queue sortQueue(Queue q){
    Queue temp = init();
    while(!isEmpty(q)){
        insertSort(temp, q->front->data);
        dequeue(q);
    }
    return temp;
}

void insertSort(Queue q, Person data){
    if(isEmpty(q) || q->rear->data.full_name.m_i - data.full_name.m_i < 0){
        enqueue(q, data);
        return;
    }
    
    Queue temp = init();
    while(!isEmpty(q) &&  q->front->data.full_name.m_i - data.full_name.m_i < 0){
        enqueue(temp, q->front->data);
        dequeue(q);
    }
    
    enqueue(temp, data);

    while(!isEmpty(q)){
        enqueue(temp, q->front->data);
        dequeue(q);
    }
    
    while(!isEmpty(temp)){
        enqueue(q, temp->front->data);
        dequeue(temp);
    }
}

void enqueue(Queue q, Person data){
    Node newNode = (Node)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    
    if(isEmpty(q)){
        q->front = newNode;
        q->rear = newNode;
        q->count++;
        return;
    }
    
    q->rear->next = newNode;
    q->rear = newNode;
}

void dequeue(Queue q){
    if(isEmpty(q)){
        return;
    }
    
    Node temp = q->front;
    q->front = q->front->next;
    free(temp);
    q->count--;
    
    if(isEmpty(q)){
        q->rear = NULL;
    }
}

int nameDifference(Name name1, Name name2) {
    int cmp = strcmp(name1.l_name, name2.l_name);
    if (cmp != 0) {
        printf("%d\n", cmp);
        return cmp;  // Return comparison result for last names
    }
    
    cmp = strcmp(name1.f_name, name2.f_name);
    if (cmp != 0) {
        return cmp;  // Return comparison result for first names
    }

    return (name1.m_i - name2.m_i);  // Compare middle initials
}

int nameInNumbers(char* str){
    int sum = 0;
    for(int i = 0; str[i] != '\0'; i++){
        sum += (int) str[i];
    }
    return sum;
}

bool isEmpty(Queue q){
    return q->front == NULL;
}

Person frontValue(Queue q){
    return q->front->data;
}

Name createName(char* f_name, char* l_name, char m_i){
    Name n;
    strcpy(n.f_name, f_name);
    strcpy(n.l_name, l_name);
    n.m_i = m_i;
    return n;
}

Date createDate(int day, int month, int year){
    Date d;
    d.day = day;
    d.month = month;
    d.year = year;
    return d;
}

Person createPerson(Name full_name, Date birthdate){
    Person p;
    p.full_name = full_name;
    p.birthdate = birthdate;
    return p;
}

void freeQueue(Queue q){
    Node current = q->front;
    Node next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

void printQueue(Queue q){
    Node current = q->front;
    while(current != NULL){
        printf("Name: ");
        printf("%s ", current->data.full_name.f_name);
        printf("%c. ", current->data.full_name.m_i);
        printf("%s ", current->data.full_name.l_name);
        printf("Birthdate: ");
        printf("%d ", current->data.birthdate.month);
        printf("%d ", current->data.birthdate.day);
        printf("%d\n", current->data.birthdate.year);
        current = current->next;
    }
}

Queue init(){
    Queue q = (Queue)malloc(sizeof(struct queue));
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
    return q;
}
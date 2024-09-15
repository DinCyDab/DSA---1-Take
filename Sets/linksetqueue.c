#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 20
#define MAX_SIZE 2

// 1.) Insert sort by name for now

typedef struct student{
    char name[MAX_NAME];
    int id;
}*Student;

typedef struct node{
    Student data;
    struct node* next;
}*Node;

typedef struct queue{
    Node front;
    Node rear;
}*Queue;

typedef struct set{
    Queue queue[MAX_SIZE];
    int count;
}*Set;

// Initialize the set
Set init();

// Returns only the Student data
Student addStudent(char* name, int id);

// Logic for insert sort in queue
void insertSort(Set s, Student data);

// Logic for hash set getting index
int getIndex(char* name);

// Logic for set
bool isElement(Set s, char* name);

// Returns only the current size of the whole set
int setCurrentSize(Set s);

// Dequeue on which row does the user input
// Logic for dequeueing
Node dequeue(Set s, int row);

// Returns only if the current row of the queue is empty
bool isEmpty(Queue q);

// Helper functions
bool greaterString(char* string1, char* string2);
void freeSet(Set s);
void printSet(Set s);

int main(){
    //Initializes the set
    Set s = init();

    // Insert the data
    insertSort(s, addStudent("Dinod", 19103291));
    insertSort(s, addStudent("Finod", 19103291));
    insertSort(s, addStudent("Eacques", 22010010));

    // Node temp = dequeue(s, 0);
    // if(temp != NULL){
    //     printf("\nDequeued: [Name: %s | ID: %d]\n\n", temp->data->name, temp->data->id);
    //     free(temp);
    // }
    
    // Print the set
    printSet(s);

    // Free the set
    freeSet(s);
    return 0;
}

bool isEmpty(Queue q){
    return q->front == NULL;
}

Node dequeue(Set s, int row){
    if(row < 0 || row > MAX_SIZE - 1){
        printf("Row doesn't exist\n");
        return NULL;
    }
    if(isEmpty(s->queue[row])){
        printf("Cannot dequeue, [%d] Row is Empty\n");
        return NULL;
    }

    Node temp = s->queue[row]->front;
    Node *front = &(s->queue[row]->front);
    
    (*front) = (*front)->next;

    if(*front == NULL){
        s->queue[row]->rear = NULL;
    }

    s->count--;

    return temp;
}

int setCurrentSize(Set s){
    return s->count;
}

bool isElement(Set s, char* name){
    int index = getIndex(name);
    Node current = s->queue[index]->front;
    while(current != NULL){
        if(strcmp(current->data->name, name) == 0){
            return true;
        }
        current = current->next;
    }
    return false;
}

bool greaterString(char* string1, char* string2){
    int i;
    for(i = 0; string1[i] != '\0' && string2[i] != '\0' && string1[i] == string2[i]; i++);

    return string1[i] < string2[i];
}

void insertSort(Set s, Student data){
    if(isElement(s, data->name)){
        printf("%s is already inside the set\n", data->name);
        return;
    }
    Node newNode = (Node)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    int index = getIndex(data->name);

    //Dereference the front and rear according to the index for simplicity or put this in a completely different function
    //For complexity access directly the front and rear
    //It will become: s->queue[index]->front = newNode and more
    Node* head = &(s->queue[index]->front);
    Node* tail = &(s->queue[index]->rear);
    s->count++;

    //If the front is NULL, just insert directly the data
    if(*head == NULL){
        *head = newNode;
        *tail = newNode;
        return;
    }

    //If the data has a lesser value than the front, insert first
    if(greaterString(newNode->data->name, (*head)->data->name) == 1){
        newNode->next = (*head);
        (*head) = newNode;
        return;
    }

    //If the data has a greater value than the tail, insert last
    if(greaterString(newNode->data->name, (*tail)->data->name) == 0){
        (*tail)->next = newNode;
        *tail = newNode;
        return;
    }

    //If the data is in the middle of the queue, traverse the list, then put it inside the right position
    Node current = *head;
    Node prev = NULL;
    while(current != NULL && greaterString(newNode->data->name, current->data->name) == 0){
        prev = current;
        current = current->next;
    }

    prev->next = newNode;
    newNode->next = current;
}

Student addStudent(char* name, int id){
    Student s = (Student)malloc(sizeof(struct student));
    strcpy(s->name, name);
    s->id = id;
    return s;
}

// Hashing technique
int getIndex(char* name){
    int sum = 0;
    for(int i = 0; name[i] != '\0'; i++){
        sum += (int) name[i];
    }
    return sum % MAX_SIZE;
}

Set init(){
    Set s = (Set)malloc(sizeof(struct set));
    for(int i = 0; i < MAX_SIZE; i++){
        s->queue[i] = (Queue)malloc(sizeof(struct queue));
        s->queue[i]->front = NULL;
        s->queue[i]->rear = NULL;
    }
    s->count = 0;
    return s;
}

void freeSet(Set s){
    for(int i = 0; i < MAX_SIZE; i++){
        Node current = s->queue[i]->front;
        Node next = NULL;
        while(current != NULL){
            next = current->next;
            //Free the student data
            free(current->data);

            //Free the Node that points to the student data
            free(current);
            current = next;
        }
        s->queue[i]->front = NULL;
        s->queue[i]->rear = NULL;

        //Free 
        free(s->queue[i]);
    }
    free(s);
}

void printSet(Set s){
    printf("QUEUE:\n");
    for(int i = 0; i < MAX_SIZE; i++){
        Node current = s->queue[i]->front;
        printf("[%d] --> ", i);
        while(current != NULL){
            printf("[%s | %d] --> ", current->data->name, current->data->id);
            current = current->next;
        }
        printf("NULL\n");
    }
}
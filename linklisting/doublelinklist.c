// Problem: Doubly Linked List Implementation in C
// You are required to implement a doubly linked list data structure in C. A doubly linked list is a type of linked list where each node contains a pointer to the next node as well as a pointer to the previous node. This allows traversal in both directions (forward and backward).

// Requirements:
// Define a Node Structure:

// Use a typedef struct to define a node that holds:
// An integer data.
// A pointer to the next node.
// A pointer to the previous node.
// Define a Doubly Linked List Structure:

// Use another typedef struct to define a doubly linked list that contains:
// A pointer to the head node.
// A pointer to the tail node.
// Functions to Implement:

// void append(DoublyLinkedList* list, int value): Adds a new node with the given value at the end of the list.
// void prepend(DoublyLinkedList* list, int value): Adds a new node with the given value at the beginning of the list.
// void deleteNode(DoublyLinkedList* list, int value): Deletes the first node with the given value.
// void displayForward(const DoublyLinkedList* list): Prints all the values in the list from head to tail.
// void displayBackward(const DoublyLinkedList* list): Prints all the values in the list from tail to head.
// int isEmpty(const DoublyLinkedList* list): Returns 1 if the list is empty, 0 otherwise.
// void freeList(DoublyLinkedList* list): Frees all nodes in the list and sets the head and tail pointers to NULL.

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} Node;

typedef struct doublyLinkedList {
    Node* head;
    Node* tail;
} DoublyLinkedList;

// Function declarations
void append(DoublyLinkedList* list, int value);
void prepend(DoublyLinkedList* list, int value);
void deleteNode(DoublyLinkedList* list, int value);
void displayForward(const DoublyLinkedList* list);
void displayBackward(const DoublyLinkedList* list);
int isEmpty(const DoublyLinkedList* list);
void freeList(DoublyLinkedList* list);

int main() {
    DoublyLinkedList list = {NULL, NULL}; // Initialize an empty doubly linked list

    append(&list, 10);
    append(&list, 20);
    prepend(&list, 5);
    displayForward(&list);   // Should display: 5 <-> 10 <-> 20
    displayBackward(&list);  // Should display: 20 <-> 10 <-> 5

    deleteNode(&list, 10);
    displayForward(&list);   // Should display: 5 <-> 20
    displayBackward(&list);  // Should display: 20 <-> 5

    printf("Is Empty: %d\n", isEmpty(&list)); // Should display: Is Empty: 0

    freeList(&list); // Free the list memory
    return 0;
}

// Function definitions

void append(DoublyLinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        printf("MEMORY ALLOCATION FAILED\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = list->tail;
    if(list->head == NULL){
        list->head = newNode;
    }
    else{
        list->tail->next = newNode;
    }
    
    list->tail = newNode;
}

void prepend(DoublyLinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        printf("MEMORY ALLOCATION FAILED\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = list->head;

    if(list->head == NULL){
        list->tail = newNode;
    }
    else{
        list->head->prev = newNode;
    }
    
    list->head = newNode;
}

void deleteNode(DoublyLinkedList* list, int value) {
    if(isEmpty(list)){
        printf("No Node to delete\n");
        return;
    }

    Node* current = list->head;
    while(current != NULL && current->data != value){
        current = current->next;
    }

    if(current == NULL){
        printf("Value not found\n");
        return;
    }

    if(current == list->head){
        list->head = list->head->next;
        if(list->head != NULL){
            list->head->prev = NULL;
        }
        else{
            list->tail = NULL;
        }
    }
    else if(current == list->tail){
        list->tail = list->tail->prev;
        if(list->tail != NULL){
            list->tail->next = NULL;
        }
        else{
            list->head = NULL;
        }
    }
    else{
        current->next->prev = current->prev;
        current->prev->next = current->next;
    }

    free(current);
}

void displayForward(const DoublyLinkedList* list) {
    Node* current = list->head;
    while(current != NULL){
        printf("%d <--> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void displayBackward(const DoublyLinkedList* list) {
    Node* current = list->tail;
    while(current != NULL){
        printf("%d <--> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

int isEmpty(const DoublyLinkedList* list) {
    return list->head == NULL;
}

void freeList(DoublyLinkedList* list) {
    Node* current = list->head;
    Node* next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CAR_ID_LENGTH 100
#define MAX_CARS 10

//Node Structure for the Queue
struct Node {
    char action[5]; // Action to perform: "push" (return car) or "pop" (rent car)
    char customerName[100]; // Customer's name
    char carId[CAR_ID_LENGTH]; // Car ID that the customer rented, empty if not rented
    struct Node* next; // Pointer to the next node in the queue
};

// Stack Structure for Car IDs:
typedef struct {
    char carIds[MAX_CARS][CAR_ID_LENGTH]; // Array to hold car IDs contiguously
    int top; // Index of the top element in the stack
} CarStack;

// Queue Structure:
typedef struct Queue{
    struct Node *front; // Pointer to the front of the queue
    struct Node *rear; // Pointer to the rear of the queue
}*Queue;

//Queue Functions:
Queue createQueue();
void enqueue(Queue q, char *action, char *customerName, char *carId);
struct Node* dequeue(Queue q, CarStack* s, struct Node* history);
int isQueueEmpty(Queue q);

//Stack Functions:
void initializeCarStack(CarStack* s);
int pushCar(CarStack* s, char *carId);
char* popCar(CarStack* s);
int isCarStackEmpty(CarStack* s);
int isCarStackFull(CarStack* s);

//Printing, Freeing of memory allocation and some helper functions
void printQueue(struct Node* head);
void printStack(CarStack s);
void printHistory(struct Node* history);
void freeQueue();
void freeHistory(struct Node* history);
void stringToLower(char* action);
void freeString(char* string);
int isStringEmptyOrWhitespace(const char *str);

struct Node* head = NULL;

int main(){
    Queue first_rear = createQueue();
    CarStack car_stack;
    struct Node* history = NULL;
    initializeCarStack(&car_stack);
    int isAdded;

    enqueue(first_rear, "push", "Dino", "Civic");
    enqueue(first_rear, "push", "Cyrano", "Honda2");
    // enqueue(first_rear, "push", "Dabon", "Honda3");
    // enqueue(first_rear, "push", "Dino", "Honda");
    // enqueue(first_rear, "push", "Cyrano", "Honda");
    // enqueue(first_rear, "push", "Dabon", "Honda");
    // enqueue(first_rear, "push", "Dino", "Honda");
    // enqueue(first_rear, "push", "Cyrano", "Honda");
    // enqueue(first_rear, "push", "Dabon", "Honda");
    // enqueue(first_rear, "push", "Dino", "Honda");
    enqueue(first_rear, "pop", "Dino", "");
    enqueue(first_rear, "pop", "Cyrano", "");
    // enqueue(first_rear, "push", "Dino", "Honda");
    // enqueue(first_rear, "push", "Dino", "Honda");
    history = dequeue(first_rear, &car_stack, history);
    history = dequeue(first_rear, &car_stack, history);
    history = dequeue(first_rear, &car_stack, history);
    history = dequeue(first_rear, &car_stack, history);
    history = dequeue(first_rear, &car_stack, history);
    // history = dequeue(first_rear, &car_stack, history);
    // history = dequeue(first_rear, &car_stack, history);
    // history = dequeue(first_rear, &car_stack, history);
    // history = dequeue(first_rear, &car_stack, history);
    // history = dequeue(first_rear, &car_stack, history);
    // history = dequeue(first_rear, &car_stack, history);
    // history = dequeue(first_rear, &car_stack, history);
    // history = dequeue(first_rear, &car_stack, history);

    printHistory(history);
    printQueue(head);
    printStack(car_stack);
    freeQueue();
    freeHistory(history);

    return 0;
}

// Removes and returns the action node from the front of the
// queue. Updates the front pointer to the next node. If the queue becomes
// empty, the rear pointer is also set to NULL.
struct Node* dequeue(Queue q, CarStack* s, struct Node* history){
    struct Node* current = head;
    if(isQueueEmpty(q)){
        printf("Empty Queue, Cannot Dequeue\n");
        return history;
    }
    //Comparing the string action of the queue
    //Popping just simply copy the string of the car ID to the queue front
    //Pushing simply push the CarID inside the stack
    //If not a valid action, cannot queue
    if(strcmp(q->front->action, "pop") == 0){
        strcpy(q->front->carId, popCar(s));
    }
    else if(strcmp(q->front->action, "push") == 0){
        if(s->top + 1 > MAX_CARS - 1){
            printf("Full Car Stack, Cannot Add more\n");
            return history;
        }
        pushCar(s, q->front->carId);
    }
    else{
        printf("ERROR, not a valid action...\n");
        return history;
    }

    //Instead of freeing the current
    //We will return it for history
    head = current->next;
    q->front = current->next;
    if(q->front == NULL){
        q->rear = NULL;
    }
    current->next = NULL;

    //Simple traversal of history
    //It connects the dequeued queue to the history
    //It returns the history so that the head of history wont change
    //Else if history is NULL, just return the current
    if(history != NULL){
        struct Node* trav = history;
        while(trav->next != NULL){
            trav = trav->next;
        }

        trav->next = current;
        return history;
    }

    return current;
}

void stringToLower(char* action){
    int i;
    for(i = 0; i < strlen(action); i++){
        action[i] = tolower(action[i]);
    }
}

//Checks if the string is just pure space or empty
int isStringEmptyOrWhitespace(const char *str) {
    int i;
    for(i = 0; i < strlen(str); i++){
        if (!isspace(str[i])) { // If a non-whitespace character is found
            return 0; // The string is not empty or whitespace only
        }
    }
    return 1; // The string is empty or contains only whitespace
}

// Adds a new action (rent or return) to the end of the queue. It
// creates a new node, sets its action, customer name, and carId, and
// updates the rear pointer
void enqueue(Queue q, char *action, char *customerName, char *carId){
    if(isStringEmptyOrWhitespace(carId) && strcmp(action, "push") == 0){
        printf("Enter the Car ID\n");
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    //Checks if memory allocation has failed
    if(newNode == NULL){
        printf("Stack is Full, cannot queue\n");
        return;
    }
    
    strcpy(newNode->action, action);
    stringToLower(newNode->action);
    //Checks if the action is valid or not (push or pop)
    //This one is bugged on my end, I cannot directly convert the *action to lower string
    if(strcmp(newNode->action, "pop") != 0 && strcmp(newNode->action, "push") != 0){
        printf("Not a valid action\n");
        free(newNode);
        return;
    }
    strcpy(newNode->customerName, customerName);
    strcpy(newNode->carId, carId);
    newNode->next = NULL;

    //Link the rear node to the new node
    if(head == NULL){
        head = newNode;
        q->front = head;
        q->rear = head;
    }
    else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Checks if the queue is empty by verifying if the front pointer is NULL
int isQueueEmpty(Queue q){
    return q->front == NULL;
}

// Description: Checks if the stack is full by comparing the top index with
// MAX_CARS - 1.
int isCarStackFull(CarStack* s){
    return s->top > MAX_CARS - 1;
}

// Checks if the stack is empty by verifying if the top index is -1.
int isCarStackEmpty(CarStack* s){
    return s->top <= -1;
}

// Removes and returns the car ID from the top of the stack. It
// checks if the stack is empty before removing the ID and updates the top
// index
char* popCar(CarStack* s){
    if(isCarStackEmpty(s)){
        return "No cars to Pop";
    }
    s->top--;
    char* string = (char*)malloc(sizeof(char) * 20);
    strcpy(string, "Rented: ");
    strcat(string, s->carIds[s->top + 1]);
    return string;
}

// Adds a car ID to the top of the stack. It checks if the stack is
// full before adding the ID and updates the top index. Returns 1 if push was
// successfully
int pushCar(CarStack* s, char *carId){
    if(isCarStackFull(s)){
        return -1;
    }
    s->top++;
    strcpy(s->carIds[s->top], carId);
    return 1;
}

// Initializes the stack by setting the top index to -1, indicating
// that the stack is empty.
void initializeCarStack(CarStack* s){
    s->top = -1;
}

// Initializes a new queue by allocating memory and setting the front and rear pointers to NULL.
Queue createQueue(){
    Queue queue = (Queue)malloc(sizeof(struct Queue));
    if(queue == NULL){
        printf("MEMORY ERROR\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

//Free the current queue
void freeQueue(){
    struct Node* current = head;
    struct Node* next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

//Free the history
void freeHistory(struct Node* history){
    struct Node* current = history;
    struct Node* next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        freeString(current->carId);
        current = next;
    }
}

//Free the allocated string
void freeString(char* string){
    free(string);
}

//Print the current car stack
void printStack(CarStack s){
    printf("\n%-10s %-20s\n", "Stack #", "Car ID");
    int i;
    for(i = s.top; i >= 0; i--){
        printf("%-10d %-20s\n", i, s.carIds[i]);
    }
}

//Print the queue history
void printHistory(struct Node* history){
    struct Node* current = history;
    int i = 1;
    printf("\n%-10s %-20s %-10s %-20s\n", "History #", "Customer Name", "Action", "Car ID");
    while(current != NULL){
        printf("%-10d %-20s %-10s %-20s\n", i++, current->customerName, current->action, current->carId);
        current = current->next;
    }
}

//print the current queue
void printQueue(struct Node* head){
    struct Node* current = head;
    int i = 1;
    printf("\n%-10s %-20s %-10s %-20s\n", "Queue #", "Customer Name", "Action", "Car ID");
    while(current != NULL){
        printf("%-10d %-20s %-10s %-20s\n", i++, current->customerName, current->action, current->carId);
        current = current->next;
    }
}
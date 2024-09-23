#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name[30];
    int age;
    char sex;
} Person;

typedef struct node{
    Person data;
    struct node *link;
} NodeType, *NodePtr, *Stack;

void initStack(Stack *s);
bool isEmpty(Stack s);
void displayStack(Stack s);

bool push(Stack *s, Person p);
bool pop(Stack *s);
Person peek(Stack s);

/*Insert sorted base on lastname. Rember to use the property 
  of the stack using push, pop, and peek functions.*/
bool insertSorted1(Stack *s, Person p);

/*Insert sorted base on lastname. Rember to use the property 
  of the stack but without using push, pop, and peek functions.*/
bool insertSorted2(Stack *s, Person p);

/*Sort the values based on name. Use flag for ascending 
  or descending. */
void sortStack(Stack *s, bool flag);

Person createPerson(char name[], int age, char sex);

//Helper functions
int nameDifference(char* name1, char* name2);
void freeStack(Stack s);

int main(){
    Stack s = NULL;
    // initStack(&s);

    // Insert data
    insertSorted1(&s, createPerson("Juinio", 22, 'M'));
    insertSorted1(&s, createPerson("Dabon", 24, 'M'));
    insertSorted2(&s, createPerson("Sabon", 24, 'M'));
    insertSorted2(&s, createPerson("Zabon", 24, 'M'));
    insertSorted2(&s, createPerson("Babon", 24, 'M'));
    // Insert data

    sortStack(&s, 0);
    sortStack(&s, 1);

    displayStack(s);
    freeStack(s);
    free(s);
    return 0;
}

void sortStack(Stack *s, bool flag){
    Stack current = NULL;
    bool isSorted = 0;
    while(!isSorted && flag == 0){
        isSorted = 1;
        current = *s;
        while(current->link != NULL){
            if(nameDifference(current->data.name, current->link->data.name) < 0){
                isSorted = 0;
                Person temp = current->data;
                current->data = current->link->data;
                current->link->data = temp;
            }
            current = current->link;
        }
    }

    while(!isSorted && flag == 1){
        isSorted = 1;
        current = *s;
        while(current->link != NULL){
            if(nameDifference(current->data.name, current->link->data.name) > 0){
                isSorted = 0;
                Person temp = current->data;
                current->data = current->link->data;
                current->link->data = temp;
            }
            current = current->link;
        }
    }
}

bool insertSorted1(Stack *s, Person p){
    if(isEmpty(*s)){
        push(s, p);
        return true;
    }

    if(nameDifference((*s)->data.name, p.name) > 0){
        push(s, p);
        return true;
    }

    Stack temp = NULL;
    Stack current = *s;
    while(current != NULL && nameDifference(current->data.name, p.name) < 0){
        push(&temp, current->data);
        pop(s);
        current = current->link;
    }

    push(s, p);

    current = temp;
    while(current != NULL){
        push(s, current->data);
        pop(&temp);
        current = current->link;
    }

    return true;
}

bool insertSorted2(Stack *s, Person p){
    Stack newNode = (Stack)malloc(sizeof(struct node));
    newNode->data = p;
    if(isEmpty(*s)){
        newNode->link = *s;
        *s = newNode;
        return true;
    }

    if(nameDifference((*s)->data.name, p.name) > 0){
        newNode->link = *s;
        *s = newNode;
        return true;
    }

    Stack prev = NULL;
    Stack current = *s;

    while(current != NULL && nameDifference(current->data.name, p.name) < 0){
        // push(&temp, current->data);
        // pop(s);
        // current = current->link;
        prev = current;
        current = current->link;
    }

    prev->link = newNode;
    newNode->link = current;

    return true;
}

int nameDifference(char* name1, char* name2){
    int i;
    for(i = 0; name1[i] != '\0' && name2[i] != '\0' && name1[i] == name2[i]; i++);

    return name1[i] - name2[i];
}

bool isEmpty(Stack s){
    return s == NULL;
}

bool push(Stack *s, Person p){
    Stack newNode = (Stack)malloc(sizeof(struct node));
    newNode->data = p;
    newNode->link = *s;
    *s = newNode;
    return true;
}

bool pop(Stack *s){
    if(isEmpty(*s)){
        printf("Empty Stack");
        return false;
    }

    Stack current = *s;
    *s = (*s)->link;
    free(current);

    return true;
}

Person peek(Stack s){
    return s->data;
}

Person createPerson(char name[], int age, char sex){
    Person p;
    strcpy(p.name, name);
    p.age = age;
    p.sex = sex;
    return p;
}

void freeStack(Stack s){
    Stack current = s;
    Stack next = NULL;
    while(current != NULL){
        next = current->link;
        free(current);
        current = next;
    }
    s = NULL;
}

void displayStack(Stack s){
    Stack current = s;
    while(current != NULL){
        printf("[%s, %d, %c] --> ", current->data.name, current->data.age, current->data.sex);
        current = current->link;
    }
    printf("NULL");
}
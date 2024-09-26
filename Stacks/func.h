#ifndef PERSON_H
#define PERSON_H

typedef struct{
    int day;
    int month;
    int year;
}Date;

typedef struct{
    char f_name[20];
    char l_name[20];
    char m_i;
}Name;

typedef struct{
    Name full_name;
    Date birthdate;
}Person;

typedef struct node{
    Person data;
    struct node* next;
}*Node;

typedef struct stack{
    Node top;
    int count;
}*Stack;

// Main function prototype
void push(Stack s, Person data);
void pop(Stack s);
int isEmpty(Stack s);
Person top(Stack s);
int size(Stack s);
void insertSort(Stack s, Person data);

//Helper functions
int monthsToDays(int year, int month);
int dateDifference(Date date1, Date date2);
Person createPerson(Name full_name, Date birthdate);
Name createName(char* f_name, char* l_name, char m_i);
Date createBdate(int day, int month, int year);
void printStack(Stack s);
void freeStack(Stack s);
Stack init();

#endif
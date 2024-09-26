#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isEmpty(Stack s){
    return s->top == NULL;
}

void insertSort(Stack s, Person data){
    if(isEmpty(s) || dateDifference(s->top->data.birthdate, data.birthdate) < 0){
        push(s, data);
        return;
    }

    Stack temp = init();
    while(!isEmpty(s) && dateDifference(s->top->data.birthdate, data.birthdate) > 0){
        push(temp, s->top->data);
        pop(s);
    }

    push(s, data);

    while(!isEmpty(temp)){
        push(s, temp->top->data);
        pop(temp);
    }
}

void push(Stack s, Person data){
    Node newNode = (Node)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
    s->count++;
}

void pop(Stack s){
    if(isEmpty(s)){
        return;
    }
    Node current = s->top;
    s->top = s->top->next;
    free(current);
    s->count--;
}

Person top(Stack s){
    return s->top->data;    
}

int size(Stack s){
    return s->count;
}

int monthsToDays(int year, int month){
    int sum = 0;
    while(month != 0){
        if(year % 4 == 0 && month == 2){
            sum += 28;
        }
        else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
            sum += 31;
        }
        else{
            sum += 30;
        }
        month--;
    }
    return sum;
}

int dateDifference(Date date1, Date date2){
    int numDays1 = (date1.year * 365) + monthsToDays(date1.year, date1.month) + date1.day;
    int numDays2 = (date2.year * 365) + monthsToDays(date2.year, date1.month) + date2.day;

    return numDays2 - numDays1;
}

//Helper functions
Person createPerson(Name full_name, Date birthdate){
    Person p;
    p.full_name = full_name;
    p.birthdate = birthdate;
    return p;
}

Name createName(char* f_name, char* l_name, char m_i){
    Name f;
    strcpy(f.f_name, f_name);
    strcpy(f.l_name, l_name);
    f.m_i = m_i;
    return f;
}

Date createBdate(int day, int month, int year){
    Date d;
    d.day = day;
    d.month = month;
    d.year = year;
    return d;
}

void printStack(Stack s){
    Node current = s->top;
    while(current != NULL){
        printf("[%s ", current->data.full_name.f_name);
        printf("%s ", current->data.full_name.l_name);
        printf("%c. ", current->data.full_name.m_i);
        printf("%d ", current->data.birthdate.month);
        printf("%d ", current->data.birthdate.day);
        printf("%d]\n", current->data.birthdate.year);
        current = current->next;
    }
}

void freeStack(Stack s){
    Node current = s->top;
    Node next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    s->top = NULL;
    s->count = 0;
}

Stack init(){
    Stack s = (Stack)malloc(sizeof(struct stack));
    s->top = NULL;
    s->count = 0;
    return s;
}
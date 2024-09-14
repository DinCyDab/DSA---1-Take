#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 20

typedef struct student{
    char name[MAX_NAME];
    int id;
}*Student;

typedef struct set{
    Student data[10];
    int count;
    int max;
}*Set;

// Jacques|22010010
// index = 0
// Jackie
// index = 0
// Dinosaur
// index = 0

//isElement(Dinosaur)
//index = 0

// [0] = Jacques|22010010
// [1] = Jackie|229999
// [2] = Dino|19010010
// [3] = Dinosaur|41516515
// [4]
// [5]
// [6]
// [7]
// [8]
// [9] 

Set init();
bool isElement(Set s, Student data);
void insert(Set s, Student data);
Student addStudent(char* name, int id);
void printSet(Set s);
int getIndex(char* name);
void freeSet(Set s);
bool isFull(Set s);

int main(){
    Set s = init();

    insert(s, addStudent("Jacques", 22010010));
    // insert(s, addStudent("Jacques", 22010010));
    // insert(s, addStudent("Dino", 19103291));
    // insert(s, addStudent("L", 19103291));
    // insert(s, addStudent("V", 19103291));
    insert(s, addStudent("Jacques", 22010010));
    insert(s, addStudent("B", 19103291));
    printSet(s);
    freeSet(s);
    free(s);
    return 0;
}

Set init(){
    Set s = (Set)malloc(sizeof(struct set));
    for(int i = 0; i < 10; i++){
        s->data[i] = (Student)malloc(sizeof(struct student));
        strcpy(s->data[i]->name, "");
        s->data[i]->id = 0;
    }
    s->count = 0;
    s->max = 10;
    return s;
}

void insert(Set s, Student data){
    if(isFull(s)){
        printf("Cannot insert, Set is full\n");
        return;
    }
    if(isElement(s, data)){
        printf("Data is already inside the set.\n");
        return;
    }

    int index = getIndex(data->name);

    while(strcmp(s->data[index]->name, "") != 0){
        index = (index + 1) % 10;
    }

    s->data[index] =  data;
    s->count++;
}

bool isElement(Set s, Student data){
    for(int i = 0; i < s->max; i++){
        if(strcmp(s->data[i]->name, data->name) == 0){
            return true;
        }
    }
    return false;
}

int getIndex(char* name){
    int i;
    int sum = 0;
    for(i = 0; name[i] != '\0'; i++){
        sum += (int) name[i];
    }
    return sum % 10;
}

Student addStudent(char* name, int id){
    Student s = (Student)malloc(sizeof(struct student));
    strcpy(s->name, name);
    s->id = id;
    return s;
}

void printSet(Set s){
    for(int i = 0; i < s->max; i++){
        if(s->data[i]->name[0] == '\0'){
            continue;
        }
        printf("%d.) Name: %s | ID: %d\n", i, s->data[i]->name, s->data[i]->id);
    }
}

void freeSet(Set s){
    for(int i = 0; i < 10; i++){
        free(s->data[i]);
    }
}

bool isFull(Set s){
    return s->count == s->max;
}
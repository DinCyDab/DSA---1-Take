#include "func.c"


// Insert by birthdate
int main(){
    Stack s = init();
    
    insertSort(s, createPerson(createName("Dabon", "Dino Cyrano", 'A'), createBdate(24, 9, 2000)));
    insertSort(s, createPerson(createName("Alice", "Smith", 'B'), createBdate(15, 5, 1995)));
    insertSort(s, createPerson(createName("Bob", "Johnson", 'C'), createBdate(10, 11, 1988)));
    insertSort(s, createPerson(createName("Clara", "Oswald", 'D'), createBdate(1, 12, 1992)));
    // insertSort(s, createPerson(createName("David", "Miller", 'E'), createBdate(30, 6, 1990)));
    
    printStack(s);
    freeStack(s);
    free(s);
    return 0;
}
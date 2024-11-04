#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5
#define SET 1
#define UNSET 0

typedef int Set[MAX];

void init(Set* main);
void display(Set main);
Set* unioN(Set* A, Set* B);
Set* intersection(Set* A, Set* B);
Set* difference(Set* A, Set* B);
Set* symmetricdiff(Set* A, Set* B);
Set* complement(Set* A);

int main(){
    Set A;
    Set B;
    init(&A);
    init(&B);

    A[0] = SET;
    A[1] = SET;
    // A[2] = SET;
    A[3] = SET;
    A[4] = SET;
    B[3] = SET;
    B[4] = SET;

    Set* C = symmetricdiff(&A, &B);

    display(A);
    display(B);
    display(*C);
    free(C);
    return 0;
}

Set* unioN(Set* A, Set* B){
    Set* C = (Set*)malloc(sizeof(Set));
    for(int i = 0; i < MAX; i++){
        (*C)[i] = (*A)[i] || (*B)[i];
    }
    return C;
}

Set* intersection(Set* A, Set* B){
    Set* C = (Set*)malloc(sizeof(Set));
    for(int i = 0; i < MAX; i++){
        (*C)[i] = (*A)[i] && (*B)[i];
    }
    return C;
}

Set* difference(Set* A, Set* B){
    Set* C = (Set*)malloc(sizeof(Set));
    for(int i = 0; i < MAX; i++){
        (*C)[i] = (*A)[i] && !((*B)[i]);
    }
    return C;
}

Set* symmetricdiff(Set* A, Set* B){
    Set* C = (Set*)malloc(sizeof(Set));
    for(int i = 0; i < MAX; i++){
        (*C)[i] = ((*A)[i] && !(*B)[i]) || (!(*A)[i] && (*B)[i]);
    }
    return C;
}
Set* complement(Set* A){
    Set* C = (Set*)malloc(sizeof(Set));
    for(int i = 0; i < MAX; i++){
        (*C)[i] = !(*A)[i];
    }
    return C;
}

void init(Set* main){
    for(int i = 0; i < MAX; i++){
        (*main)[i] = UNSET;
    }
}

void display(Set main){
    for(int i = 0; i < MAX; i++){
        printf("[%d] ", main[i]);
    }
    printf("\n");
}
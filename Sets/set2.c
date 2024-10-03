#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 8

int main(){
    int arr1[] = {1,2,4,5,0,6,7,8};
    int arr2[] = {1,2,0,5,0,3,7,8};

    int arr3[MAX];

    for(int i = 0; i < MAX; i++){
        arr3[i] = arr1[i] & arr2[i];
    }

    for(int i = 0; i < MAX; i++){
        printf("%d\n", arr3[i]);
    }

    return 0;
}
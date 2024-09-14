#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bogoSort(int* arr, int size){
    int isSorted = 0;
    int* temp = arr;
    int count = 0;
    while(!isSorted){
        isSorted = 1;
        int i = 0;
        for (int i = size - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            // Swap array[i] with array[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        for(i = 0; i < size; i++){
            if(temp[i] > temp[i + 1]){
                isSorted = 0;
                break;
            }
        }
        count++;
        printf("%d\n", count);
    }
    printf("Count: %d\n", count);
}

int main(){
    srand(time(NULL));
    int arr[] = {2,1,3,4,2,2,4,2,4,1,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    bogoSort(arr, size);

    for(int i = 0; i < size; i++){
        printf("%d --> ", arr[i]);
    }
    printf("NULL");
    // for(int i = 3; i > 0; i--){
    //     printf("%d\n",  rand() % i);
    // }
    return 0;
}
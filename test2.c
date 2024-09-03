#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* arr, int start, int mid, int end){
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int L[n1], R[n2];

    for(i = 0; i < n1; i++){
        L[i] = arr[start + i];
    }

    for(i = 0; i < n2; i++){
        R[i] = arr[mid + i + 1];
    }

    i = 0;
    j = 0;
    k = start;

    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }

}

void mergeSort(int* arr, int start, int end){
    if(start < end){
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int sum = 0;
    int sum_size = nums1Size + nums2Size;
    int new_array[sum_size];
    int i = 0;
    for(i = 0; i < nums1Size; i++){
        new_array[i] = nums1[i];
    }

    for(int j = 0; j < nums2Size; j++, i++){
        new_array[i] = nums2[j];
    }

    mergeSort(new_array, 0, sum_size - 1);

    //Find the middle
    int mid = (nums1Size + nums2Size) / 2;
    if((nums1Size + nums2Size) % 2 == 0 && mid != 0){
        return (new_array[mid] + new_array[mid - 1]) / 2.0;
    }
    return new_array[mid];
}

int main(){
    int nums1[] = {1,2};
    int nums2[] = {2,3};
    printf("%f", findMedianSortedArrays(nums1, 0, nums2, 2));
    // findMedianSortedArrays(nums1, 2, nums2, 2);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swap(int *i, int *j){
    int temp = *i;
    *i = *j;
    *j = temp;
}


int partition(int arr[], int low, int high){
    int j;
    int i = low-1;
    int pivot = arr[high];

    for (j= low; j<high; j++){
        if (arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return i;
}

void quicksort(int arr[], int low, int high){
    if (high>low){
        int i = partition(arr,low,high);
 

        quicksort(arr, 0, i);
        quicksort(arr,i+2, high);
    }

}


int main(){
    int arr[] = {1,4,5,3,5,2,6};
    quicksort(arr,0,6);
    int i;
    for (i=0; i<7; i++){
        printf("%d", arr[i]);
    }
}
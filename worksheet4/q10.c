#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high, int ORDER) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // ORDER == 0: Ascending
        // ORDER == 1: Descending 
        int condition = (ORDER == 0) ? (arr[j] < pivot) : (arr[j] > pivot);
        
        if (condition) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void QUICKSORT(int arr[], int low, int high, int ORDER) {
    if (low < high) {
        int pi = partition(arr, low, high, ORDER);

        QUICKSORT(arr, low, pi - 1, ORDER);
        QUICKSORT(arr, pi + 1, high, ORDER);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Original Array: ");
    printArray(arr1, n1);

 
    QUICKSORT(arr1, 0, n1 - 1, 0);
    printf("Sorted Array (Ascending, ORDER = 0): ");
    printArray(arr1, n1);

    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

 
    QUICKSORT(arr2, 0, n2 - 1, 1);
    printf("Sorted Array (Descending, ORDER = 1): ");
    printArray(arr2, n2);

    return 0;
}
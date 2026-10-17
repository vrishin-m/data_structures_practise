#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
    int size_l = mid - left + 1;
    int size_r = right - mid;

    int *left_arr = (int *)malloc(sizeof(int) * size_l);
    int *right_arr = (int *)malloc(sizeof(int) * size_r);

    for (int i = 0; i < size_l; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int j = 0; j < size_r; j++) {
        right_arr[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;


    while (i < size_l && j < size_r) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < size_l) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < size_r) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }

  
    free(left_arr);
    free(right_arr);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; 

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right); 
    }
}

void print_arr(int arr[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {4, 5, 2, 3, 1};
    printf("Original: ");
    print_arr(arr, 5);

    merge_sort(arr, 0, 4);

    printf("Sorted:   ");
    print_arr(arr, 5);

    return 0;
}
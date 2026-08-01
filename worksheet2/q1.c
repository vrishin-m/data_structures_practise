#include <stdio.h>
#include <stdlib.h>

void insertSorted(int arr[], int *n, int *ptr)
{
    int i = *n - 1;
    while (i >= 0 && arr[i] > *ptr)
    {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = *ptr;
    (*n)++;
}

int main()
{
    int arr1[10] = {10, 20, 30, 40, 50};
    int n1 = 5;
    int val1 = 35;
    
    printf("--- Test Case 1 ---\n");
    printf("Original array: 10 20 30 40 50\n");
    printf("Value to insert: %d\n", val1);
    insertSorted(arr1, &n1, &val1);
    printf("Array after insertion: ");
    for (int i = 0; i < n1; i++) printf("%d ", arr1[i]);
    printf("\n\n");

    int arr2[10] = {5, 15, 25};
    int n2 = 3;
    int val2 = 2;
    
    printf("--- Test Case 2 ---\n");
    printf("Original array: 5 15 25\n");
    printf("Value to insert: %d\n", val2);
    insertSorted(arr2, &n2, &val2);
    printf("Array after insertion: ");
    for (int i = 0; i < n2; i++) printf("%d ", arr2[i]);
    printf("\n");

    return 0;
}
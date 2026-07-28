/*question 1*/

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
    int arr[10] = {10, 20, 30, 40, 50};
    int n = 5;
    int value = 35;

    insertSorted(arr, &n, &value);

    printf("Array after insertion:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);


    /*question 2*/
    int *ptr2 = (int *)malloc(sizeof(int)*10);
    int *ptr3 = (int *)calloc(5, sizeof(int)*10);
    
    /* making it longer*/
    int *ptr2 = (int *)realloc(ptr2, sizeof(int));

    
    return 0;
}
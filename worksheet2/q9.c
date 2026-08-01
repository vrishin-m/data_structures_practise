#include <stdio.h>
#include <stdlib.h>

int rotate_array(int arr[], int length, int rotate_by){
    int i;
    int new_pos;
    int *new_arr = malloc(length * sizeof(int));
    for (i = 0; i < length; i++){
        new_pos = i + rotate_by;
        if (new_pos >= length){
            new_pos -= length;
        }
        if (new_pos < 0){
            new_pos += length;
        }
        new_arr[new_pos] = arr[i];
    }
    for (i = 0; i < length; i++){
        printf("%d ", new_arr[i]);
    }
    printf("\n");
    free(new_arr);
    return 0;
}

int main()
{
    printf("--- Array Rotation ---\n\n");
    
    int arr1[] = {1, 2, 3, 4};
    printf("Test 1 Original array: 1 2 3 4\n");
    printf("Rotating by -1 positions (Left shift by 1)...\n");
    printf("Resulting array: ");
    rotate_array(arr1, 4, -1);
    
    printf("\n");
    
    int arr2[] = {10, 20, 30, 40, 50};
    printf("Test 2 Original array: 10 20 30 40 50\n");
    printf("Rotating by 2 positions (Right shift by 2)...\n");
    printf("Resulting array: ");
    rotate_array(arr2, 5, 2);
    
    return 0;
}
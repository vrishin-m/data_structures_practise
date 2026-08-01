#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Test 1: Allocating block for 10 integers using malloc...\n");
    int *ptr2 = (int *)malloc(sizeof(int) * 10);
    if (ptr2 != NULL) printf("Result 1: Malloc successful.\n\n");
    
    printf("Test 2: Allocating block for 50 integers (5 blocks of 10) using calloc...\n");
    int *ptr3 = (int *)calloc(5, sizeof(int) * 10);
    if (ptr3 != NULL) printf("Result 2: Calloc successful.\n\n");
    
    printf("Test 3: Modifying the malloc block size to hold 20 integers using realloc...\n");
    ptr2 = (int *)realloc(ptr2, sizeof(int) * 20);
    if (ptr2 != NULL) printf("Result 3: Realloc successful.\n\n");
    
    free(ptr2);
    free(ptr3);
    
    printf("Memory freed.\n");
    
    return 0;
}
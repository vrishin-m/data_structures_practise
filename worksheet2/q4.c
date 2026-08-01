#include <stdio.h>
#include <stdlib.h>

int to_upper(char string[], int length){
    char *ptr = malloc(sizeof(char));
    int i;
    for (i = 0; i < length; i++){
        if (*(string + i) <= 'z' && *(string + i) >= 'a'){
            string[i] -= 32;
        }
    }
    printf("%s\n", string);
    free(ptr);
    return 0;
}

int main()
{
    printf("--- Lowercase to Uppercase Conversion ---\n\n");
    
    char str1[] = "udhay";
    printf("Test 1 Original : udhay\n");
    printf("Test 1 Result   : ");
    to_upper(str1, 5);
    
    printf("\n");
    
    char str2[] = "sanjay123";
    printf("Test 2 Original : sanjay123\n");
    printf("Test 2 Result   : ");
    to_upper(str2, 9);
    
    return 0;
}
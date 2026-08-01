#include <stdio.h>

int reverse_string(char string[], int length){
    char temp;
    int i;
    for (i = 0; i < length / 2; i++){
        temp = string[i];
        string[i] = string[length - i - 1];
        string[length - i - 1] = temp;
    }
    printf("%s\n", string);
    return 0;
}

int main()
{
    printf("--- String Reversal ---\n\n");
    
    char str1[] = "sanjay";
    printf("Test 1 Original : sanjay\n");
    printf("Test 1 Reversed : ");
    reverse_string(str1, 6);
    
    printf("\n");
    
    char str2[] = "udhay";
    printf("Test 2 Original : udhay\n");
    printf("Test 2 Reversed : ");
    reverse_string(str2, 5);
    
    return 0;
}
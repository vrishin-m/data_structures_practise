#include <stdio.h>

void to_lower(char string[], int length) {
    for (int i = 0; i < length; i++) {
        if (string[i] >= 'A' && string[i] <= 'Z') {
            string[i] += 32;
        }
    }
    printf("%s\n", string);
}

int main() {
    printf("--- Uppercase to Lowercase Conversion ---\n\n");
    
    char str1[] = "HELLO";
    printf("Test 1 Original : HELLO\n");
    printf("Test 1 Result   : ");
    to_lower(str1, 5);
    
    printf("\n");
    
    char str2[] = "WoRLd";
    printf("Test 2 Original : WoRLd\n");
    printf("Test 2 Result   : ");
    to_lower(str2, 5);
    
    return 0;
}
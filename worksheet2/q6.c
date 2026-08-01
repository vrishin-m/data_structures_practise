#include <stdio.h>

void toggle_case(char string[], int length) {
    for (int i = 0; i < length; i++) {
        if (string[i] >= 'a' && string[i] <= 'z') {
            string[i] -= 32;
        } else if (string[i] >= 'A' && string[i] <= 'Z') {
            string[i] += 32;
        }
    }
    printf("%s\n", string);
}

int main() {
    printf("--- Toggle Case Conversion ---\n\n");
    
    char str1[] = "HeLlO";
    printf("Test 1 Original : HeLlO\n");
    printf("Test 1 Result   : ");
    toggle_case(str1, 5);
    
    printf("\n");
    
    char str2[] = "uDHAY";
    printf("Test 2 Original : uDHAY\n");
    printf("Test 2 Result   : ");
    toggle_case(str2, 5);
    
    return 0;
}
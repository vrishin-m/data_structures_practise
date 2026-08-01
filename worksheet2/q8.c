#include <stdio.h>

void check_palindrome(char string[], int length) {
    int is_pal = 1;
    for (int i = 0; i < length / 2; i++) {
        if (string[i] != string[length - i - 1]) {
            is_pal = 0;
            break;
        }
    }
    if (is_pal) {
        printf("Result: '%s' IS a palindrome.\n", string);
    } else {
        printf("Result: '%s' IS NOT a palindrome.\n", string);
    }
}

int main() {
    printf("--- Palindrome Checker ---\n\n");
    
    char str1[] = "racecar";
    printf("Test 1: Checking string '%s'...\n", str1);
    check_palindrome(str1, 7);
    
    printf("\n");
    
    char str2[] = "hello";
    printf("Test 2: Checking string '%s'...\n", str2);
    check_palindrome(str2, 5);
    
    return 0;
}
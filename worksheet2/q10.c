#include <stdio.h>

void reverse_pointers(char *arr[], int length) {
    char *temp;
    for (int i = 0; i < length / 2; i++) {
        temp = arr[i];
        arr[i] = arr[length - i - 1];
        arr[length - i - 1] = temp;
    }
}

int main() {
    char *strings[] = {"apple", "banana", "cherry", "date"};
    int len = 4;
    
    printf("--- Reverse Array of Pointers to Strings ---\n\n");
    
    printf("Original array of strings:\n");
    for (int i = 0; i < len; i++) {
        printf("[%d]: %s  ", i, strings[i]);
    }
    printf("\n\n");
    
    reverse_pointers(strings, len);
    
    printf("Reversed array of strings:\n");
    for (int i = 0; i < len; i++) {
        printf("[%d]: %s  ", i, strings[i]);
    }
    printf("\n");
    
    return 0;
}
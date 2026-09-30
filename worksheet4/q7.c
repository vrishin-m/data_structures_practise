#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef enum { INT, FLOAT, CHAR, STRING } DataType;

typedef struct {
    DataType type;
    void *data;
} Element;

typedef struct {
    Element items[MAX];
    int top;
} HeteroStack;

void initHeteroStack(HeteroStack *s) {
    s->top = -1;
}

void push(HeteroStack *s, void *val, DataType type, size_t dataSize) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    s->top++;
    s->items[s->top].type = type;
    s->items[s->top].data = malloc(dataSize);
    memcpy(s->items[s->top].data, val, dataSize);
}

Element pop(HeteroStack *s) {
    Element empty = {0, NULL};
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return empty;
    }
    return s->items[(s->top)--];
}

void printElement(Element item) {
    if (item.data == NULL) return;
    switch (item.type) {
        case INT: printf("INTEGER: %d\n", *(int*)item.data); break;
        case FLOAT: printf("FLOAT: %.2f\n", *(float*)item.data); break;
        case CHAR: printf("CHAR: %c\n", *(char*)item.data); break;
        case STRING: printf("STRING: %s\n", (char*)item.data); break;
    }
}

int main() {
    HeteroStack s;
    initHeteroStack(&s);

    int a = 67;
    float b = 3.14f;
    char c = 'Z';
    char str[] = "potato";

    printf("Pushing items to Heterogeneous Stack...\n");
    push(&s, &a, INT, sizeof(int));
    push(&s, &b, FLOAT, sizeof(float));
    push(&s, &c, CHAR, sizeof(char));
    push(&s, str, STRING, strlen(str) + 1);

    printf("\nPopping items from Heterogeneous Stack:\n");
    for (int i = 0; i < 4; i++) {
        Element el = pop(&s);
        printElement(el);
        free(el.data); 
    }

    return 0;
}
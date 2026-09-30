#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

//linear array
typedef struct {
    int items[MAX];
    int top;
} ArrayStack;

void initArrayStack(ArrayStack *s) {
    s->top = -1;
}

bool underflowArray(ArrayStack *s) {
    return s->top == -1;
}

bool overflowArray(ArrayStack *s) {
    return s->top == MAX - 1;
}

void pushArray(ArrayStack *s, int val) {
    if (overflowArray(s)) {
        printf("Stack Overflow (Array)\n");
        return;
    }
    s->items[++(s->top)] = val;
}

int popArray(ArrayStack *s) {
    if (underflowArray(s)) {
        printf("Stack Underflow (Array)\n");
        return -1;
    }
    return s->items[(s->top)--];
}

//linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} ListStack;

void initListStack(ListStack *s) {
    s->top = NULL;
}

bool underflowList(ListStack *s) {
    return s->top == NULL;
}

bool overflowList(ListStack *s) {
    Node *temp = (Node *)malloc(sizeof(Node));
    if (temp == NULL) return true;
    free(temp);
    return false;
}

void pushList(ListStack *s, int val) {
    if (overflowList(s)) {
        printf("Stack Overflow (Linked List)\n");
        return;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
}

int popList(ListStack *s) {
    if (underflowList(s)) {
        printf("Stack Underflow (Linked List)\n");
        return -1;
    }
    Node *temp = s->top;
    int val = temp->data;
    s->top = s->top->next;
    free(temp);
    return val;
}

//linked array
typedef struct {
    int data;
    int next;
} ArrayNode;

typedef struct {
    ArrayNode nodes[MAX];
    int top;
    int free_head;
} LinkedArrayStack;

void initLinkedArrayStack(LinkedArrayStack *s) {
    s->top = -1;
    s->free_head = 0;
    for (int i = 0; i < MAX - 1; i++) {
        s->nodes[i].next = i + 1;
    }
    s->nodes[MAX - 1].next = -1;
}

bool underflowLinkedArray(LinkedArrayStack *s) {
    return s->top == -1;
}

bool overflowLinkedArray(LinkedArrayStack *s) {
    return s->free_head == -1;
}

void pushLinkedArray(LinkedArrayStack *s, int val) {
    if (overflowLinkedArray(s)) {
        printf("Stack Overflow (Linked Array)\n");
        return;
    }
    int new_idx = s->free_head;
    s->free_head = s->nodes[s->free_head].next;
    
    s->nodes[new_idx].data = val;
    s->nodes[new_idx].next = s->top;
    s->top = new_idx;
}

int popLinkedArray(LinkedArrayStack *s) {
    if (underflowLinkedArray(s)) {
        printf("Stack Underflow (Linked Array)\n");
        return -1;
    }
    int popped_idx = s->top;
    int val = s->nodes[popped_idx].data;
    s->top = s->nodes[popped_idx].next;
    
    s->nodes[popped_idx].next = s->free_head;
    s->free_head = popped_idx;
    
    return val;
}

int main() {
    printf("--- Testing Array Stack ---\n");
    ArrayStack s1;
    initArrayStack(&s1);
    pushArray(&s1, 10);
    pushArray(&s1, 20);
    printf("Popped: %d\n", popArray(&s1));

    printf("\n--- Testing Dynamic Linked List Stack ---\n");
    ListStack s2;
    initListStack(&s2);
    pushList(&s2, 100);
    pushList(&s2, 200);
    printf("Popped: %d\n", popList(&s2));

    printf("\n--- Testing Linked Array Stack ---\n");
    LinkedArrayStack s3;
    initLinkedArrayStack(&s3);
    pushLinkedArray(&s3, 1000);
    pushLinkedArray(&s3, 2000);
    printf("Popped: %d\n", popLinkedArray(&s3));

    return 0;
}
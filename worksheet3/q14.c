#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct ArrayNode {
    int data;
    int next;
};

struct ArrayLinkedList {
    struct ArrayNode nodes[100];
    int head;
    int free_head;
};

void init_array_list(struct ArrayLinkedList* list) {
    list->head = -1;
    list->free_head = 0;
    for (int i = 0; i < 99; i++) {
        list->nodes[i].next = i + 1;
    }
    list->nodes[99].next = -1;
}

int allocate_array_node(struct ArrayLinkedList* list) {
    if (list->free_head == -1) return -1;
    int index = list->free_head;
    list->free_head = list->nodes[index].next;
    return index;
}

struct Node* create_pointer(int arr[], int n) {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    for (int i = 0; i < n; i++) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = arr[i];
        new_node->next = NULL;
        if (head == NULL) { head = new_node; tail = new_node; }
        else { tail->next = new_node; tail = new_node; }
    }
    return head;
}

int count_occurrences_pointer(struct Node* head, int key) {
    int count = 0;
    struct Node* curr = head;
    while (curr != NULL) {
        if (curr->data == key) count++;
        curr = curr->next;
    }
    return count;
}

void create_array(struct ArrayLinkedList* list, int arr[], int n) {
    int prev = -1;
    for (int i = 0; i < n; i++) {
        int idx = allocate_array_node(list);
        list->nodes[idx].data = arr[i];
        list->nodes[idx].next = -1;
        if (list->head == -1) list->head = idx;
        else list->nodes[prev].next = idx;
        prev = idx;
    }
}

int count_occurrences_array(struct ArrayLinkedList* list, int key) {
    int count = 0;
    int curr = list->head;
    while (curr != -1) {
        if (list->nodes[curr].data == key) count++;
        curr = list->nodes[curr].next;
    }
    return count;
}

void free_pointer_list(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    printf("=== TEST CASE Q14: Count Occurrences of Key Data ===\n");
    int arr[] = {1, 2, 2, 3, 2, 4, 2};
    struct Node* p_head = create_pointer(arr, 7);
    printf("Pointer Occurrences of 2: %d\n", count_occurrences_pointer(p_head, 2));

    struct ArrayLinkedList alist;
    init_array_list(&alist);
    create_array(&alist, arr, 7);
    printf("Array Occurrences of 2: %d\n", count_occurrences_array(&alist, 2));

    free_pointer_list(p_head);
    return 0;
}
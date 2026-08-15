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

int Josephus_pointer(int n, int k) {
    if (n <= 0 || k <= 0) return -1;
    
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->data = 1;
    struct Node* prev = head;

    for (int i = 2; i <= n; i++) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = i;
        prev->next = new_node;
        prev = new_node;
    }
    prev->next = head;

    struct Node* curr = head;
    struct Node* p_prev = prev;

    while (curr->next != curr) {
        for (int count = 1; count < k; count++) {
            p_prev = curr;
            curr = curr->next;
        }
        p_prev->next = curr->next;
        free(curr);
        curr = p_prev->next;
    }
    
    int survivor = curr->data;
    free(curr);
    return survivor;
}

int Josephus_array(int n, int k) {
    if (n <= 0 || k <= 0) return -1;

    struct ArrayLinkedList list;
    init_array_list(&list);

    int first_idx = allocate_array_node(&list);
    list.nodes[first_idx].data = 1;
    int prev = first_idx;

    for (int i = 2; i <= n; i++) {
        int idx = allocate_array_node(&list);
        list.nodes[idx].data = i;
        list.nodes[prev].next = idx;
        prev = idx;
    }
    list.nodes[prev].next = first_idx;

    int curr = first_idx;
    int p_prev = prev;

    while (list.nodes[curr].next != curr) {
        for (int count = 1; count < k; count++) {
            p_prev = curr;
            curr = list.nodes[curr].next;
        }
        list.nodes[p_prev].next = list.nodes[curr].next;
        curr = list.nodes[p_prev].next;
    }
    
    return list.nodes[curr].data;
}

int main() {
    printf("=== TEST CASE: Josephus Problem with Circular Linked List (n=7, k=3) ===\n");
    int survivor_p = Josephus_pointer(7, 3);
    printf("Pointer Representation Survivor: Person %d\n", survivor_p);

    int survivor_a = Josephus_array(7, 3);
    printf("Array Representation Survivor: Person %d\n", survivor_a);

    printf("\n=== TEST CASE: Josephus Problem Edge Case (n=1, k=1) ===\n");
    printf("Pointer Representation Survivor: Person %d\n", Josephus_pointer(1, 1));
    printf("Array Representation Survivor: Person %d\n", Josephus_array(1, 1));

    return 0;
}
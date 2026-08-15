#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct ArrayNode {
    int data;
    int prev;
    int next;
};

struct ArrayDLL {
    struct ArrayNode nodes[100];
    int head;
    int free_head;
};

void init_array_dll(struct ArrayDLL* list) {
    list->head = -1;
    list->free_head = 0;
    for (int i = 0; i < 99; i++) {
        list->nodes[i].next = i + 1;
    }
    list->nodes[99].next = -1;
}

int allocate_array_node(struct ArrayDLL* list) {
    if (list->free_head == -1) return -1;
    int index = list->free_head;
    list->free_head = list->nodes[index].next;
    return index;
}

void insert_DLL_pointer(struct Node** head, int data, int pos) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    if (pos == 1) {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
        return;
    }

    struct Node* curr = *head;
    int i = 1;
    while (curr->next != NULL && i < pos - 1) {
        curr = curr->next;
        i++;
    }

    new_node->next = curr->next;
    new_node->prev = curr;
    if (curr->next != NULL) {
        curr->next->prev = new_node;
    }
    curr->next = new_node;
}

void print_DLL_pointer(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d <-> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

void insert_DLL_array(struct ArrayDLL* list, int data, int pos) {
    int idx = allocate_array_node(list);
    list->nodes[idx].data = data;
    list->nodes[idx].prev = -1;
    list->nodes[idx].next = -1;

    if (list->head == -1) {
        list->head = idx;
        return;
    }

    if (pos == 1) {
        list->nodes[idx].next = list->head;
        list->nodes[list->head].prev = idx;
        list->head = idx;
        return;
    }

    int curr = list->head;
    int i = 1;
    while (list->nodes[curr].next != -1 && i < pos - 1) {
        curr = list->nodes[curr].next;
        i++;
    }

    list->nodes[idx].next = list->nodes[curr].next;
    list->nodes[idx].prev = curr;
    if (list->nodes[curr].next != -1) {
        list->nodes[list->nodes[curr].next].prev = idx;
    }
    list->nodes[curr].next = idx;
}

void print_DLL_array(struct ArrayDLL* list) {
    int curr = list->head;
    while (curr != -1) {
        printf("%d <-> ", list->nodes[curr].data);
        curr = list->nodes[curr].next;
    }
    printf("NULL\n");
}

void free_pointer_dll(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    printf("=== TEST CASE Q10: Doubly Linked List Insertions ===\n");
    struct Node* p_head = NULL;
    insert_DLL_pointer(&p_head, 10, 1);
    insert_DLL_pointer(&p_head, 30, 2);
    insert_DLL_pointer(&p_head, 20, 2);
    insert_DLL_pointer(&p_head, 5, 1);
    printf("Pointer DLL Variations (Beginning, End, Middle): ");
    print_DLL_pointer(p_head);

    struct ArrayDLL adll;
    init_array_dll(&adll);
    insert_DLL_array(&adll, 10, 1);
    insert_DLL_array(&adll, 30, 2);
    insert_DLL_array(&adll, 20, 2);
    insert_DLL_array(&adll, 5, 1);
    printf("Array DLL Variations (Beginning, End, Middle): ");
    print_DLL_array(&adll);

    free_pointer_dll(p_head);
    return 0;
}
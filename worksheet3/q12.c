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

void delete_node_pointer(struct Node* node_ptr) {
    if (node_ptr == NULL || node_ptr->next == NULL) return;
    struct Node* temp = node_ptr->next;
    node_ptr->data = temp->data;
    node_ptr->next = temp->next;
    free(temp);
}

void delete_node_array(struct ArrayLinkedList* list, int node_idx) {
    if (node_idx == -1 || list->nodes[node_idx].next == -1) return;
    int temp_idx = list->nodes[node_idx].next;
    list->nodes[node_idx].data = list->nodes[temp_idx].data;
    list->nodes[node_idx].next = list->nodes[temp_idx].next;
    list->nodes[temp_idx].next = list->free_head;
    list->free_head = temp_idx;
}

void print_pointer(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

void print_array(struct ArrayLinkedList* list) {
    int curr = list->head;
    while (curr != -1) {
        printf("%d -> ", list->nodes[curr].data);
        curr = list->nodes[curr].next;
    }
    printf("NULL\n");
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
    printf("=== TEST CASE Q12: Delete Node Without Head Pointer ===\n");
    struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n3 = (struct Node*)malloc(sizeof(struct Node));
    n1->data = 10; n1->next = n2;
    n2->data = 20; n2->next = n3;
    n3->data = 30; n3->next = NULL;

    printf("Pointer before deleting node (20): ");
    print_pointer(n1);
    delete_node_pointer(n2);
    printf("Pointer after deleting node (20): ");
    print_pointer(n1);

    struct ArrayLinkedList alist;
    init_array_list(&alist);
    int idx1 = allocate_array_node(&alist);
    int idx2 = allocate_array_node(&alist);
    int idx3 = allocate_array_node(&alist);
    alist.head = idx1;
    alist.nodes[idx1].data = 10; alist.nodes[idx1].next = idx2;
    alist.nodes[idx2].data = 20; alist.nodes[idx2].next = idx3;
    alist.nodes[idx3].data = 30; alist.nodes[idx3].next = -1;

    printf("Array before deleting node (20): ");
    print_array(&alist);
    delete_node_array(&alist, idx2);
    printf("Array after deleting node (20): ");
    print_array(&alist);

    free_pointer_list(n1);
    return 0;
}
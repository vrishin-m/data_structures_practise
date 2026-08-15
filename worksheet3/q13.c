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

void print_pointer(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

void swap_kth_pointer(struct Node* head, int k) {
    int n = 0;
    struct Node* curr = head;
    while (curr != NULL) {
        n++;
        curr = curr->next;
    }
    if (k > n || (2 * k - 1) == n) return;

    struct Node* p1 = head;
    for (int i = 1; i < k; i++) p1 = p1->next;

    struct Node* p2 = head;
    for (int i = 1; i < n - k + 1; i++) p2 = p2->next;

    int temp = p1->data;
    p1->data = p2->data;
    p2->data = temp;
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

void print_array(struct ArrayLinkedList* list) {
    int curr = list->head;
    while (curr != -1) {
        printf("%d -> ", list->nodes[curr].data);
        curr = list->nodes[curr].next;
    }
    printf("NULL\n");
}

void swap_kth_array(struct ArrayLinkedList* list, int k) {
    int n = 0;
    int curr = list->head;
    while (curr != -1) {
        n++;
        curr = list->nodes[curr].next;
    }
    if (k > n || (2 * k - 1) == n) return;

    int p1 = list->head;
    for (int i = 1; i < k; i++) p1 = list->nodes[p1].next;

    int p2 = list->head;
    for (int i = 1; i < n - k + 1; i++) p2 = list->nodes[p2].next;

    int temp = list->nodes[p1].data;
    list->nodes[p1].data = list->nodes[p2].data;
    list->nodes[p2].data = temp;
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
    printf("=== TEST CASE Q13: Swap Kth Node From Beginning With Kth Node From End ===\n");
    int arr[] = {1, 2, 3, 4, 5};
    struct Node* p_head = create_pointer(arr, 5);
    printf("Pointer before swap (k=2): ");
    print_pointer(p_head);
    swap_kth_pointer(p_head, 2);
    printf("Pointer after swap (k=2): ");
    print_pointer(p_head);

    struct ArrayLinkedList alist;
    init_array_list(&alist);
    create_array(&alist, arr, 5);
    printf("Array before swap (k=2): ");
    print_array(&alist);
    swap_kth_array(&alist, 2);
    printf("Array after swap (k=2): ");
    print_array(&alist);

    free_pointer_list(p_head);
    return 0;
}
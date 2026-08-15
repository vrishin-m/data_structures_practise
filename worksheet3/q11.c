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

struct Node* intersection_pointer(struct Node* head1, struct Node* head2) {
    struct Node* result = NULL;
    struct Node* tail = NULL;
    struct Node* p1 = head1;
    struct Node* p2 = head2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->data == p2->data) {
            struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
            new_node->data = p1->data;
            new_node->next = NULL;
            if (result == NULL) { result = new_node; tail = new_node; }
            else { tail->next = new_node; tail = new_node; }
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->data < p2->data) {
            p1 = p1->next;
        } else {
            p2 = p2->next;
        }
    }
    return result;
}

void print_pointer(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

struct ArrayLinkedList intersection_array(struct ArrayLinkedList* l1, struct ArrayLinkedList* l2) {
    struct ArrayLinkedList res;
    init_array_list(&res);
    int p1 = l1->head;
    int p2 = l2->head;
    int prev = -1;

    while (p1 != -1 && p2 != -1) {
        if (l1->nodes[p1].data == l2->nodes[p2].data) {
            int idx = allocate_array_node(&res);
            res.nodes[idx].data = l1->nodes[p1].data;
            res.nodes[idx].next = -1;
            if (res.head == -1) res.head = idx;
            else res.nodes[prev].next = idx;
            prev = idx;
            p1 = l1->nodes[p1].next;
            p2 = l2->nodes[p2].next;
        } else if (l1->nodes[p1].data < l2->nodes[p2].data) {
            p1 = l1->nodes[p1].next;
        } else {
            p2 = l2->nodes[p2].next;
        }
    }
    return res;
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
    printf("=== TEST CASE Q11: Intersection of Two Sorted Lists ===\n");
    int a1[] = {1, 3, 5, 7, 9};
    int a2[] = {3, 4, 5, 8, 9};

    struct Node* l1_p = create_pointer(a1, 5);
    struct Node* l2_p = create_pointer(a2, 5);
    struct Node* res_p = intersection_pointer(l1_p, l2_p);
    printf("Pointer Intersection: ");
    print_pointer(res_p);

    struct ArrayLinkedList l1_a, l2_a;
    init_array_list(&l1_a);
    init_array_list(&l2_a);
    create_array(&l1_a, a1, 5);
    create_array(&l2_a, a2, 5);
    struct ArrayLinkedList res_a = intersection_array(&l1_a, &l2_a);
    printf("Array Intersection: ");
    print_array(&res_a);

    free_pointer_list(l1_p);
    free_pointer_list(l2_p);
    free_pointer_list(res_p);
    return 0;
}
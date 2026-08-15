#include <stdio.h>
#include <stdlib.h>

enum DataType { INT_TYPE, FLOAT_TYPE };

union Value {
    int i;
    float f;
};

struct Node {
    enum DataType type;
    union Value val;
    struct Node* next;
};

struct ArrayNode {
    enum DataType type;
    union Value val;
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

float get_node_val(enum DataType type, union Value val) {
    return (type == INT_TYPE) ? (float)val.i : val.f;
}

struct Node* Create_sort_pointer(enum DataType types[], union Value vals[], int n) {
    struct Node* head = NULL;
    for (int i = 0; i < n; i++) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->type = types[i];
        new_node->val = vals[i];
        new_node->next = NULL;

        float new_v = get_node_val(new_node->type, new_node->val);
        if (head == NULL || get_node_val(head->type, head->val) >= new_v) {
            new_node->next = head;
            head = new_node;
        } else {
            struct Node* curr = head;
            while (curr->next != NULL && get_node_val(curr->next->type, curr->next->val) < new_v) {
                curr = curr->next;
            }
            new_node->next = curr->next;
            curr->next = new_node;
        }
    }
    return head;
}

void print_pointer_list(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        if (curr->type == INT_TYPE) printf("%d -> ", curr->val.i);
        else printf("%.2f -> ", curr->val.f);
        curr = curr->next;
    }
    printf("NULL\n");
}

void Create_sort_array(struct ArrayLinkedList* list, enum DataType types[], union Value vals[], int n) {
    for (int i = 0; i < n; i++) {
        int idx = allocate_array_node(list);
        list->nodes[idx].type = types[i];
        list->nodes[idx].val = vals[i];
        
        float new_v = get_node_val(types[i], vals[i]);
        if (list->head == -1 || get_node_val(list->nodes[list->head].type, list->nodes[list->head].val) >= new_v) {
            list->nodes[idx].next = list->head;
            list->head = idx;
        } else {
            int curr = list->head;
            while (list->nodes[curr].next != -1 && get_node_val(list->nodes[list->nodes[curr].next].type, list->nodes[list->nodes[curr].next].val) < new_v) {
                curr = list->nodes[curr].next;
            }
            list->nodes[idx].next = list->nodes[curr].next;
            list->nodes[curr].next = idx;
        }
    }
}

void print_array_list(struct ArrayLinkedList* list) {
    int curr = list->head;
    while (curr != -1) {
        if (list->nodes[curr].type == INT_TYPE) printf("%d -> ", list->nodes[curr].val.i);
        else printf("%.2f -> ", list->nodes[curr].val.f);
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
    printf("=== TEST CASE Q2: Create Sorted List (Mixed Int and Float Data) ===\n");
    enum DataType types[] = {INT_TYPE, FLOAT_TYPE, INT_TYPE, FLOAT_TYPE};
    union Value vals[4];
    vals[0].i = 15;
    vals[1].f = 4.5f;
    vals[2].i = 10;
    vals[3].f = 12.3f;

    struct Node* p_head = Create_sort_pointer(types, vals, 4);
    printf("Pointer Sorted List: ");
    print_pointer_list(p_head);

    struct ArrayLinkedList alist;
    init_array_list(&alist);
    Create_sort_array(&alist, types, vals, 4);
    printf("Array Sorted List: ");
    print_array_list(&alist);

    free_pointer_list(p_head);
    return 0;
}
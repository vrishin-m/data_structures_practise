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
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
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

int count_pointer(struct Node* head) {
    int count = 0;
    struct Node* curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

void modify_pointer(struct Node* head, int old_val, int new_val) {
    struct Node* curr = head;
    while (curr != NULL) {
        if (curr->data == old_val) {
            curr->data = new_val;
        }
        curr = curr->next;
    }
}

struct Node* search_pointer(struct Node* head, int key) {
    struct Node* curr = head;
    while (curr != NULL) {
        if (curr->data == key) return curr;
        curr = curr->next;
    }
    return NULL;
}

void search_prev_pointer(struct Node* head, int key, struct Node** key_node, struct Node** prev_node) {
    *key_node = NULL;
    *prev_node = NULL;
    struct Node* curr = head;
    struct Node* prev = NULL;
    while (curr != NULL) {
        if (curr->data == key) {
            *key_node = curr;
            *prev_node = prev;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void insert_after_pointer(struct Node* head, int data, int key) {
    struct Node* curr = head;
    while (curr != NULL) {
        if (curr->data == key) {
            struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
            new_node->data = data;
            new_node->next = curr->next;
            curr->next = new_node;
            return;
        }
        curr = curr->next;
    }
}

void insert_before_pointer(struct Node** head, int data, int key) {
    struct Node* curr = *head;
    struct Node* prev = NULL;
    while (curr != NULL) {
        if (curr->data == key) {
            struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
            new_node->data = data;
            if (prev == NULL) {
                new_node->next = *head;
                *head = new_node;
            } else {
                new_node->next = curr;
                prev->next = new_node;
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void insert_at_k_pointer(struct Node** head, int data, int k) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    if (k == 1) {
        new_node->next = *head;
        *head = new_node;
        return;
    }
    struct Node* curr = *head;
    for (int i = 1; curr != NULL && i < k - 1; i++) {
        curr = curr->next;
    }
    if (curr != NULL) {
        new_node->next = curr->next;
        curr->next = new_node;
    }
}

void insert_sorted_pointer(struct Node** head, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    if (*head == NULL || (*head)->data >= data) {
        new_node->next = *head;
        *head = new_node;
        return;
    }
    struct Node* curr = *head;
    while (curr->next != NULL && curr->next->data < data) {
        curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
}

void create_array(struct ArrayLinkedList* list, int arr[], int n) {
    int prev = -1;
    for (int i = 0; i < n; i++) {
        int idx = allocate_array_node(list);
        list->nodes[idx].data = arr[i];
        list->nodes[idx].next = -1;
        if (list->head == -1) {
            list->head = idx;
        } else {
            list->nodes[prev].next = idx;
        }
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

int count_array(struct ArrayLinkedList* list) {
    int count = 0;
    int curr = list->head;
    while (curr != -1) {
        count++;
        curr = list->nodes[curr].next;
    }
    return count;
}

void modify_array(struct ArrayLinkedList* list, int old_val, int new_val) {
    int curr = list->head;
    while (curr != -1) {
        if (list->nodes[curr].data == old_val) {
            list->nodes[curr].data = new_val;
        }
        curr = list->nodes[curr].next;
    }
}

int search_array(struct ArrayLinkedList* list, int key) {
    int curr = list->head;
    while (curr != -1) {
        if (list->nodes[curr].data == key) return curr;
        curr = list->nodes[curr].next;
    }
    return -1;
}

void search_prev_array(struct ArrayLinkedList* list, int key, int* key_idx, int* prev_idx) {
    *key_idx = -1;
    *prev_idx = -1;
    int curr = list->head;
    int prev = -1;
    while (curr != -1) {
        if (list->nodes[curr].data == key) {
            *key_idx = curr;
            *prev_idx = prev;
            return;
        }
        prev = curr;
        curr = list->nodes[curr].next;
    }
}

void insert_after_array(struct ArrayLinkedList* list, int data, int key) {
    int curr = list->head;
    while (curr != -1) {
        if (list->nodes[curr].data == key) {
            int idx = allocate_array_node(list);
            list->nodes[idx].data = data;
            list->nodes[idx].next = list->nodes[curr].next;
            list->nodes[curr].next = idx;
            return;
        }
        curr = list->nodes[curr].next;
    }
}

void insert_before_array(struct ArrayLinkedList* list, int data, int key) {
    int curr = list->head;
    int prev = -1;
    while (curr != -1) {
        if (list->nodes[curr].data == key) {
            int idx = allocate_array_node(list);
            list->nodes[idx].data = data;
            if (prev == -1) {
                list->nodes[idx].next = list->head;
                list->head = idx;
            } else {
                list->nodes[idx].next = curr;
                list->nodes[prev].next = idx;
            }
            return;
        }
        prev = curr;
        curr = list->nodes[curr].next;
    }
}

void insert_at_k_array(struct ArrayLinkedList* list, int data, int k) {
    int idx = allocate_array_node(list);
    list->nodes[idx].data = data;
    if (k == 1) {
        list->nodes[idx].next = list->head;
        list->head = idx;
        return;
    }
    int curr = list->head;
    for (int i = 1; curr != -1 && i < k - 1; i++) {
        curr = list->nodes[curr].next;
    }
    if (curr != -1) {
        list->nodes[idx].next = list->nodes[curr].next;
        list->nodes[curr].next = idx;
    }
}

void insert_sorted_array(struct ArrayLinkedList* list, int data) {
    int idx = allocate_array_node(list);
    list->nodes[idx].data = data;
    if (list->head == -1 || list->nodes[list->head].data >= data) {
        list->nodes[idx].next = list->head;
        list->head = idx;
        return;
    }
    int curr = list->head;
    while (list->nodes[curr].next != -1 && list->nodes[list->nodes[curr].next].data < data) {
        curr = list->nodes[curr].next;
    }
    list->nodes[idx].next = list->nodes[curr].next;
    list->nodes[curr].next = idx;
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
    printf("=== TEST CASE Q1: Pointer Representation (create, print, count, modify) ===\n");
    int init_data[] = {10, 20, 30, 40};
    struct Node* head = create_pointer(init_data, 4);
    print_pointer(head);
    printf("Node count: %d\n", count_pointer(head));
    modify_pointer(head, 30, 99);
    printf("After modifying 30 to 99: ");
    print_pointer(head);

    printf("\n=== TEST CASE Q1: Array Representation (create, print, count, modify) ===\n");
    struct ArrayLinkedList alist;
    init_array_list(&alist);
    create_array(&alist, init_data, 4);
    print_array(&alist);
    printf("Node count: %d\n", count_array(&alist));
    modify_array(&alist, 30, 99);
    printf("After modifying 30 to 99: ");
    print_array(&alist);

    printf("\n=== TEST CASE Q3: Search Key Node ===\n");
    struct Node* found = search_pointer(head, 20);
    printf("Pointer search for 20: %s\n", found ? "Found" : "Not Found");
    int arr_idx = search_array(&alist, 20);
    printf("Array search for 20: %s (Index: %d)\n", arr_idx != -1 ? "Found" : "Not Found", arr_idx);

    printf("\n=== TEST CASE Q4: Search Key and Previous Node ===\n");
    struct Node *k_node = NULL, *p_node = NULL;
    search_prev_pointer(head, 40, &k_node, &p_node);
    printf("Pointer Search 40: Key Data = %d, Prev Data = %d\n", k_node->data, p_node->data);
    int k_idx = -1, p_idx = -1;
    search_prev_array(&alist, 40, &k_idx, &p_idx);
    printf("Array Search 40: Key Data = %d, Prev Data = %d\n", alist.nodes[k_idx].data, alist.nodes[p_idx].data);

    printf("\n=== TEST CASE Q5: Insert After Key Node ===\n");
    insert_after_pointer(head, 25, 20);
    printf("Pointer after inserting 25 after 20: ");
    print_pointer(head);
    insert_after_array(&alist, 25, 20);
    printf("Array after inserting 25 after 20: ");
    print_array(&alist);

    printf("\n=== TEST CASE Q6: Insert Before Key Node ===\n");
    insert_before_pointer(&head, 15, 20);
    printf("Pointer after inserting 15 before 20: ");
    print_pointer(head);
    insert_before_array(&alist, 15, 20);
    printf("Array after inserting 15 before 20: ");
    print_array(&alist);

    printf("\n=== TEST CASE Q7: Insert at Position K ===\n");
    insert_at_k_pointer(&head, 5, 1);
    printf("Pointer after inserting 5 at pos 1: ");
    print_pointer(head);
    insert_at_k_array(&alist, 5, 1);
    printf("Array after inserting 5 at pos 1: ");
    print_array(&alist);

    printf("\n=== TEST CASE Q8: Insert into Sorted List ===\n");
    free_pointer_list(head);
    head = NULL;
    insert_sorted_pointer(&head, 30);
    insert_sorted_pointer(&head, 10);
    insert_sorted_pointer(&head, 20);
    printf("Pointer Sorted List: ");
    print_pointer(head);

    struct ArrayLinkedList sorted_alist;
    init_array_list(&sorted_alist);
    insert_sorted_array(&sorted_alist, 30);
    insert_sorted_array(&sorted_alist, 10);
    insert_sorted_array(&sorted_alist, 20);
    printf("Array Sorted List: ");
    print_array(&sorted_alist);

    free_pointer_list(head);
    return 0;
}
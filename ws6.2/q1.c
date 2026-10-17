#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node *left; 
    struct Node *right; 
} Node;


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


Node* findKthNode(Node* head, int k) {
    if (head == NULL || k <= 0) return NULL;

    Node* curr = head;
    for (int i = 1; i < k; i++) {
        curr = curr->right;
    }
    return curr;
}


void deleteKthNode(Node** head_ref, int k) {
    if (head_ref == NULL || *head_ref == NULL || k <= 0) return;

    Node* target = findKthNode(*head_ref, k);

    if (target->right == target && target->left == target) {
        *head_ref = NULL;
        free(target);
        return;
    }


    target->left->right = target->right;
    target->right->left = target->left;

    *head_ref = target->right;

    free(target);
}


int josephusProblem(int n, int k) {
    if (n <= 0 || k <= 0) return -1;

    Node* head = createNode(1);
    Node* prev = head;

    for (int i = 2; i <= n; i++) {
        Node* newNode = createNode(i);
        prev->right = newNode;
        newNode->left = prev;
        prev = newNode;
    }

    prev->right = head;
    head->left = prev;


    while (head != NULL && head->right != head) {
        deleteKthNode(&head, k);
    }

    int winner = head->data;
    free(head);
    return winner;
}

int main() {
    printf("=== Worksheet 6.2: Questions 1 & 2 ===\n\n");

    printf("--- Testing Linked List via Tree Nodes ---\n");
    Node* head = createNode(10);
    Node* n2 = createNode(20);
    Node* n3 = createNode(30);
    Node* n4 = createNode(40);

    head->right = n2; n2->left = head;
    n2->right = n3;   n3->left = n2;
    n3->right = n4;   n4->left = n3;
    n4->right = head; head->left = n4; 

    printf("Original circular list starting at head: 10 -> 20 -> 30 -> 40\n");

    Node* kNode = findKthNode(head, 3);
    printf("3rd node from head: %d\n", kNode ? kNode->data : -1);

    deleteKthNode(&head, 3); 
    printf("After deleting 3rd node, new head points to: %d\n", head->data);

    printf("\n--- Testing Josephus Problem ---\n");
    int N = 7, K = 3;
    int safePosition = josephusProblem(N, K);
    printf("Josephus Position for N = %d, K = %d is: %d\n", N, K, safePosition);

    return 0;
}
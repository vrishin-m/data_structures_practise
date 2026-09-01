#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;


Node* create_circular_list(int n) {
    if (n <= 0) return NULL;

    Node *head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    head->next = head; 

    Node *curr = head;
    for (int i = 2; i <= n; i++) {
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = head; 
        curr->next = new_node;
        curr = new_node;
    }

    return head;
}



void print_list(Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = head;
    printf("Circular List: ");

    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(back to head: %d)\n", head->data);
}

int josephus(Node **head, int k){
    Node *curr = *head;
    Node *prev= curr->next;
    int i;
    while (prev->next != curr){
        prev = prev->next;
    }

    while (prev != curr){
        for (i=1; i<k; i++){
            prev= curr;
            curr= curr->next;
        }

        Node *temp = curr;
        curr=curr->next;
        prev->next= curr;
        
        if (temp != *head){
            free(temp);
        }

        else {
            *head = temp->next;

        }
        print_list(*head);
    }
    printf("survivor: %d", prev->data);
    return prev->data;
    
}


int main() {
    int n = 5; 
    int k = 3; 

    Node *head = create_circular_list(n);
    print_list(head);
    josephus(&head, k);
    return 0;
}
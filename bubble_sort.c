/*i'll implement bubble sort on a linked list in C*/
#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int data;
    struct node *next;
} node;

void swap(node *n1){
    node *temp;
    temp = n1->next->next;
    n1->next->next = n1;
    n1->next = temp;
}

void print_list(node *head){
    node *temp;
    for(temp=head; temp != NULL; temp=temp->next){
        printf("%d \n", temp->data);
        }

}

int bubble_sort(node *head){
    int iters =0;
    int needs_sort;
    node *temp;
    node *nextnode;
    node *prev;

    do {
        iters +=1;
        needs_sort=0;
        temp = head;
        if (temp->data > temp->next->data){
            nextnode = temp->next;
            head = nextnode;
            temp->next = nextnode->next;
            nextnode->next = temp;
            needs_sort=1;
           
        }
    
        while (temp->next != NULL){
            nextnode = temp->next;

            if (temp->data > nextnode->data){
                

            }

            

        }
    }
    
    while (needs_sort);

    printf("sorted in %d iterations", iters);
    print_list(head);
    return 0;

}



int main(){
    node *head = malloc(sizeof(node));
    node *a= malloc(sizeof(node));
    node *b= malloc(sizeof(node));
    node*c= malloc(sizeof(node));
    head->data = 5;
    head->next = a;
    a->data = 3;
    a->next = b;
    b->data = 8;
    b->next =c;
    c->data = 6;
    c->next = NULL;
    print_list(head);
    bubble_sort(head);
}
/* question 1*/
#include <stdio.h>
#include <stdlib.h>


struct Node{
    int data;
    struct Node *next;
};


int print_list(struct Node *head){

    for(struct Node *temp = head; temp->next != NULL; temp = temp->next){
        printf("%d --->", temp->data);
        if (temp->next->next == NULL){
            printf("%d", temp->next->data);


        }
    }
    return 0;
}

int count(struct Node *head){
    int sum =0;
    for(struct Node *temp = head; temp->next != NULL; temp = temp->next){
        sum +=1;
        if (temp->next->next == NULL){
            sum+=1;
        }
    }
    return sum;
}

int modify(struct Node *head, int position, int new_value){
    int i =0;
    struct Node *temp = head;
    while (i <position){
        temp = temp->next;
        i++;

    };
    temp->data = new_value;
    return 0;

}


int main(){
    struct Node *head = malloc(sizeof(struct Node));
    struct Node *second = malloc(sizeof(struct Node));
    struct Node *third = malloc(sizeof(struct Node));
    head->data = 5;
    head->next = second;
    second->data = 20;
    second->next = third;
    third->data = 50;
    third->next = NULL;
    print_list(head);
    printf("\nsize of linked list: %d", count(head));
    modify(head, 1, 67);
    printf("\n");
    print_list(head);
    free(head);
    free(second);
    return 0;
    
    
}



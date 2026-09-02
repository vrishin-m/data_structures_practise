// queue as an array
#include <stdio.h>
#include <stdlib.h>
#define MAX 3

typedef struct {
    int data[MAX];
    int rear;
    int front;
} queue;

void print_queue(queue *q) {
    if (q->front == -1 ) {
        printf("Queue is empty.\n");
        return;
    }

    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }

    for (int i = q->rear; i <= q->front; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int push(queue *q, int elem){
    if (q->rear<MAX-1){
        q->rear++;
        q->data[q->rear]= elem;
        if (q->front ==-1){ q->front++;}
        return 0;
    }
    return -1;
}

int pop(queue *q){
    if (q->front !=-1 && q->rear > q->front){
        int output= q->data[q->front];
        q->front++;
        return output;

    }
    return -1;
}

int push_circular(queue *q, int elem){
    if ((q->rear +1) % MAX == q->front){
        return -1;
    }

    if (q->front ==-1){q->front++;}

    q->rear =( q->rear+1) % MAX;
    q->data[q->rear]= elem;
    return 0;
}

int pop_circular(queue *q){
    if (q->front !=-1 && q->rear- q->front != -1){
        int output= q->data[q->front];
        q->front++;
        return output;

    }
    return -1;

}

int main(){
    queue *q = malloc(sizeof(queue));
    q->front=-1;
    q->rear =-1;
    push(q,2);
    push(q,5);
    push(q,8);
    print_queue(q);
    pop_circular(q);
    print_queue(q);
    push_circular(q, 67);
    print_queue(q);

}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *disks;
    int top;
    int capacity;
    int name; 
} Stack;


Stack* createPeg(int capacity, int name) {
    Stack *peg = (Stack*)malloc(sizeof(Stack));
    peg->capacity = capacity;
    peg->top = -1;
    peg->name = name;
    peg->disks = (int*)malloc(capacity * sizeof(int));
    return peg;
}


void push(Stack *peg, int disk) {
    if (peg->top == peg->capacity - 1) return;
    peg->disks[++(peg->top)] = disk;
}


int pop(Stack *peg) {
    if (peg->top == -1) return -1;
    return peg->disks[(peg->top)--];
}


void moveDisk(Stack *fromPeg, Stack *toPeg) {
    int disk = pop(fromPeg);
    push(toPeg, disk);
    printf("Move disk %d from Peg %d to Peg %d\n", disk, fromPeg->name, toPeg->name);
}


void displayPegs(Stack *peg1, Stack *peg2, Stack *peg3) {
    printf("\n--- Current State ---\n");
    
    Stack *pegs[3] = {peg1, peg2, peg3};
    for (int p = 0; p < 3; p++) {
        printf("Peg %d: ", pegs[p]->name);
        for (int i = 0; i <= pegs[p]->top; i++) {
            printf("%d ", pegs[p]->disks[i]);
        }
        printf("\n");
    }
    printf("---------------------\n\n");
}

int hanoi(int n, Stack *source, Stack *target, Stack *aux) {
    if (n==1){
        moveDisk(source, target);
        return 0;
    }


    hanoi(n-1,source, aux, target);
    moveDisk(source, target);
    hanoi(n-1,aux, target, source);

}

int main() {
    int n = 5; 

    Stack *peg1 = createPeg(n, 1);
    Stack *peg2 = createPeg(n, 2);
    Stack *peg3 = createPeg(n, 3);


    for (int i = n; i >= 1; i--) {
        push(peg1, i);
    }

    printf("Initial Setup:");
    displayPegs(peg1, peg2, peg3);


    hanoi(n, peg1, peg3, peg2);

    printf("Final Setup:");
    displayPegs(peg1, peg2, peg3);

    return 0;
}
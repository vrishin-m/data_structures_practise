#include <stdio.h>
#include <math.h>

void moveDisk(char fromRod, char toRod, int disk) {
    printf("Move disk %d from rod %c to rod %c\n", disk, fromRod, toRod);
}

void Tower_NR(int n, char src, char dest, char aux) {
    int total_moves = pow(2, n) - 1;
    

    if (n % 2 == 0) {
        char temp = dest;
        dest = aux;
        aux = temp;
    }
    
    for (int i = 1; i <= total_moves; i++) {
        if (i % 3 == 1) {
 
            printf("Move %d: ", i);
            moveDisk(src, dest, (i & i - 1) == 0 ? 1 : 0); 
        } else if (i % 3 == 2) {

            printf("Move %d: ", i);
            moveDisk(src, aux, 0);
        } else if (i % 3 == 0) {

            printf("Move %d: ", i);
            moveDisk(aux, dest, 0);
        }
    }
}

int main() {
    int n = 3;
    printf("Non-Recursive Tower of Hanoi moves for %d disks:\n", n);
    Tower_NR(n, 'A', 'C', 'B');
    return 0;
}
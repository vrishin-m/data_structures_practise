#include <stdio.h>
#include <stdlib.h>

#define MAX 100


typedef struct {
    int arr[MAX];
    int size;
} heap;


void swap(heap* maxheap, int index){
    int temp = maxheap->arr[index];
    maxheap->arr[index] = maxheap->arr[(index-1)/2];
    maxheap->arr[(index-1)/2]= temp;
}


heap *heapify(int *arr){
    heap *max_heap = malloc(sizeof(heap));
    max_heap->size = 0;
    for (int i=0; arr[i] != NULL; i++){
        max_heap->arr[i] = arr[i];
        max_heap->size +=1;
    
    int curr = max_heap->size-1;
    int sorted =1;

    while (sorted && curr >0) { 
        sorted=0;
        if (max_heap->arr[curr] > max_heap->arr[(curr-1)/2]){
            swap(max_heap, curr);
            sorted =1;
        }
        curr= (curr-1)/2;
        
    }

    }
}
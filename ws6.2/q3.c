#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int size;
} Heap;

    
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void maxHeapifyDown(Heap *heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->arr[left] > heap->arr[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->arr[right] > heap->arr[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(&heap->arr[index], &heap->arr[largest]);
        maxHeapifyDown(heap, largest);
    }
}

void minHeapifyDown(Heap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&heap->arr[index], &heap->arr[smallest]);
        minHeapifyDown(heap, smallest);
    }
}

Heap* createMaxHeap(int inputArr[], int n) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = n;

    for (int i = 0; i < n; i++) {
        heap->arr[i] = inputArr[i];
    }

    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        maxHeapifyDown(heap, i);
    }

    return heap;
}

Heap* createMinHeap(int inputArr[], int n) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = n;

    for (int i = 0; i < n; i++) {
        heap->arr[i] = inputArr[i];
    }

    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        minHeapifyDown(heap, i);
    }

    return heap;
}


int delete_root(Heap *heap) {
    if (heap->size <= 0) {
        printf("Heap Underflow!\n");
        return -1;
    }

    int rootValue = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    maxHeapifyDown(heap, 0);

    return rootValue;
}


void heapSort(int arr[], int n, int SORT) {
    if (SORT == 1) {

        Heap *maxHeap = createMaxHeap(arr, n);
        for (int i = n - 1; i >= 0; i--) {
            arr[i] = delete_root(maxHeap);
        }
        free(maxHeap);
    } else if (SORT == 0) {

        Heap *minHeap = createMinHeap(arr, n);
        for (int i = 0; i < n; i++) {
            int minVal = minHeap->arr[0];
            minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
            minHeap->size--;
            minHeapifyDown(minHeap, 0);
            arr[i] = minVal;
        }
        free(minHeap);
    } else {
        printf("Invalid SORT flag! Pass 1 for Ascending, 0 for Descending.\n");
    }
}

// Utility to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf("Questions 3, 4, 5 & 6 \n\n");

    int rawData[] = {45, 12, 89, 34, 7, 63, 21};
    int n = sizeof(rawData) / sizeof(rawData[0]);

    printf("Original Data: ");
    printArray(rawData, n);

  
    Heap *maxH = createMaxHeap(rawData, n);
    printf("\nMax Heap Array: ");
    printArray(maxH->arr, maxH->size);


    Heap *minH = createMinHeap(rawData, n);
    printf("Min Heap Array: ");
    printArray(minH->arr, minH->size);

    int poppedRoot = delete_root(maxH);
    printf("\nDeleted Root from Max Heap: %d\n", poppedRoot);
    printf("Max Heap after delete_root: ");
    printArray(maxH->arr, maxH->size);


    int ascArray[] = {45, 12, 89, 34, 7, 63, 21};
    heapSort(ascArray, n, 1);
    printf("\nHeap Sort (SORT = 1, Ascending): ");
    printArray(ascArray, n);

    int descArray[] = {45, 12, 89, 34, 7, 63, 21};
    heapSort(descArray, n, 0);
    printf("Heap Sort (SORT = 0, Descending): ");
    printArray(descArray, n);

    free(maxH);
    free(minH);
    return 0;
}
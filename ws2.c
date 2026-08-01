/*question 1*/

#include <stdio.h>
#include <stdlib.h>

void insertSorted(int arr[], int *n, int *ptr)
{
    int i = *n - 1;
    while (i >= 0 && arr[i] > *ptr)
    {
        arr[i + 1] = arr[i];
        i--;
    }

    arr[i + 1] = *ptr;
    (*n)++;
}

int to_upper(char string[], int length){
    char *ptr = malloc(sizeof(char));
    int i;
    for (i =0; i<length; i++){
        if (*(string + i) <= 'z'&& *(string +i)>='a'){
            string[i] -=32;
        }
    
    }
    printf("%s", string);
    return 0;
    
}


int reverse_string(char string[], int length){
    char temp;
    int i;

    for (i=0; i<length/2;i++){
        temp = string[i];
        string[i]= string[length-i-1];
        string[length-i-1]= temp;

    }

    
    printf("%s", string);
}

int rotate_array(int arr[], int length, int rotate_by){
    int i;
    int temp;
    int new_pos;
    int *new_arr= malloc(length*sizeof(int));
    for (i=0;i<length;i++){
        new_pos = i+rotate_by;
        if (new_pos>=length){
            new_pos -=length;
        }
        if (new_pos <0){
            new_pos += length;
        }

        new_arr[new_pos]= arr[i];

    }

    for (i=0;i<length;i++){
        printf("%d", new_arr[i]);
    }
        
}



int main()
{
    int arr[10] = {10, 20, 30, 40, 50};
    int n = 5;
    int value = 35;

    insertSorted(arr, &n, &value);

    printf("Array after insertion:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);


    /*question 2*/
    int *ptr2 = (int *)malloc(sizeof(int)*10);
    int *ptr3 = (int *)calloc(5, sizeof(int)*10);
    
    /* making it longer*/
    ptr2 = (int *)realloc(ptr2, sizeof(int));

    char string[] = "udhay";
    printf("%s \n", string);
    to_upper(string, 5);
    char string2[] ="sanjay";
    reverse_string(string, 5);
    
    int arr2[] ={1,2,3,4};
    rotate_array(arr2,4,-1);
    return 0;
}
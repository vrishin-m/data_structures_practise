//going to implement infix to postfix and prefix using stack in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int top;
    char array[100];
} stack;

void push(stack *s, char elem){
    if (s->top<100){
        s->top++;
        s->array[s->top]= elem;
    }
}

void pop(stack *s){
    if (s->top>0){
        s->top--;
    }
}

int precedence(c){
    if (c=="^"){
        return 3;
    }
    else if (c=="*" || c=="/"){
        return 2;
    }
    else if (c=="+" || c=="-"){
        return 1;
    }
    else {
        return -1;
    }

}

int postfix(char *str, char *new_str){
    int i;
    int j =0;
    stack *s;
    s->top =-1;

    for (i=0; str[i] != "\0"; i++){
        if (isalnum(str[i])){
            j++;
            new_str[j]=str[i];
        }

        else if (str[i]=="("){
            push(s, str[i]);
        }

        else if (str[i]==")"){
            while (s->array[s->top] !="("){
                pop(s);
                j++;
                new_str[j]= s->array[s->top];
            }
        }

        else{
            
        }


    }
}

int main(){
    char infix[] = "(1+3)*5";
    char output[100];
    postfix(infix,output);

}
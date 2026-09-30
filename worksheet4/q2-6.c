#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100


typedef struct {
    char items[MAX];
    int top;
} CharStack;

void initCStack(CharStack *s) { s->top = -1; }
int isCEmpty(CharStack *s) { return s->top == -1; }
void pushC(CharStack *s, char c) { s->items[++(s->top)] = c; }
char popC(CharStack *s) { return s->items[(s->top)--]; }
char peekC(CharStack *s) { return s->items[s->top]; }


typedef struct {
    int items[MAX];
    int top;
} IntStack;

void initIStack(IntStack *s) { s->top = -1; }
int isIEmpty(IntStack *s) { return s->top == -1; }
void pushI(IntStack *s, int val) { s->items[++(s->top)] = val; }
int popI(IntStack *s) { return s->items[(s->top)--]; }


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return (int)pow(a, b);
    }
    return 0;
}

// Q2: Infix to Postfix
void INF_T_PostF(const char *infix, char *postfix) {
    CharStack s;
    initCStack(&s);
    int k = 0;
    
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        if (isalnum(ch)) {
            postfix[k++] = ch;
        } else if (ch == '(') {
            pushC(&s, ch);
        } else if (ch == ')') {
            while (!isCEmpty(&s) && peekC(&s) != '(') {
                postfix[k++] = popC(&s);
            }
            popC(&s); // remove '('
        } else {
            while (!isCEmpty(&s) && precedence(peekC(&s)) >= precedence(ch)) {
                postfix[k++] = popC(&s);
            }
            pushC(&s, ch);
        }
    }
    while (!isCEmpty(&s)) {
        postfix[k++] = popC(&s);
    }
    postfix[k] = '\0';
}

// Q3: Evaluate Postfix
int PostFE_Value(const char *postfix) {
    IntStack s;
    initIStack(&s);
    
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            pushI(&s, ch - '0');
        } else {
            int val2 = popI(&s);
            int val1 = popI(&s);
            pushI(&s, applyOp(val1, val2, ch));
        }
    }
    return popI(&s);
}

// Q4: Infix to Prefix
void INF_T_PreF(const char *infix, char *prefix) {
    int len = strlen(infix);
    char rev[MAX];
    int k = 0;
    
    for (int i = len - 1; i >= 0; i--) {
        if (infix[i] == '(') rev[k++] = ')';
        else if (infix[i] == ')') rev[k++] = '(';
        else rev[k++] = infix[i];
    }
    rev[k] = '\0';
    
    char tempPostfix[MAX];
    CharStack s;
    initCStack(&s);
    int j = 0;
    
    for (int i = 0; rev[i]; i++) {
        char ch = rev[i];
        if (isalnum(ch)) {
            tempPostfix[j++] = ch;
        } else if (ch == '(') {
            pushC(&s, ch);
        } else if (ch == ')') {
            while (!isCEmpty(&s) && peekC(&s) != '(') {
                tempPostfix[j++] = popC(&s);
            }
            popC(&s);
        } else {
            while (!isCEmpty(&s) && precedence(peekC(&s)) > precedence(ch)) {
                tempPostfix[j++] = popC(&s);
            }
            pushC(&s, ch);
        }
    }
    while (!isCEmpty(&s)) {
        tempPostfix[j++] = popC(&s);
    }
    tempPostfix[j] = '\0';
    

    int pLen = strlen(tempPostfix);
    for (int i = 0; i < pLen; i++) {
        prefix[i] = tempPostfix[pLen - 1 - i];
    }
    prefix[pLen] = '\0';
}

// Q5: Evaluate Prefix
int PreFE_Value(const char *prefix) {
    IntStack s;
    initIStack(&s);
    int len = strlen(prefix);
    
    for (int i = len - 1; i >= 0; i--) {
        char ch = prefix[i];
        if (isdigit(ch)) {
            pushI(&s, ch - '0');
        } else {
            int val1 = popI(&s);
            int val2 = popI(&s);
            pushI(&s, applyOp(val1, val2, ch));
        }
    }
    return popI(&s);
}

// Q6: Main program
int main() {
    char infix[MAX], postfix[MAX], prefix[MAX];
    
    printf("Enter a valid Infix expression (single digits operands, e.g., (2+3)*4): ");
    scanf("%s", infix);
    
    INF_T_PostF(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);
    
    int postfixResult = PostFE_Value(postfix);
    printf("Value of Postfix Expression: %d\n", postfixResult);
    
    INF_T_PreF(infix, prefix);
    printf("\nPrefix Expression: %s\n", prefix);
    
    int prefixResult = PreFE_Value(prefix);
    printf("Value of Prefix Expression: %d\n", prefixResult);

    return 0;
}
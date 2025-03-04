#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack using Array
typedef struct {
    char items[MAX][MAX]; // Stack now stores strings instead of chars
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, const char *str) {
    if (!isFull(s)) {
        strcpy(s->items[++(s->top)], str);
    }
}

char *pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return "";
}

char *peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return "";
}

// Function to check operator precedence
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

// Function to check if character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to check if character is alphanumeric
int isAlnum(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Reverse a string
void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Convert Infix to Prefix
void infixToPrefix(char *infix, char *prefix) {
    Stack s;
    initStack(&s);
    reverse(infix);

    int j = 0;
    for (int i = 0; i < strlen(infix); i++) {
        char c = infix[i];

        if (isAlnum(c)) {
            prefix[j++] = c;
        } else if (c == ')') {
            push(&s, ")");
        } else if (c == '(') {
            while (!isEmpty(&s) && strcmp(peek(&s), ")") != 0) {
                prefix[j++] = pop(&s)[0];
            }
            pop(&s); // Remove ')'
        } else if (isOperator(c)) {
            while (!isEmpty(&s) && precedence(peek(&s)[0]) >= precedence(c)) {
                prefix[j++] = pop(&s)[0];
            }
            char op[2] = {c, '\0'};
            push(&s, op);
        }
    }

    while (!isEmpty(&s)) {
        prefix[j++] = pop(&s)[0];
    }
    prefix[j] = '\0';
    reverse(prefix);
}

// Convert Prefix to Infix
void prefixToInfix(char *prefix, char *infix) {
    Stack s;
    initStack(&s);
    reverse(prefix);

    for (int i = 0; i < strlen(prefix); i++) {
        char c = prefix[i];

        if (isAlnum(c)) {
            char operand[2] = {c, '\0'};
            push(&s, operand);
        } else if (isOperator(c)) {
            char op1[MAX], op2[MAX], expr[MAX];
            strcpy(op1, pop(&s));
            strcpy(op2, pop(&s));
            sprintf(expr, "(%s%c%s)", op1, c, op2);
            push(&s, expr);
        }
    }
    strcpy(infix, pop(&s));
}

int main() {
    char infix[MAX], prefix[MAX], infixConverted[MAX];
    
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);
    
    prefixToInfix(prefix, infixConverted);
    printf("Converted back to Infix: %s\n", infixConverted);
    
    return 0;
}


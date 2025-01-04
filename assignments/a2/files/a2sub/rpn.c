#include <stdio.h>
#include <stdlib.h>

//code from lecture
void push(int **p, size_t *len, size_t *cap, int val) {
    if (*len == *cap) {
        int *newArr = malloc(*cap * sizeof(int) * 2);
        if (newArr == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < *len; ++i) {
            newArr[i] = (*p)[i];
        }
        free(*p);
        *p = newArr;
        *cap = *cap * 2;
    }
    int *arr = *p;
    arr[(*len)++] = val;
}
//code from lecture
int pop(int **p, size_t *len) {
    if (*len > 0) {
        return (*p)[--*len];
    } else {
        fprintf(stderr, "Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
}

//recognize operators and perform those operations accordingly
int operation(int a, int b, char ops) {
    if (ops == 'p') {
        return a + b;
    } else if (ops == '*') {
        return a * b;
    } else if (ops == 's') {
        return a - b;
    } else if (ops == '/') {
        if (b != 0) {
            return a / b;
        } else {
            fprintf(stderr, "Floating point exception\n"); //if dividing by zero
            return 0;
        }
    } else {
        fprintf(stderr, "Invalid input invalid operator %c\n", ops); //if user enters something other than p/s/*//
        exit(EXIT_FAILURE);
    }
}

int main() {
    size_t cap = 4; //initialising capacity to 4
    size_t len = 0;

    char ops;
    int operand;

    int *arr = malloc(sizeof(int) * cap);
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if (scanf(" %c", &ops) == EOF) {
            break;  // Exit the loop on EOF
        }

        if (ops == 'p' || ops == 's' || ops == '*' || ops == '/') {
            if (len >= 2) { // need at least 2 operands to perform operation
                int b = pop(&arr, &len);
                int a = pop(&arr, &len);
                int result = operation(a, b, ops);
                push(&arr, &len, &cap, result);
            }
        } else {
            ungetc(ops, stdin);  // Put back the non-operator character
            if (scanf("%d", &operand) == 1) {
                push(&arr, &len, &cap, operand); // push the int onto the stack
            } else {
                fprintf(stderr, "Invalid input\n");
                break;
            }
        }
    }

    // final result
    if (len == 1) {
        printf("%d\n", arr[0]);
    } else {
        fprintf(stderr, "Invalid expression.\n");
    }

    // Free dynamically allocated memory
    free(arr);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 256

int *stack = (int*) malloc(STACK_SIZE * sizeof(int)),
    *top   = stack,
    *curr  = stack;

void push(int val) {
    // push new action
    if (curr >= stack + STACK_SIZE) {
        fprintf(stderr, "Stack overflow\n");
        return;
    }
    *(++curr) = val;
    top = curr;
}

// todo...
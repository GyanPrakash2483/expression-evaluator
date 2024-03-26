#include <stack.h>
#include <stdlib.h>

stack_char initStackChar() {
    stack_char newstack;
    newstack.top = 0;
    newstack.stack = (char *)malloc(100 * sizeof(char));

    return newstack;
}

stack_int initStackInt() {
    stack_int newstack;
    newstack.top = 0;
    newstack.stack = (int *)malloc(100 * sizeof(int));

    return newstack;
}

void stackCharPush(stack_char *stack, char topush) {
    stack->stack[stack->top] = topush;
    (stack->top)++;
}

void stackIntPush(stack_int *stack, int topush) {
    stack->stack[stack->top] = topush;
    (stack->top)++;
}

char stackCharPop(stack_char *stack) {
    (stack->top)--;
    return stack->stack[stack->top];
}

int stackIntPop(stack_int *stack) {
    (stack->top)--;
    return stack->stack[stack->top];
}

char stackCharTop(stack_char stack) {
    return stack.stack[stack.top-1];
}

int stackIntTop(stack_int stack) {
    return stack.stack[stack.top-1];
}

bool stackCharIsEmpty(stack_char stack) {
    return (stack.top == 0);
}

bool stackIntIsEmpty(stack_int stack) {
    return (stack.top == 0);
}

void stackCharDestruct(stack_char* stack) {
    free(stack->stack);
}

void stackIntDestruct(stack_int* stack) {
    free(stack->stack);
}

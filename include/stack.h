#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stchar {
    char* stack;
    int top;
} stack_char;

typedef struct stint {
    int* stack;
    int top;
} stack_int;

stack_char initStackChar();
stack_int initStackInt();
void stackCharPush(stack_char *stack, char topush);
void stackIntPush(stack_int *stack, int topush);
char stackCharPop(stack_char *stack);
int stackIntPop(stack_int *stack);
char stackCharTop(stack_char stack);
int stackIntTop(stack_int stack);
bool stackCharIsEmpty(stack_char stack);
bool stackIntIsEmpty(stack_int stack);
void stackCharDestruct(stack_char* stack);
void stackIntDestruct(stack_int* stack);

#endif
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdbool.h>

typedef struct tkn {
    bool isOperator;
    char operator;
    int operand;    
} token;

typedef struct tkn_exp {
    token* expression;
    int length;
} expression;

expression initExpression();
void insertOperator(expression* expr, char op);
void insertDigit(expression* expr, int d);
void insertNumber(expression* expr, int num);
bool isOperator(char op);
expression tokenizeExpression(char *expression_string);
void printExpression(expression expr);
void destructExpression(expression *todestroy);

#endif
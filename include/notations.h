#ifndef NOTATIONS_H
#define NOTATIONS_H

#include <expression.h>

int precedence(char op);
char associativity(char op);
void validateInfix(expression infix);
expression infixToPostfix(expression infix);
expression infixToPrefix(expression infix);
int evaluatePostfix(expression postfix);


#endif
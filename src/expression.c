#include <expression.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

expression initExpression() {
    expression newexpression;
    newexpression.expression = (token *)malloc(100 * sizeof(token));
    newexpression.length = 0;
    newexpression.expression[0].operand = 0;
    return newexpression;
}

void insertOperator(expression* expr, char op) {
    expr->expression[expr->length].operator = op;
    expr->expression[expr->length].isOperator = true;
    (expr->length)++;
}

void insertDigit(expression* expr, int d) {
    if(expr->length == 0) {
        expr->expression[expr->length].operand = d;
        expr->expression[expr->length].isOperator = false;
        (expr->length)++;
    } else if(expr->expression[expr->length-1].isOperator) {
        expr->expression[expr->length].operand = d;
        expr->expression[expr->length].isOperator = false;
        (expr->length)++;
    } else {
        expr->expression[expr->length-1].operand *= 10;
        expr->expression[expr->length-1].operand += d;
    }
}

void insertNumber(expression* expr, int num) {
    expr->expression[expr->length].operand = num;
    expr->expression[expr->length].isOperator = false;
    (expr->length)++;
}

bool isOperator(char op) {
    if(op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '(' || op == ')') {
        return true;
    } else {
        return false;
    }
}



expression tokenizeExpression(char *expression_string) {

    for(int i = 0; expression_string[i] != '\0'; i++) {
        if(expression_string[i] == ' ') {
            for(int j = i; expression_string[j] != '\0'; j++) {
                expression_string[j] = expression_string[j+1];
            }
        } else if(expression_string[i] == '{' || expression_string[i] == '[') {
            expression_string[i] = '(';
        } else if(expression_string[i] == '}' || expression_string[i] == ']') {
            expression_string[i] = ')';
        } else if((expression_string[i] >= 'a' && expression_string[i] <= 'z') || (expression_string[i] >= 'Z' && expression_string[i] <= 'Z')) {
            printf("Invalid token: '%c', only numerical expressions can be evaluated\n", expression_string[i]);
            exit(1);
        }
    }

    expression tokenized_expression = initExpression();
    for(int i = 0; expression_string[i] != '\0'; i++) {
        if(i != 0 && expression_string[i] == '(' && !isOperator(expression_string[i-1])){
            insertOperator(&tokenized_expression, '*');
        }
        if(isOperator(expression_string[i])) {
            insertOperator(&tokenized_expression, expression_string[i]);
        } else {
            insertDigit(&tokenized_expression, (int)(expression_string[i]-'0'));
        }
    }
    return tokenized_expression;
}

void printExpression(expression expr) {
    for(int i = 0; i < expr.length; i++) {
        if(expr.expression[i].isOperator) {
            printf("%c ", expr.expression[i].operator);
        } else {
            printf("%d ", expr.expression[i].operand);
        }
    }
    printf("\n");
}

void destructExpression(expression *todestroy) {
    free(todestroy->expression);
}

#include <notations.h>
#include <expression.h>
#include <stack.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int precedence(char op) {
    if(op == '^') {
        return 2;
    } else if(op == '*' || op == '/') {
        return 1;
    } else if(op == '+' || op == '-') {
        return 0;
    } else {
        return -1;
    }
}

char associativity(char op) {
    if(op == '^') {
        return 'R';
    } else {
        return 'L';
    }
}

void validateInfix(expression infix) {

    bool prevOp = true;
    stack_char stack = initStackChar();
    
    for(int i = 0; i < infix.length; i++) {
        token current_token = infix.expression[i];
        if(current_token.isOperator && current_token.operator == '(') {
            stackCharPush(&stack, '(');
        } else if (current_token.isOperator && current_token.operator == ')') {
            if(stackCharIsEmpty(stack)) {
                printf("Invalid Expression: Mismatching Paranthesis\n");
                exit(1);
            } else {
                stackCharPop(&stack);
            }
        } else if(current_token.isOperator) {
            if(prevOp) {
                printf("Invalid Expression: Expected operand before and after a binary operator\n");
                exit(1);
            } else {
                prevOp = true;
            }
        } else {
            prevOp = false;
        }
    }
    if(!stackCharIsEmpty(stack)) {
        printf("Invalid Expression: Mismatching Paranthesis\n");
        exit(1);
    }
    if(infix.expression[0].isOperator && infix.expression[0].operator != '(' && infix.expression[0].operator != ')') {
        printf("Invalid Expression: Expected operand before and after a binary operator\n");
        exit(1);
    } else if(infix.expression[infix.length-1].isOperator && (infix.expression[infix.length-1].operator != '(' || infix.expression[infix.length-1].operator != ')')) {
        printf("Invalid Expression: Expected operand before and after a binary operator\n");
        exit(1);
    }


    stackCharDestruct(&stack);
}

expression infixToPostfix(expression infix) {
    expression postfix = initExpression();
    stack_char stack = initStackChar();

    for(int i = 0; i < infix.length; i++) {
        token current_token = infix.expression[i];

        if(!current_token.isOperator) {
            insertNumber(&postfix, current_token.operand);
        } else if(current_token.operator == '(') {
            stackCharPush(&stack, '(');
        } else if(current_token.operator == ')') {
            while(stackCharTop(stack) != '(') {
                insertOperator(&postfix, stackCharPop(&stack));
            }
            stackCharPop(&stack);
        } else if(stackCharIsEmpty(stack) || stackCharTop(stack) == '(') {
            stackCharPush(&stack, current_token.operator);
        } else if(precedence(current_token.operator) > precedence(stackCharTop(stack))) {
            stackCharPush(&stack, current_token.operator);
        } else if(precedence(current_token.operator) < precedence(stackCharTop(stack))) {
            while(precedence(current_token.operator) < precedence(stackCharTop(stack))) {
                insertOperator(&postfix, stackCharPop(&stack));
            }
            stackCharPush(&stack, current_token.operator);
        } else if(precedence(current_token.operator) == precedence(stackCharTop(stack))) {
            if(associativity(current_token.operator) == 'L') {
                insertOperator(&postfix, stackCharPop(&stack));
                stackCharPush(&stack, current_token.operator);
            } else {
                stackCharPush(&stack, current_token.operator);
            }
        }
    }

    while(!stackCharIsEmpty(stack)) {
        insertOperator(&postfix, stackCharPop(&stack));
    }

    stackCharDestruct(&stack);

    return postfix;
}

expression infixToPrefix(expression infix) {
    expression prefix = initExpression();
    stack_char stack = initStackChar();

    for(int i = infix.length-1; i >= 0; i--) {
        token current_token = infix.expression[i];

        if(!current_token.isOperator) {
            insertNumber(&prefix, current_token.operand);
        } else if (current_token.operator == ')') {
            stackCharPush(&stack, ')');
        } else if (current_token.operator == '(') {
            while(stackCharTop(stack) != ')') {
                insertOperator(&prefix, stackCharPop(&stack));
            }
            stackCharPop(&stack);
        } else {
            if(stackCharIsEmpty(stack)) {
                stackCharPush(&stack, current_token.operator);
            } else if (precedence(current_token.operator) > precedence(stackCharTop(stack))) {
                stackCharPush(&stack, current_token.operator);
            } else if(precedence(current_token.operator) == precedence(stackCharTop(stack)) && associativity(current_token.operator) == 'R') {
                while(precedence(current_token.operator) == precedence(stackCharTop(stack)) && associativity(current_token.operator) == 'R') {
                    insertOperator(&prefix, stackCharPop(&stack));
                }
                stackCharPush(&stack, current_token.operator);
            } else if(precedence(current_token.operator) == precedence(stackCharTop(stack))) {
                stackCharPush(&stack, current_token.operator);
            } else if(precedence(current_token.operator) < precedence(stackCharTop(stack))) {
                while(!stackCharIsEmpty(stack) && precedence(current_token.operator) < precedence(stackCharTop(stack))) {
                    insertOperator(&prefix, stackCharPop(&stack));
                }
                stackCharPush(&stack, current_token.operator);
            }
        }
    }

    while(!stackCharIsEmpty(stack)) {
        insertOperator(&prefix, stackCharPop(&stack));
    }

    for(int i = 0; i < prefix.length/2; i++) {
        token temp = prefix.expression[i];
        prefix.expression[i] = prefix.expression[prefix.length - i - 1];
        prefix.expression[prefix.length - i - 1] = temp;
    }

    stackCharDestruct(&stack);

    return prefix;

}

int evaluatePostfix(expression postfix) {
    stack_int stack = initStackInt();

    for(int i = 0; i < postfix.length; i++) {
        token current_token = postfix.expression[i];

        if(current_token.isOperator) {
            int right_operand = stackIntPop(&stack);
            int left_operand = stackIntPop(&stack);
            int result;
            if(current_token.operator == '+') {
                result = left_operand + right_operand;
            } else if (current_token.operator == '-') {
                result = left_operand - right_operand;
            } else if (current_token.operator == '*') {
                result = left_operand * right_operand;
            } else if (current_token.operator == '/') {
                result = left_operand - right_operand;
            } else if (current_token.operator == '^') {
                result = pow(left_operand, right_operand);
            }

            stackIntPush(&stack, result);
        } else {
            stackIntPush(&stack, current_token.operand);
        }
    }

    int result = stackIntPop(&stack);

    stackIntDestruct(&stack);

    return result;
}
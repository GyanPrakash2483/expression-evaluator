#include <expression.h>
#include <stack.h>
#include <notations.h>
#include <stdio.h>

int main() {
    printf("Enter expression(infix): ");
    char expression_string[100];
    scanf("%[^\n]s", expression_string);

    expression tokenized_expression = tokenizeExpression(expression_string);

    printf("\nInfix expression:\n");
    printExpression(tokenized_expression);

    validateInfix(tokenized_expression);

    expression postfix = infixToPostfix(tokenized_expression);
    printf("\nPostfix Expression:\n");
    printExpression(postfix);

    expression prefix = infixToPrefix(tokenized_expression);
    printf("\nPrefix Expression:\n");
    printExpression(prefix);

    int eval = evaluatePostfix(postfix);
    printf("\nEvaluation: %d\n", eval);

    //Memory cleanup
    destructExpression(&tokenized_expression);
    destructExpression(&postfix);
    destructExpression(&prefix);

    return 0;
}

/*
TODO:

- Add expression invalidation checks

*/
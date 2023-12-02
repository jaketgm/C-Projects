#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"
#include "queue.h"

/******************************************************************************
 * @author Jake Brockbank
 * Dec 2nd, 2023
 * Calculates a methematical expression through the use of a stack and queue
 * utilizing infix to postfix conversion.
*******************************************************************************/

void infixToPostfix(stack *opStack, queue *outQueue, const char *infix);
int evaluate(queue *postfixQueue);
int getPrec(char op);
int operate(int a, int b, char op);
void freeStack(stack *s);
void freeQueue(queue *q);   

/******************************************************************************
 * Method: main: 
 * 
 * - Creates a stack (opStack) and a queue (postfixQueue) for processing
 * the mathematical expressions.
 * - Prompts the user to input an infix mathematical expression and reads 
 * it into the infixExpr buffer. It also trims the newline character 
 * from the input.
 * - The user's infix expression is converted to postfix notation 
 * using infixToPostfix, with the stack handling operators and the 
 * queue storing the postfix expression.
 * - The postfix expression is evaluated to a single result using the 
 * evaluate function.
 * - The calculated result of the expression is printed.
 * - Frees the memory allocated for the stack and queue.
 *
 * Input: None.
 *
 * Output: Result of the expression.
 *
******************************************************************************/
int main() 
{
    stack *opStack = createStack();
    queue *postfixQueue = createQueue();

    // Define a buffer for the input expression
    char infixExpr[256];

    printf("Enter an infix expression: ");
    if (fgets(infixExpr, sizeof(infixExpr), stdin) == NULL) 
    {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove newline character if present
    infixExpr[strcspn(infixExpr, "\n")] = 0;

    infixToPostfix(opStack, postfixQueue, infixExpr);

    int result = evaluate(postfixQueue);

    printf("Result: %d\n", result);

    freeStack(opStack);
    freeQueue(postfixQueue);

    return 0;
}

/******************************************************************************
 * Method: infixToPostfix: 
 * 
 * - Converts an infix mathematical expression to postfix notation.
 *
 * Input: stack *opStack, queue *outQueue, const char *infix.
 *
 * Output: Converted expression.
 *
******************************************************************************/
void infixToPostfix(stack *opStack, queue *outQueue, const char *infix) 
{
    int i = 0;
    char current;
    char numberBuffer[16]; // Buffer to hold multi-digit numbers as strings
    int numberIndex = 0;

    while ((current = infix[i++]) != '\0') 
    {
        if (isdigit(current)) {
            // Start collecting the number in the buffer
            numberBuffer[numberIndex++] = current;
            // Look ahead to see if the next character is also a digit
            while (isdigit(infix[i])) 
            {
                numberBuffer[numberIndex++] = infix[i++];
            }
            numberBuffer[numberIndex] = '\0';
            enqueue(outQueue, atoi(numberBuffer)); // Convert to integer and enqueue
            numberIndex = 0; // Reset the index for the next number
        } 
        else if (isspace(current)) 
        {
            continue;
        } 
        else if (current == '(') 
        {
            push(opStack, current);
        } 
        else if (current == ')') 
        {
            while (!isEmptyStack(opStack) && peekStack(opStack) != '(') 
            {
                enqueue(outQueue, pop(opStack));
            }
            pop(opStack); // Discard the '(' from the stack
        } 
        else 
        {
            while (!isEmptyStack(opStack) && getPrec(peekStack(opStack)) >= getPrec(current)) 
            {
                enqueue(outQueue, pop(opStack));
            }
            push(opStack, current);
        }
    }

    while (!isEmptyStack(opStack)) 
    {
        enqueue(outQueue, pop(opStack));
    }
}

/******************************************************************************
 * Method: evaluate: 
 * 
 * - Evaluates a postfix mathematical expression.
 *
 * Input: queue *postfixQueue.
 *
 * Output: Result of the expression.
 *
******************************************************************************/
int evaluate(queue *postfixQueue) 
{
    stack *evalStack = createStack();

    while (!isEmptyQueue(postfixQueue)) 
    {
        int current = dequeue(postfixQueue);
        if (current != '+' && current != '-' && current != '*' && current != '/' && current != '^') 
        {
            push(evalStack, current);
        } 
        else 
        {
            int b = pop(evalStack);
            int a = pop(evalStack);
            int result = operate(a, b, current);
            push(evalStack, result);
        }
    }
    int result = pop(evalStack);
    return result;
}

/******************************************************************************
 * Method: getPrec: 
 * 
 * - Returns the precedence of an operator.
 *
 * Input: char op.
 *
 * Output: Precedence of the operator.
 *
******************************************************************************/
int getPrec(char op)
{
    switch (op) 
    {
        case '+': 
        case '-': 
            return 1;
        case '*': 
        case '/': 
            return 2;
        case '^': 
            return 3;
        default: 
            return 0;
    }
}

/******************************************************************************
 * Method: operate: 
 * 
 * - Performs an operation on two operands.
 *
 * Input: int a, int b, char op.
 *
 * Output: Result of the operation.
 *
******************************************************************************/
int operate(int a, int b, char op)
{
    switch (op) 
    {
        case '+': 
            return a + b;
        case '-':
            return a - b;
        case '*': 
            return a * b;
        case '/':
            if (b == 0) 
            {
                fprintf(stderr, "Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        case '^': 
            if (b < 0 && a == 0) 
            {
                fprintf(stderr, "Error: Division by zero\n");
                exit(EXIT_FAILURE); 
            }
            return (int)pow((double)a, (double)b);
        default: 
            fprintf(stderr, "Error: Unknown operation '%c'\n", op);
            exit(EXIT_FAILURE);
    }
}

/******************************************************************************
 * Method: freeStack: 
 * 
 * - Frees the memory allocated for the stack.
 *
 * Input: stack *s.
 *
 * Output: None.
 *
******************************************************************************/
void freeStack(stack *s)
{
    while (!isEmptyStack(s))
    {
        pop(s);
    }
    free(s);
}

/******************************************************************************
 * Method: freeQueue: 
 * 
 * - Frees the memory allocated for the queue.
 *
 * Input: queue *q.
 *
 * Output: None.
 *
******************************************************************************/
void freeQueue(queue *q)
{
    while (!isEmptyQueue(q))
    {
        dequeue(q);
    }
    free(q);
}
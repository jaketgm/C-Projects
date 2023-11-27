#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node *next;
} node;

typedef struct Stack 
{
    node *top;
    int size;
} stack;

/******************************************************************************
 * Method: createStack: 
 * 
 * - Allocates memory for a new stack, initializes its top pointer to NULL and 
 *    its size to 0, and returns a pointer to the newly created stack.
 *
 * Input: None.
 *
 * Output: stack* - A pointer to the newly created stack.
 *
******************************************************************************/
stack *createStack()
{
    stack *s = (stack*) malloc(sizeof(stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

/******************************************************************************
 * Method: isEmpty: 
 * 
 * - Checks if the stack is empty by verifying if the top pointer is NULL.
 *
 * Input: stack *s - Pointer to the stack to be checked.
 *
 * Output: bool - True if the stack is empty, false otherwise.
 *
******************************************************************************/
bool isEmpty(stack *s)
{
    return s->top == NULL;
}

/******************************************************************************
 * Method: push: 
 * 
 * - Creates a new node with the given data and pushes it onto the stack.
 *
 * Input: stack *s - Pointer to the stack to be pushed onto.
 *        int item - The data to be pushed onto the stack.
 *
 * Output: None.
 * 
******************************************************************************/
void push(stack *s, int item)
{
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = item;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

/******************************************************************************
 * Method: pop: 
 * 
 * - Removes the top element from the stack and returns it.
 *
 * Input: stack *s - Pointer to the stack to be popped from.
 *
 * Output: int - The data of the popped node.
 *
******************************************************************************/
int pop(stack *s)
{
    if (isEmpty(s)) 
    {
        printf("Stack is empty\n");
        return -1;
    }
    int data = s->top->data;
    node *temp = s->top;
    s->top = s->top->next;
    free(temp);
    s->size--;
    return data;
}

/******************************************************************************
 * Method: peek: 
 * 
 * - Returns the data of the top element of the stack.
 *
 * Input: stack *s - Pointer to the stack to be peeked at.
 *
 * Output: int - The data of the top node.
 *
******************************************************************************/
int peek(stack *s)
{
    if (isEmpty(s)) 
    {
        printf("Stack is empty\n");
        return -1;
    }
    return s->top->data;
}

/******************************************************************************
 * Method: printStack: 
 * 
 * - Prints the contents of the stack to the console.
 *
 * Input: stack *s - Pointer to the stack to be printed.
 *
 * Output: None.
 *
******************************************************************************/
void printStack(stack *s)
{
    if (isEmpty(s)) 
    {
        printf("Stack is empty\n");
        return;
    }
    node *temp = s->top;
    while (temp != NULL) 
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
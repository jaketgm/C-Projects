#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

/******************************************************************************
 * @author Jake Brockbank
 * Nov 10th, 2023
 * Creates a stack and push/pops nodes from it.
******************************************************************************/

/******************************************************************************
 * Method: main: 
 * 
 * - Creates a Stack: A stack named s is created using the createStack() 
 * function. Which initializes a new stack data structure.
 * - Pushes Elements onto the Stack:
 *   - The integer 10 is pushed onto the stack.
 *   - The integer 20 is then pushed onto the stack, placing it on top of 10.
 *   - Finally, the integer 30 is pushed onto the stack, placing it on top 
 *     of 20.
 * - After these operations, the stack s contains the elements in the following 
 *   order (top to bottom): 30, 20, 10.
 * - Prints the Original Stack:
 *   - The current contents of the stack are printed to the console using 
 *     the printStack(s) function. This displays the stack elements 
 *     30, 20, 10.
 * - Pops an Element from the Stack:
 *   - The pop(s) function is called, which removes the top element from 
 *     the stack and returns it. The value returned by pop(s) is printed 
 *     to the console.
 *   - Prints the Stack After Removal:
 * - The stack is printed again using printStack(s) to show its state 
 *   after the pop operation. At this point, the stack contains
 *   20 at the top, followed by 10.
 *
 * Input: None.
 *
 * Output: The printed stack after manipulations.
 *
******************************************************************************/
int main()
{
    stack *s = createStack();

    push(s, 10);
    push(s, 20);
    push(s, 30);

    printf("\n");
    printf("Original stack\n");
    printStack(s);

    printf("\n%d popped from stack\n", pop(s));

    printf("\nStack after removal\n");
    printStack(s);
    printf("\n");

    return 0;
}
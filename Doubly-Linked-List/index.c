#include <stdio.h>
#include <stdlib.h>
#include "doublyLL.h"

/******************************************************************************
 * @author Jake Brockbank
 * Nov 10th, 2023
 * Creates a doubly linked list and inserts/deletes nodes from it.
******************************************************************************/

/******************************************************************************
 * Method: main: 
 * 
 * - Creates a Doubly Linked List:
 * - Starts by creating an empty doubly linked list dll.
 * - Inserts Nodes at the Front of the List:
 * - Inserts the integer 1 at the front of the list.
 * - Inserts the integer 2 at the front, making 1 the second node.
 * - Inserts the integer 3 at the front, pushing 2 and 1 to second and third positions respectively.
 * - After these insertions, the list looks like this: 3 -> 2 -> 1.
 * - Prints the Original List:
 * - Prints the current state of the list, which displays: 3 2 1.
 * - Deletes the Node with Data 1:
 * - Deletes the node whose data value is 1. After this deletion we have: 3 -> 2.
 * - Prints the List After Deletion of 1:
 * - Prints the current state of the list: 3 2.
 * - Deletes the Node with Data 2:
 * - Deletes the node whose data value is 2. After this deletion: 3.
 * - Prints the List After Deletion of 2:
 * - Prints the current state of the list, which displays: 3.
 *
 * Input: None.
 *
 * Output: The printed doubly linked list after manipulations.
 *
******************************************************************************/
int main()
{
    doublyLL *dll = createDLL();
    insertAtFront(dll, 1);
    insertAtFront(dll, 2);
    insertAtFront(dll, 3);

    printf("Original Doubly Linked List: \n");
    printDLL(dll);

    deleteNode(dll, 1);

    printf("Doubly Linked List After Deletion of 1: \n");
    printDLL(dll);

    deleteNode(dll, 2);

    printf("Doubly Linked List After Deletion of 2: \n");
    printDLL(dll);
    return 0;
}
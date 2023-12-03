/******************************************************************************
 * @author Jake Brockbank
 * Dec 3rd, 2023
 * Creates a simple linked list and performs some operations on it.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/******************************************************************************
 * Method: Main: 
 * 
 * - Creates a simple linked list and performs some operations on it.
 *
 * Input: None.
 *
 * Output: Linked list with applied operations.
 *
******************************************************************************/
int main()
{
    linkedlist *list = createLinkedList();

    insertAtBeginning(list, 10);
    insertAtBeginning(list, 20);
    insertAtBeginning(list, 30);
    printList(list);

    if (searchNode(list, 20))
    {
        printf("\nNode found.\n");
    }
    else
    {
        printf("\nNode not found.\n");
    }

    deleteOnKey(list, 20);
    printList(list);

    freeLinkedList(list);
    return 0;
}
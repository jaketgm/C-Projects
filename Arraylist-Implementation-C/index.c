#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arrayList.h"

/************************************************************************************
 * @author Jake Brockbank
 * October 31st, 2023
 * This code creates an ArrayList, populates it with numbers from 1 to 40, prints 
 * the original contents, sorts the ArrayList, and then prints the sorted contents. 
 * It's a simple demonstration of how to use an ArrayList data structure in C to 
 * store and manipulate a list of integers.
************************************************************************************/

/*---------------------------------------------------------------------------------*/

/************************************************************************************
 * Method: main: 
 * 
 * - ArrayList *myList = createArrayList();: This line creates an ArrayList and 
 * assigns it to the pointer myList. createArrayList() is a function that initializes 
 * an ArrayList, allocates memory for it, and returns a pointer to the newly 
 * created ArrayList. The ArrayList is essentially a dynamically resizing array.
 * - The code then enters a loop that inserts the numbers from 1 to 40 into the 
 * ArrayList using the insert() function. This loop populates the ArrayList with 
 * elements.
 * - After populating the ArrayList, it prints the contents of the ArrayList to the 
 * console using a loop. The loop iterates through the list attribute of the 
 * ArrayList and prints each element to the console.
 * - The code then calls sortArrayList(myList);, which presumably sorts the 
 * ArrayList. This function sorts the elements in the ArrayList in ascending 
 * order.
 * - After sorting, it prints the sorted contents of the ArrayList to the console 
 * in a similar manner as before.
 * - Finally, the code frees the memory allocated for the ArrayList using 
 * freeArrayList(myList);. This is important to prevent memory leaks.
 *
 * Input: None.
 *
 * Output: Arraylist Implementation in C.
 *
************************************************************************************/
int main()
{
    arrayList *myList = createArrayList();

    for (int i = 1; i <= 40; i++)
    {
        insert(i, myList);
    }

    printf("ArrayList contents: ");
    for (int i = 0; i < myList->load; i++) {
        printf("%d ", myList->list[i]);
    }
    printf("\n");

    sortArrayList(myList);

    printf("Sorted ArrayList contents: ");
    for (int i = 0; i < myList->load; i++) {
        printf("%d ", myList->list[i]);
    }
    printf("\n");

    // Free the ArrayList when done
    freeArrayList(myList);
    return 0;
}
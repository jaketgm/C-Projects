#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

/******************************************************************************
 * @author Jake Brockbank
 * Nov 10th, 2023
 * Creates a queue and enqueue/dequeue nodes from it.
******************************************************************************/

/******************************************************************************
 * Method: main: 
 * 
 * - Creates a Queue:
 *   - A queue q is created using the createQueue() function. 
 *     This function initializes a new queue data structure.
 * - Enqueues Elements into the Queue:
 *   - The integer 10 is added (enqueued) to the queue.
 *   - The integer 20 is then added to the queue, following 10.
 *   - Finally, the integer 30 is added to the queue, following 20.
 * - After these operations, the queue q contains the elements in the 
 *   following order (front to rear): 10, 20, 30.
 * - Prints the Original Queue:
 *   - The current contents of the queue are printed to the console 
 *     using the printQueue(q) function. This displays the queue elements 
 *     10, 20, 30.
 * - Dequeues an Element from the Queue:
 *   - The dequeue(q) function is called, which removes and returns the front 
 *     element of the queue. This element is then printed using printf. 
 *     Since 10 is at the front of the queue, it is removed and its 
 *     value is printed.
 * - Prints the Queue After Removal:
 *   - The queue is printed again using printQueue(q) to show its state 
 *     after the dequeue operation. At this point, the queue 
 *     contains 20 at the front, followed by 30.
 *
 * Input: None.
 *
 * Output: The printed queue after manipulations.
 *
******************************************************************************/
int main()
{
    queue* q = createQueue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    printf("\n");
    printf("Original queue\n");
    printQueue(q);

    printf("\n%d dequeued from queue\n", dequeue(q));

    printf("\nQueue after removal\n");
    printQueue(q);
    printf("\n");

    return 0;
}
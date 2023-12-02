#include <stdbool.h>
#include <stdlib.h>

typedef struct QueueNode 
{
    int data;
    struct QueueNode* next;
} queueNode;

typedef struct Queue 
{
    queueNode* head;
    queueNode* tail;
} queue;

/******************************************************************************
 * Method: createQueue: 
 * 
 * - Memory Allocation for Queue:
 *   - The function allocates memory for a new queue structure. This is done 
 *     using the malloc function, which allocates memory of size equal to 
 *     sizeof(queue). 
 * - Initialization of Queue Properties:
 *   - The head and tail pointers of the queue are initialized to NULL. 
 * - Returns the New Queue:
 *   - The function returns a pointer to the newly created and initialized 
 *     queue (q).
 *
 * Input: None.
 *
 * Output: queue* - A pointer to the newly created queue.
 *
******************************************************************************/
queue* createQueue() 
{
    queue* q = (queue*) malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/******************************************************************************
 * Method: isEmptyQueue: 
 * 
 * - Checks if the Queue is Empty:
 *   - The function checks if the head pointer of the queue is NULL. 
 *     If it is, the queue is empty and the function returns true. 
 *     Otherwise, the function returns false.
 *
 * Input: queue* q - A pointer to the queue to check.
 *
 * Output: bool - True if the queue is empty, false otherwise.
 *
******************************************************************************/
bool isEmptyQueue(queue* q) 
{
    return q->head == NULL;
}

/******************************************************************************
 * Method: enqueue: 
 * 
 * - Memory Allocation for New Node:
 *   - The function allocates memory for a new queue node. This is done using 
 *     the malloc function, which allocates memory of size equal to 
 *     sizeof(queueNode). 
 * - Initialization of New Node:
 *   - The data field of the new node is initialized to the value passed 
 *     to the function. The next pointer of the new node is initialized to NULL.
 * - Checks if Queue is Empty:
 *   - The function checks if the queue is empty. If it is, the new node is 
 *     added as the first node in the queue. The head and tail pointers of 
 *     the queue are set to the new node.
 * - Adds Node to End of Queue:
 *   - If the queue is not empty, the new node is added to the end of the 
 *     queue. The next pointer of the current tail node is set to the new node. 
 *     The tail pointer of the queue is then set to the new node.
 *
 * Input: queue* q - A pointer to the queue to add to.
 *        int data - The data to add to the queue.
 *
 * Output: None.
 *
******************************************************************************/
void enqueue(queue* q, int data) 
{
    queueNode* newNode = (queueNode*) malloc(sizeof(queueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmptyQueue(q)) 
    {
        q->head = q->tail = newNode;
        return;
    }

    q->tail->next = newNode;
    q->tail = newNode;
}

/******************************************************************************
 * Method: dequeue: 
 * 
 * - Checks if Queue is Empty:
 *   - The function checks if the queue is empty. If it is, the function 
 *     returns -1.
 * - Removes Node from Front of Queue:
 *   - If the queue is not empty, the node at the front of the queue is 
 *     removed. The head pointer of the queue is set to the next node in 
 *     the queue. If the head pointer is now NULL, the tail pointer is also 
 *     set to NULL.
 * - Returns the Data of the Removed Node:
 *   - The data of the removed node is returned.
 *
 * Input: queue* q - A pointer to the queue to remove from.
 *
 * Output: int - The data of the removed node.
 *
******************************************************************************/
int dequeue(queue* q) 
{
    if (isEmptyQueue(q))
        return -1;

    queueNode* temp = q->head;
    int data = temp->data;

    q->head = q->head->next;

    if (q->head == NULL)
        q->tail = NULL;

    free(temp);

    return data;
}

/******************************************************************************
 * Method: peekQueue: 
 * 
 * - Checks if Queue is Empty:
 *   - The function checks if the queue is empty. If it is, the function 
 *     returns -1.
 * - Returns the Data of the Front Node:
 *   - The data of the front node is returned.
 *
 * Input: queue* q - A pointer to the queue to peek at.
 *
 * Output: int - The data of the front node.
 *
******************************************************************************/
int peekQueue(queue* q) 
{
    if (isEmptyQueue(q))
        return -1;

    return q->head->data;
}

/******************************************************************************
 * Method: printQueue: 
 * 
 * - Checks if Queue is Empty:
 *   - The function checks if the queue is empty. If it is, the function 
 *     prints a message to the console and returns.
 * - Prints the Queue:
 *   - If the queue is not empty, the function prints the contents of the 
 *     queue to the console. The function starts at the head of the queue 
 *     and prints the data of each node until the tail of the queue is reached.
 *
 * Input: queue* q - A pointer to the queue to print.
 *
 * Output: None.
 *
******************************************************************************/
void printQueue(queue* q) 
{
    if (isEmptyQueue(q)) 
    {
        printf("Queue is empty.\n");
        return;
    }

    queueNode* temp = q->head;

    while (temp != NULL) 
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL");
    printf("\n");
}
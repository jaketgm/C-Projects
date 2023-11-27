typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} node;

typedef struct DoublyLL
{
    node *head;
} doublyLL;

void freeSingleNode(node *theNode);

/******************************************************************************
* Method: createNode
* 
* - Creates a new node with the given data, setting its next and previous 
*   pointers to NULL.
*
* Input: int data - The data to be stored in the node.
*
* Output: node* - Pointer to the newly created node.
*
******************************************************************************/
node *createNode(int data)
{
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/******************************************************************************
* Method: createDLL
* 
* - Creates a new doubly linked list by allocating memory for it and 
*   initializing its head to NULL.
* 
* Input: None.
* 
* Output: doublyLL* - Pointer to the newly created doubly linked list.
*
******************************************************************************/
doublyLL *createDLL()
{
    doublyLL *newDLL = (doublyLL*) malloc(sizeof(doublyLL));
    newDLL->head = NULL;
    return newDLL;
}

/******************************************************************************
* Method: insertAtFront
*
* - Inserts a new node with the given data at the front of the doubly linked list.
*
* Input: doublyLL *dll - The doubly linked list to insert the node into.
*        int data - The data for the new node.
*
* Output: None.
*
******************************************************************************/
void insertAtFront(doublyLL *dll, int data)
{
    node *newNode = createNode(data);
    if (dll->head == NULL)
    {
        dll->head = newNode;
        return;
    }
    newNode->next = dll->head;
    dll->head->prev = newNode;
    dll->head = newNode;
}

/******************************************************************************
* Method: deleteNode
*   
* - Deletes a node with the specified data from the doubly linked list. If 
*   multiple nodes have the same data, only the first one encountered is deleted.
* 
* Input: doublyLL *dll - The doubly linked list from which to delete the node.
*        int data - The data of the node to be deleted.
* 
* Output: None.
*
******************************************************************************/
void deleteNode(doublyLL *dll, int data) 
{
    if (dll->head == NULL)
        return;

    node *temp = dll->head;

    while (temp != NULL && temp->data != data)
        temp = temp->next;

    if (temp == NULL)
        return;

    if (temp == dll->head)
        dll->head = dll->head->next;

    // Update the next and prev pointers
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    if (temp->prev != NULL)
        temp->prev->next = temp->next;

    freeSingleNode(temp);
}

/******************************************************************************
* Method: freeSingleNode
* 
* - Frees the memory allocated for a single node.
* 
* Input: node *theNode - The node to be freed.
* 
* Output: None.
*
******************************************************************************/
void freeSingleNode(node *theNode) 
{
    free(theNode);
}

/******************************************************************************
* Method: freeDLL
* 
* - Frees the entire doubly linked list including all its nodes and the list 
*   structure itself.
*
* Input: doublyLL *dll - The doubly linked list to be freed.
*
* Output: None.
*
******************************************************************************/
void freeDLL(doublyLL *dll)
{
    freeSingleNode(dll->head);
    free(dll);
}

/******************************************************************************
* Method: printDLL
* 
* - Prints the data of each node in the doubly linked list from head to tail.
* 
* Input: doublyLL *dll - The doubly linked list to be printed.
* 
* Output: None (Output is printed to the console).
*
******************************************************************************/
void printDLL(doublyLL *dll)
{
    node *temp = dll->head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
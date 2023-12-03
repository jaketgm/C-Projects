typedef struct Node
{
    int data;
    struct Node *next;
} node;

typedef struct LinkedList
{
    node *head;
} linkedlist;

/******************************************************************************
 * Method: createLinkedList: 
 * 
 * - Creates a linked list.
 *
 * Input: None.
 *
 * Output: A linked list.
 *
******************************************************************************/
linkedlist *createLinkedList()
{
    linkedlist *list = (linkedlist*) malloc(sizeof(linkedlist));
    if (list == NULL)
        exit(EXIT_FAILURE);
    
    list->head = NULL;
    return list;
}

/******************************************************************************
 * Method: createNode: 
 * 
 * - Creates a node.
 *
 * Input: int data.
 *
 * Output: A node.
 *
******************************************************************************/
node *createNode(int data)
{
    node *newNode = (node*) malloc(sizeof(node));
    if (newNode == NULL)
        exit(EXIT_FAILURE);
    
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/******************************************************************************
 * Method: insertAtBeginning: 
 * 
 * - Inserts a node at the beginning of the linked list.
 *
 * Input: linkedlist *list, int data.
 *
 * Output: None.
 *
******************************************************************************/
void insertAtBeginning(linkedlist *list, int data)
{
    node *newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

/******************************************************************************
 * Method: insertAtEnd: 
 * 
 * - Inserts a node at the end of the linked list.
 *
 * Input: linkedlist *list, int data.
 *
 * Output: None.
 *
******************************************************************************/
void insertAtEnd(linkedlist *list, int data)
{
    node *newNode = createNode(data);
    if (list->head == NULL)
    {
        list->head = newNode;
        return;
    }

    node *last = list->head;
    while (last->next != NULL)
        last = last->next;
    
    last->next = newNode;
}

/******************************************************************************
 * Method: deleteOnKey: 
 * 
 * - Deletes a node on a given key.
 *
 * Input: linkedlist *list, int key.
 *
 * Output: None.
 *
******************************************************************************/
void deleteOnKey(linkedlist *list, int key)
{
    node *temp = list->head, *prev = NULL;
    if (temp != NULL && temp->data == key)
    {
        list->head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;
    
    prev->next = temp->next;
    free(temp);
}

/******************************************************************************
 * Method: searchNode: 
 * 
 * - Searches for a node on a given key.
 *
 * Input: linkedlist *list, int key.
 *
 * Output: 1 if found, 0 if not.
 *
******************************************************************************/
int searchNode(linkedlist *list, int key)
{
    node *current = list->head;
    while (current != NULL)
    {
        if (current->data == key)
            return 1;
        current = current->next;
    }
    return 0;
}

/******************************************************************************
 * Method: freeLinkedList: 
 * 
 * - Frees the linked list.
 *
 * Input: linkedlist *list.
 *
 * Output: None.
 *
******************************************************************************/
void freeLinkedList(linkedlist *list)
{
    node *current = list->head;
    node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

/******************************************************************************
 * Method: printList: 
 * 
 * - Prints the linked list.
 *
 * Input: linkedlist *list.
 *
 * Output: None.
 *
******************************************************************************/
void printList(linkedlist *list)
{
    node *newNode = list->head;
    while (newNode != NULL)
    {
        printf("%d -> ", newNode->data);
        newNode = newNode->next;
    }
    printf("NULL");
}
typedef struct AVLNode
{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} avlNode;

/******************************************************************************
 * Method: findHeight: 
 * 
 * - Finds the height of the given node.
 *
 * Input: avlNode *theNode.
 *
 * Output: Height of the given node.
 *
******************************************************************************/
int findHeight(avlNode *theNode)
{
    if (theNode == NULL)
        return 0;
    
    return theNode->height;
}

/******************************************************************************
 * Method: max: 
 * 
 * - Finds the max of the given two numbers.
 *
 * Input: int a, int b.
 *
 * Output: Max of the given two numbers.
 *
******************************************************************************/
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/******************************************************************************
 * Method: createNode: 
 * 
 * - Creates a new node with the given key.
 *
 * Input: int key.
 *
 * Output: New node with the given key.
 *
******************************************************************************/
avlNode *createNode(int key)
{
    avlNode *newNode = (avlNode*) malloc(sizeof(avlNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return (newNode);
}

/******************************************************************************
 * Method: rightRotate: 
 * 
 * - Performs a right rotation on the given node.
 *
 * Input: avlNode *theNode.
 *
 * Output: The node after the right rotation.
 *
******************************************************************************/
avlNode *rightRotate(avlNode *theNode)
{
    avlNode *newNode = theNode->left;
    avlNode *T2 = newNode->right;

    newNode->right = theNode;
    theNode->left = T2;

    theNode->height = max(findHeight(theNode->left), findHeight(theNode->right)) + 1;
    newNode->height = max(findHeight(newNode->left), findHeight(newNode->right)) + 1;

    return newNode;
}

/******************************************************************************
 * Method: leftRotate: 
 * 
 * - Performs a left rotation on the given node.
 *
 * Input: avlNode *newNode.
 *
 * Output: The node after the left rotation.
 *
******************************************************************************/
avlNode *leftRotate(avlNode *newNode)
{
    avlNode *theNode = newNode->right;
    avlNode *T2 = theNode->left;

    theNode->left = newNode;
    newNode->right = T2;

    newNode->height = max(findHeight(newNode->left), findHeight(newNode->right)) + 1;
    theNode->height = max(findHeight(theNode->left), findHeight(theNode->right)) + 1;

    return theNode;
}

/******************************************************************************
 * Method: getBalance: 
 * 
 * - Gets the balance of the given node.
 *
 * Input: avlNode *theNode.
 *
 * Output: Balance of the given node.
 *
******************************************************************************/
int getBalance(avlNode *theNode)
{
    if (theNode == NULL)
        return 0;
    
    return findHeight(theNode->left) - findHeight(theNode->right);
}

/******************************************************************************
 * Method: insert: 
 * 
 * - Inserts a new node with the given key.
 *
 * Input: avlNode *newNode, int key.
 *
 * Output: The node after the insertion.
 *
******************************************************************************/
avlNode *insert(avlNode *newNode, int key)
{
    if (newNode == NULL)
        return (createNode(key));
    
    if (key < newNode->key)
        newNode->left = insert(newNode->left, key);
    else if (key > newNode->key)
        newNode->right = insert(newNode->right, key);
    else
        return newNode;

    newNode->height = 1 + max(findHeight(newNode->left), findHeight(newNode->right));

    int balance = getBalance(newNode);

    if (balance > 1 && key < newNode->left->key)
        return rightRotate(newNode);
    
    if (balance < -1 && key > newNode->right->key)
        return leftRotate(newNode);

    if (balance > 1 && key > newNode->left->key)
    {
        newNode->left = leftRotate(newNode->left);
        return rightRotate(newNode);
    }

    if (balance < -1 && key < newNode->right->key)
    {
        newNode->right = rightRotate(newNode->right);
        return leftRotate(newNode);
    }

    return newNode;    
}

avlNode *minValNode(avlNode *theNode);

/******************************************************************************
 * Method: deleteNode: 
 * 
 * - Deletes a node with the given key.
 *
 * Input: avlNode *root, int key.
 *
 * Output: The node after the deletion.
 *
******************************************************************************/
avlNode *deleteNode(avlNode *root, int key)
{
    if (root == NULL)
        return root;
    
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            avlNode *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }

            free(temp);
        }
        else
        {
            avlNode *temp = minValNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }        
    }

    if (root == NULL)
        return root;
    
    root->height = 1 + max(findHeight(root->left), findHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/******************************************************************************
 * Method: preOrder: 
 * 
 * - Performs a preorder traversal on the given node.
 *
 * Input: avlNode *root.
 *
 * Output: None.
 *
******************************************************************************/
void preOrder(avlNode *root)
{
    if (root != NULL)
    {
        printf("%d -> ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

/******************************************************************************
 * Method: minValNode: 
 * 
 * - Finds the node with the minimum value.
 *
 * Input: avlNode *theNode.
 *
 * Output: The node with the minimum value.
 *
******************************************************************************/
avlNode *minValNode(avlNode *theNode)
{
    avlNode *current = theNode;

    while (current->left != NULL)
        current = current->left;
    
    return current;
}
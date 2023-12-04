typedef struct bstNode 
{
    int data;
    struct bstNode *left, *right;
} bstnode;

typedef struct BST 
{
    bstnode *root;
} bst;

/******************************************************************************
 * Method: createBSTNode: 
 * 
 * - This code is for creating a BST node.
 *
 * Input: int data.
 *
 * Output: bstnode* newNode.
 *
******************************************************************************/
bstnode *createBSTNode(int data) 
{
    bstnode *newNode = (bstnode*) malloc(sizeof(bstnode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/******************************************************************************
 * Method: createBST: 
 * 
 * - This code is for creating a BST.
 *
 * Input: None.
 *
 * Output: bst* tree.
 *
******************************************************************************/
bst *createBST() 
{
    bst *tree = (bst*) malloc(sizeof(bst));
    tree->root = NULL;
    return tree;
}

/******************************************************************************
 * Method: freeBSTNode: 
 * 
 * - This code is for freeing a BST node.
 *
 * Input: bstnode *theNode.
 *
 * Output: None.
 *
******************************************************************************/
void freeBSTNode(bstnode *theNode) 
{
    if (theNode != NULL) 
    {
        freeBSTNode(theNode->left);
        freeBSTNode(theNode->right);
        free(theNode);
    }
}

/******************************************************************************
 * Method: freeBST: 
 * 
 * - This code is for freeing a BST.
 *
 * Input: bst *tree.
 *
 * Output: None.
 *
******************************************************************************/
void freeBST(bst *tree) 
{
    if (tree != NULL) 
    {
        freeBSTNode(tree->root);
        free(tree);
    }
}

/******************************************************************************
 * Method: insert: 
 * 
 * - This code is for inserting a node into a BST.
 *
 * Input: bst *tree, int key.
 *
 * Output: None.
 *
******************************************************************************/
void insert(bst *tree, int key) 
{
    bstnode **current = &(tree->root);
    while (*current != NULL) 
    {
        if (key < (*current)->data) 
        {
            current = &((*current)->left);
        } 
        else if (key > (*current)->data) 
        {
            current = &((*current)->right);
        } 
        else 
        {
            return; // Key already exists, no duplicates in BST
        }
    }
    *current = createBSTNode(key);
}

/******************************************************************************
 * Method: minValBSTNode: 
 * 
 * - This code is for finding the minimum value node in a BST.
 *
 * Input: bstnode *theNode.
 *
 * Output: bstnode *current.
 *
******************************************************************************/
bstnode *minValBSTNode(bstnode *theNode) 
{
    bstnode *current = theNode;
    while (current && current->left != NULL) 
    {
        current = current->left;
    }
    return current;
}

/******************************************************************************
 * Method: deleteBSTNode: 
 * 
 * - This code is for deleting a node in a BST.
 *
 * Input: bst *tree, int key.
 *
 * Output: None.
 *
******************************************************************************/
void deleteBSTNode(bst *tree, int key) 
{
    bstnode **current = &(tree->root);
    while (*current != NULL) 
    {
        if (key < (*current)->data) 
        {
            current = &((*current)->left);
        } 
        else if (key > (*current)->data) 
        {
            current = &((*current)->right);
        } 
        else 
        {
            // Node with only one child or no child
            if ((*current)->left == NULL) 
            {
                bstnode *temp = (*current)->right;
                free(*current);
                *current = temp;
            } 
            else if ((*current)->right == NULL) 
            {
                bstnode *temp = (*current)->left;
                free(*current);
                *current = temp;
            } 
            else 
            {
                // Node with two children: Get the inorder successor
                bstnode *temp = minValBSTNode((*current)->right);

                // Copy the inorder successor's content to this node
                (*current)->data = temp->data;

                // Delete the inorder successor
                bstnode **succ_parent = &((*current)->right);
                while ((*succ_parent) != temp) 
                {
                    succ_parent = &((*succ_parent)->left);
                }
                if (temp->right != NULL) 
                {
                    *succ_parent = temp->right;
                } 
                else 
                {
                    *succ_parent = NULL;
                }
                free(temp);
            }
            return;
        }
    }
}

/******************************************************************************
 * Method: inOrderTraverse: 
 * 
 * - This code is for performing an inorder traversal on a BST.
 *
 * Input: bstnode *root.
 *
 * Output: None.
 *
******************************************************************************/
void inOrderTraverse(bstnode *root) 
{
    if (root != NULL) 
    {
        inOrderTraverse(root->left);
        printf("(%d) -> ", root->data);
        inOrderTraverse(root->right);
    }
}

/******************************************************************************
 * Method: printSpaces: 
 * 
 * - This code is for printing spaces.
 *
 * Input: int count.
 *
 * Output: None.
 *
******************************************************************************/
void printSpaces(int count) 
{
    while (count--) printf(" ");
}

/******************************************************************************
 * Method: printTreeLevel: 
 * 
 * - This code is for printing a level of a BST.
 *
 * Input: bstnode* root, int level, int indentSpace, int totalDepth.
 *
 * Output: None.
 *
******************************************************************************/
void printTreeLevel(bstnode* root, int level, int indentSpace, int totalDepth) 
{
    if (root == NULL) 
    {
        printSpaces(indentSpace);  // Print space for missing nodes
        return;
    }
    if (level == 1) 
    {
        printSpaces(indentSpace);
        printf("(%d)", root->data);  // Print node
        printSpaces(indentSpace);
    } 
    else if (level > 1) 
    {
        int isLeft = (level == totalDepth);  // Check if on the leftmost edge
        printTreeLevel(root->left, level - 1, indentSpace - isLeft, totalDepth);  // Recur for left subtree
        printSpaces(indentSpace * 2 + 1);
        printTreeLevel(root->right, level - 1, indentSpace - isLeft, totalDepth);  // Recur for right subtree
    }
}

/******************************************************************************
 * Method: printBranches: 
 * 
 * - This code is for printing branches of a BST.
 *
 * Input: int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, 
 * const int *nodeValues.
 *
 * Output: None.
 *
******************************************************************************/
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const int *nodeValues) 
{
    for (int i = 0; i < nodesInThisLevel / 2; i++) 
    {
        printSpaces(startLen - i);
        printf("/");
        printSpaces(2 * i + nodeSpaceLen);
        printf("\\");
        printSpaces(branchLen - i);
    }
    printf("\n");
}

/******************************************************************************
 * Method: printNodes: 
 * 
 * - This code is for printing nodes of a BST.
 *
 * Input: int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, 
 * const int *nodeValues
 *
 * Output: None.
 *
******************************************************************************/
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const int *nodeValues) 
{
    for (int i = 0; i < nodesInThisLevel; i++) 
    {
        printSpaces(startLen);
        printf("(%d)", nodeValues[i]);
        printSpaces(nodeSpaceLen);
    }
    printf("\n");
}

/******************************************************************************
 * Method: getTreeDepth: 
 * 
 * - This code is for getting the depth of a BST.
 *
 * Input: bstnode *node.
 *
 * Output: None.
 *
******************************************************************************/
int getTreeDepth(bstnode *node) 
{
    if (node == NULL) return 0;
    int leftDepth = getTreeDepth(node->left);
    int rightDepth = getTreeDepth(node->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

/******************************************************************************
 * Method: getNodesAtLevel: 
 * 
 * - This code is for getting the nodes at a level of a BST.
 *
 * Input: bstnode *root, int level, bstnode **nodes, int index.
 *
 * Output: None.
 *
******************************************************************************/
void getNodesAtLevel(bstnode *root, int level, bstnode **nodes, int index) 
{
    if (root == NULL) 
        return;
    if (level == 1) 
    {
        nodes[index] = root;
    } 
    else if (level > 1) 
    {
        getNodesAtLevel(root->left, level - 1, nodes, 2 * index);
        getNodesAtLevel(root->right, level - 1, nodes, 2 * index + 1);
    }
}

/******************************************************************************
 * Method: fillNodeValues: 
 * 
 * - This code is for filling the values of a node in a BST.
 *
 * Input: bstnode *node, int level, int *nodeValues, int index, int treeDepth.
 *
 * Output: None.
 *
******************************************************************************/
void fillNodeValues(bstnode *node, int level, int *nodeValues, int index, int treeDepth) 
{
    if (node == NULL) 
    {
        if (level < treeDepth) 
        {
            // Fill left and right children's places with -1 to indicate NULL
            fillNodeValues(NULL, level + 1, nodeValues, index * 2 + 1, treeDepth);
            fillNodeValues(NULL, level + 1, nodeValues, index * 2 + 2, treeDepth);
        }
    } 
    else 
    {
        nodeValues[index] = node->data;
        fillNodeValues(node->left, level + 1, nodeValues, index * 2 + 1, treeDepth);
        fillNodeValues(node->right, level + 1, nodeValues, index * 2 + 2, treeDepth);
    }
}

/******************************************************************************
 * Method: printChar: 
 * 
 * - This code is for printing a character.
 *
 * Input: char character, int count.
 *
 * Output: None.
 *
******************************************************************************/
void printChar(char character, int count) 
{
    for (int i = 0; i < count; ++i) 
    {
        printf("%c", character);
    }
}

/******************************************************************************
 * Method: printTree: 
 * 
 * - This code is for printing a BST.
 *
 * Input: bstnode *root.
 *
 * Output: None.
 *
******************************************************************************/
void printTree(bstnode *root) 
{
    int depth = getTreeDepth(root);

    // Calculate the width of the tree at the widest point
    int levelWidth = (int)pow(2, depth);

    // Array of nodes for current level
    bstnode **levelNodes = (bstnode**) malloc(sizeof(bstnode*) * levelWidth);
    for (int i = 0; i < levelWidth; ++i) 
    {
        levelNodes[i] = NULL;
    }

    // Put the root node in the first position of the array
    levelNodes[0] = root;

    // The width of the gap between left and right '/' and '\' for each node
    int nodeSpace = 0;
    int nodeCount = 1;  // Start with 1 node at the root

    for (int currentDepth = 1; currentDepth <= depth; ++currentDepth) 
    {
        // The space between left and right branches
        int branchSpace = (int)pow(2, depth - currentDepth) - 1;

        // Print nodes at current level
        for (int i = 0; i < nodeCount; ++i) 
        {
            printChar(' ', branchSpace);  // Space before the node
            if (levelNodes[i] != NULL) 
            {
                printf("(%d)", levelNodes[i]->data);
            } 
            else 
            {
                printf("   ");  // Space for missing node
            }
            printChar(' ', branchSpace);  // Space after the node
            printChar(' ', (currentDepth == 1) ? 0 : 1);  // Additional space between nodes
        }
        printf("\n");

        if (currentDepth == depth) 
        {
            break;  // If this is the last level, don't print branches
        }

        // Calculate the space between the branches for the next level
        int subBranchSpace = (int)pow(2, depth - currentDepth - 1) - 1;
        nodeSpace = branchSpace * 2 + 1;

        // Print branches for current level
        for (int i = 0; i < nodeCount; ++i) 
        {
            // Only modify the spaces if we are not on the last level
            if (currentDepth < depth) 
            {
                // Calculate the spaces for the left padding and between branches
                int leftPadding = (int)pow(2, depth - currentDepth - 1) - 1;
                int spacesBetweenBranches = (int)pow(2, depth - currentDepth) - 1;

                // Print the left padding
                printChar(' ', leftPadding);
                
                // Print the left branch or space
                printf("%c", (levelNodes[i] != NULL && levelNodes[i]->left != NULL) ? '/' : ' ');
                
                // Print the spaces between branches
                printChar(' ', spacesBetweenBranches);
                
                // Print the right branch or space
                printf("%c", (levelNodes[i] != NULL && levelNodes[i]->right != NULL) ? '\\' : ' ');
                
                // Print the right padding
                printChar(' ', leftPadding + 1);  // +1 to account for the printed branch or space
            }
        }
        printf("\n");

        // Prepare for next level
        bstnode **newLevelNodes = (bstnode**) malloc(sizeof(bstnode*) * levelWidth * 2);
        for (int i = 0, j = 0; i < nodeCount; ++i) 
        {
            if (levelNodes[i] != NULL) 
            {
                newLevelNodes[j++] = levelNodes[i]->left;
                newLevelNodes[j++] = levelNodes[i]->right;
            } 
            else 
            {
                newLevelNodes[j++] = NULL;
                newLevelNodes[j++] = NULL;
            }
        }
        free(levelNodes);  // Free the memory for the current level
        levelNodes = newLevelNodes;  // Use new array for next level
        nodeCount *= 2;  // Double the node count for the next level
    }

    free(levelNodes);  // Free the memory for the last level
}
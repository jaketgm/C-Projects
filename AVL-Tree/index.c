/******************************************************************************
 * @author Jake Brockbank
 * Sep 26th, 2023
 * This code showcases insertion and traversal operations. The balancing 
 * nature of the AVL tree is maintained throughout, ensuring that operations 
 * like search, insert, and delete can be performed efficiently.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "AVL-Tree.h"

/******************************************************************************
 * Method: main: 
 * 
 * - This code showcases insertion and traversal operations. The balancing 
 * nature of the AVL tree is maintained throughout, ensuring that operations 
 * like search, insert, and delete can be performed efficiently.
 *
 * Input: None.
 *
 * Output: AVL tree with operations performed on it.
 *
******************************************************************************/
int main()
{
    avlNode *root = NULL;

    // Insert nodes into the AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Display the AVL tree after insertion
    printf("Preorder traversal of the constructed AVL tree after insertion is \n");
    preOrder(root);
    printf("\n");

    // Delete some nodes from the AVL tree
    root = deleteNode(root, 20); // Assuming deleteNode is the function name
    root = deleteNode(root, 30);

    // Display the AVL tree after deletion
    printf("Preorder traversal of the AVL tree after deletion is \n");
    preOrder(root);
    printf("\n");

    return 0;
}
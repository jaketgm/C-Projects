/******************************************************************************
 * @author Jake Brockbank
 * Dec 3rd, 2023
 * This code is for BST, inserting nodes, performing inorder traversal, 
 * deleting nodes, and freeing the tree's memory.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "binary-search-tree.h"

/******************************************************************************
 * Method: main: 
 * 
 * - This code is for BST, inserting nodes, performing inorder traversal, 
 * deleting nodes, and freeing the tree's memory.
 *
 * Input: None.
 *
 * Output: BST with operations performed on it.
 *
******************************************************************************/
int main() 
{
    bst *tree = createBST();

    insert(tree, 50);
    insert(tree, 30);
    insert(tree, 20);
    insert(tree, 40);
    insert(tree, 70);
    insert(tree, 60);
    insert(tree, 80);

    printf("Inorder traversal of the original tree: \n");
    inOrderTraverse(tree->root);
    
    // Note: Tree doesn't really print properly, but I couldn't get proper alignment lmao (You get the point)
    printf("\n\n");
    printf("\nTree structure:\n");
    printTree(tree->root);

    printf("\nDeleting 20\n");
    deleteBSTNode(tree, 20);
    printf("Inorder traversal after deleting 20: \n");
    inOrderTraverse(tree->root);

    printf("\n\n");
    printf("\nTree structure:\n");
    printTree(tree->root);

    printf("\nDeleting 30\n");
    deleteBSTNode(tree, 30);
    printf("Inorder traversal after deleting 30: \n");
    inOrderTraverse(tree->root);

    printf("\n\n");
    printf("\nTree structure:\n");
    printTree(tree->root);


    printf("\nDeleting 50\n");
    deleteBSTNode(tree, 50);
    printf("Inorder traversal after deleting 50: \n");
    inOrderTraverse(tree->root);

    printf("\n\n");
    printf("\nTree structure:\n");
    printTree(tree->root);


    freeBST(tree);

    return 0;
}
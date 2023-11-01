#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct weightedQuickUnionWithPathCompression
{
    int *id;
    int *size;
    int (*findRootWQUWPC)(struct weightedQuickUnionWithPathCompression *wQUWPC, int element);
    void (*unionPointsWQUWPC)(struct weightedQuickUnionWithPathCompression *wQUWPC, int p, int q);
    bool (*isConnectedWQUWPC)(struct weightedQuickUnionWithPathCompression *wQUWPC, int p, int q);
} weightedQUWPC;

/************************************************************************************
 * Method: initializeWeightedQUWPC: 
 * 
 * - It takes two parameters:
 *   - weightedQUWPC* wQUWPC: A pointer to the weightedQUWPC structure. 
 *   - int size: The number of elements in the data structure.
 * - It allocates memory for two integer arrays of size size using the malloc 
 * function:
 *   - wQU->id: This array will store the parent of each element. Initially, each 
 *     element is its own parent (representing a singleton set).
 *   - wQU->size: This array will store the size of each subtree, initially set to 
 *     1 for each element.
 *   - It then enters a loop that iterates through all elements from 0 to size 
 *     - 1 and initializes the arrays:
 *   - wQU->id[i] = i: It initializes the parent of each element to itself, 
 *     meaning each element starts as the root of its own tree.
 *   - wQU->size[i] = 1: It initializes the size of each subtree to 1, as each 
 *     element is initially in its own subtree.
 *
 * Input: weightedQUWPC* wQUWPC, int size.
 *
 * Output: Initialized Weighted Quick Union With Path Compression.
 *
************************************************************************************/
void initializeWeightedQUWPC(weightedQUWPC* wQUWPC, int size)
{
    wQUWPC->id = (int*) malloc(sizeof(int) * size);
    wQUWPC->size = (int*) malloc(sizeof(int) * size);
    int i;
    for (i = 0; i < size; i++)
    {
        wQUWPC->id[i] = i;
        wQUWPC->size[i] = 1;
    }
}

/************************************************************************************
 * Method: findRootWQUWPC: 
 * 
 * - It takes two parameters:
 *   - weightedQUWPC* wQUWPC: A pointer to the weightedQUWPC structure.
 *   - int element: The element for which you want to find the root 
 *     (leader) of its set.
 * - It initializes a variable root to the value of the input element. This 
 *   variable is used to track the current element as the code traverses the 
 *   tree to find the root.
 * - It enters a while loop that continues as long as the root is not equal to 
 *   the value stored in the id array at the same index. In a WQUWPC data 
 *   structure, the id array stores the parent of each element.
 * - Inside the loop, the code performs path compression by updating the parent 
 *   pointers along the path to the root. Specifically:
 *   - It sets the element (initially the root) to point directly to its grandparent 
 *     by assigning wQUWPC->id[wQUWPC->id[root]] to wQUWPC->id[root]. This reduces 
 *     the tree depth and flattens the tree structure.
 *   - The root is then updated to wQUWPC->id[root], which effectively makes it the 
 *     next element in the path to the root.
 * - The loop continues until root is equal to the value stored in the id array at the 
 *   same index, which indicates that the root of the set has been found.
 * - Finally, the function returns the root, which represents the root of the set to 
 *   which the original element belongs.
 *
 * Input: weightedQUWPC* wQUWPC, int element.
 *
 * Output: Returns the root.
 *
************************************************************************************/
int findRootWQUWPC(weightedQUWPC* wQUWPC, int element)
{
    int root = element;
    while (root != wQUWPC->id[root]) 
    {
        wQUWPC->id[root] = wQUWPC->id[wQUWPC->id[root]];
        root = wQUWPC->id[root];

    }
    return root;
}

/************************************************************************************
 * Method: unionPointsWQUWPC: 
 * 
 * - It takes three parameters:
 *   - weightedQUWPC* wQUWPC: A pointer to the weightedQUWPC structure.
 *   - int p: An element from one of the sets that you want to union.
 *   - int q: An element from the other set that you want to union.
 * - It calls the findRootWQUWPC function twice to find the roots of the sets to which 
 *   elements p and q belong. rootP and rootQ will represent the roots (leaders) of 
 *   these sets.
 * - It checks if rootP is equal to rootQ. If they are equal, it means that 
 *   elements p and q are already in the same set, so no union operation is 
 *   necessary, and the function returns without making any changes.
 * - If rootP is not equal to rootQ, it proceeds to perform the union operation. 
 *   It compares the sizes of the subtrees rooted at rootP and rootQ to determine 
 *   which tree should be attached to the other. The code checks which subtree is 
 *   larger and makes the smaller one a child of the larger one to balance the 
 *   tree sizes.
 * - After determining which tree should be the parent, the code updates the parent 
 *   pointer of rootP to rootQ, effectively making rootQ the new parent of the set 
 *   containing element p.
 * - It also updates the size of the subtree rooted at rootQ by adding the size of 
 *   the subtree rooted at rootP.
 *
 * Input: weightedQUWPC* wQUWPC, int p, int q.
 *
 * Output: Unions the two inputted points p and q.
 *
************************************************************************************/
void unionPointsWQUWPC(weightedQUWPC* wQUWPC, int p, int q) 
{
    int rootP = findRootWQUWPC(wQUWPC, p);
    int rootQ = findRootWQUWPC(wQUWPC, q);

    if (rootP == rootQ)
        return;

    if (wQUWPC->size[rootQ] > wQUWPC->size[rootP])
    {
        wQUWPC->id[rootP] = rootQ;
        wQUWPC->size[rootQ] += wQUWPC->size[rootP];
    }
    else
    {
        wQUWPC->id[rootP] = rootQ;
        wQUWPC->size[rootQ] += wQUWPC->size[rootP];
    }
}

/************************************************************************************
 * Method: isConnectedWQUWPC: 
 * 
 * - It takes three parameters:
 *   - weightedQUWPC* wQUWPC: A pointer to the weightedQUWPC structure.
 *   - int p: An element you want to check for connectivity.
 *   - int q: Another element you want to check for connectivity.
 * - It calls the findRootWQUWPC function twice with the input elements p and q. The 
 *   purpose of this is to find the roots (leaders) of the sets to which elements p 
 *   and q belong. findRootWQUWPC returns the root element for each element.
 * - It then compares the roots returned for elements p and q. If the roots are the 
 *   same, it means that both elements belong to the same set, and they are connected. 
 *   In this case, the function returns true to indicate connectivity.
 * - If the roots are different, it means that elements p and q belong to different 
 *   sets and are not connected. In this case, the function returns false to 
 *   indicate no connectivity.
 *
 * Input: weightedQUWPC* wQUWPC, int p, int q.
 *
 * Output: Returns true or false depending on whether the roots of p and q are
 * equal and thus unioned.
 *
************************************************************************************/
bool isConnectedWQUWPC(weightedQUWPC* wQUWPC, int p, int q)
{
    return findRootWQUWPC(wQUWPC, p) == findRootWQUWPC(wQUWPC, q);
}

/************************************************************************************
 * Method: freeWQUWPC: 
 * 
 * - Frees the allocated memory back to the heap for the id and size.
 *
 * Input: weightedQUWPC* wQUWPC.
 *
 * Output: Frees the allocated memory back to the heap.
 *
************************************************************************************/
void freeWQUWPC(weightedQUWPC* wQUWPC)
{
    free(wQUWPC->id);
    free(wQUWPC->size);
}

/************************************************************************************
 * Method: weightedQuickUnionWPCToString: 
 * 
 * - Creates a string with the id data.
 *
 * Input: weightedQUWPC* wQUWPC, int size.
 *
 * Output: Creates a string with the id data.
 *
************************************************************************************/
char *weightedQuickUnionWPCToString(weightedQUWPC* wQUWPC, int size)
{
    int maxChar = (size * 4) + 1;
    char *str = (char*) malloc(sizeof(char) * maxChar);

    if (str == NULL)
        return NULL;

    strcpy(str, "");

    int i;
    for (i = 0; i < size; i++)
    {
        char temp[5];
        snprintf(temp, sizeof(temp), "%d ", wQUWPC->id[i]);
        strcat(str, temp);
    }

    return str;
}

/************************************************************************************
 * Method: weightedQuickUnionWPCToStringSize: 
 * 
 * - Creates a string with the size data.
 *
 * Input: weightedQUWPC* wQUWPC, int size.
 *
 * Output: Creates a string with the size data.
 *
************************************************************************************/
char *weightedQuickUnionWPCToStringSize(weightedQUWPC* wQUWPC, int size)
{
    int maxChar = (size * 4) + 1;
    char *str = (char*) malloc(sizeof(char) * maxChar);

    if (str == NULL)
        return NULL;

    strcpy(str, "");

    int i;
    for (i = 0; i < size; i++)
    {
        char temp[5];
        snprintf(temp, sizeof(temp), "%d ", wQUWPC->size[i]);
        strcat(str, temp);
    }

    return str;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct WeightedQuickUnion
{
    int *id;
    int *size;
    int (*findRootWQU)(struct WeightedQuickUnion *wQU, int element);
    void (*unionPointsWQU)(struct WeightedQuickUnion *wQU, int p, int q);
    bool (*isConnectedWQU)(struct WeightedQuickUnion *wQU, int p, int q);
} weightedQU;

/************************************************************************************
 * Method: initializeWeightedQU: 
 * 
 * - It takes two parameters:
 *   - weightedQU* wQU: A pointer to the weightedQU structure. 
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
 * Input: weightedQU* wQU, int size.
 *
 * Output: Initialized Weighted Quick Union.
 *
************************************************************************************/
void initializeWeightedQU(weightedQU* wQU, int size)
{
    wQU->id = (int*) malloc(sizeof(int) * size);
    wQU->size = (int*) malloc(sizeof(int) * size);
    int i;
    for (i = 0; i < size; i++)
    {
        wQU->id[i] = i;
        wQU->size[i] = 1;
    }
}

/************************************************************************************
 * Method: findRootWQU: 
 * 
 * - It takes two parameters:
 *   - weightedQU* wQU: A pointer to the weightedQU structure.
 *   - int element: The element for which you want to find the root 
 *     (leader) of its set.
 * - It enters a while loop that continues as long as the element is not equal to 
 *   the value stored in the id array at the same index.
 * - Inside the loop, the code updates the element by setting it to the value 
 *   stored in the id array at that index. This process continues until element is 
 *   equal to the value stored in the id array at the same index. At this point, 
 *   element will represent the root of the set to which the original 
 *   element belongs.
 * - Finally, the function returns the element, which is now the root of the set to 
 *   which the original element belongs.
 *
 * Input: weightedQU* wQU, int element.
 *
 * Output: Returns the root.
 *
************************************************************************************/
int findRootWQU(weightedQU* wQU, int element)
{
    while (element != wQU->id[element]) 
    {
        element = wQU->id[element];
    }
    return element;
}

/************************************************************************************
 * Method: unionPointsWQU: 
 * 
 * - It takes three parameters:
 *   - weightedQU* wQU: A pointer to the weightedQU structure.
 *   - int p: An element from one of the sets that you want to union.
 *   - int q: An element from the other set that you want to union.
 * - It calls the findRootWQU function twice to find the roots of the sets to which 
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
 * Input: weightedQU* wQU, int p, int q.
 *
 * Output: Unions the two inputted points p and q.
 *
************************************************************************************/
void unionPointsWQU(weightedQU* wQU, int p, int q) 
{
    int rootP = findRootWQU(wQU, p);
    int rootQ = findRootWQU(wQU, q);

    if (rootP == rootQ)
        return;

    if (wQU->size[rootQ] > wQU->size[rootP])
    {
        wQU->id[rootP] = rootQ;
        wQU->size[rootQ] += wQU->size[rootP];
    }
    else
    {
        wQU->id[rootP] = rootQ;
        wQU->size[rootQ] += wQU->size[rootP];
    }
}

/************************************************************************************
 * Method: isConnectedWQU: 
 * 
 * - It takes three parameters:
 *   - weightedQU* wQU: A pointer to the weightedQU structure.
 *   - int p: An element you want to check for connectivity.
 *   - int q: Another element you want to check for connectivity.
 * - It calls the findRootWQU function twice with the input elements p and q. The 
 *   purpose of this is to find the roots (leaders) of the sets to which elements p 
 *   and q belong. findRootWQU returns the root element for each element.
 * - It then compares the roots returned for elements p and q. If the roots are the 
 *   same, it means that both elements belong to the same set, and they are connected. 
 *   In this case, the function returns true to indicate connectivity.
 * - If the roots are different, it means that elements p and q belong to different 
 *   sets and are not connected. In this case, the function returns false to 
 *   indicate no connectivity.
 *
 * Input: weightedQU* wQU, int p, int q.
 *
 * Output: Returns true or false depending on whether the roots of p and q are
 * equal and thus unioned.
 *
************************************************************************************/
bool isConnectedWQU(weightedQU* wQU, int p, int q)
{
    return findRootWQU(wQU, p) == findRootWQU(wQU, q);
}

/************************************************************************************
 * Method: freeWQU: 
 * 
 * - Frees the allocated memory back to the heap for the id and size.
 *
 * Input: weightedQU* wQU.
 *
 * Output: Frees the allocated memory back to the heap.
 *
************************************************************************************/
void freeWQU(weightedQU* wQU)
{
    free(wQU->id);
    free(wQU->size);
}

/************************************************************************************
 * Method: weightedQuickUnionToString: 
 * 
 * - Creates a string with the id data.
 *
 * Input: weightedQU* wQU, int size.
 *
 * Output: Creates a string with the id data.
 *
************************************************************************************/
char *weightedQuickUnionToString(weightedQU* wQU, int size)
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
        snprintf(temp, sizeof(temp), "%d ", wQU->id[i]);
        strcat(str, temp);
    }

    return str;
}

/************************************************************************************
 * Method: weightedQuickUnionToStringSize: 
 * 
 * - Creates a string with the size data.
 *
 * Input: weightedQU* wQU, int size.
 *
 * Output: Creates a string with the size data.
 *
************************************************************************************/
char *weightedQuickUnionToStringSize(weightedQU* wQU, int size)
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
        snprintf(temp, sizeof(temp), "%d ", wQU->size[i]);
        strcat(str, temp);
    }

    return str;
}
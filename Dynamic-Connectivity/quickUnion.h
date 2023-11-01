#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct QuickUnion 
{
    int *id;
    int size;
    int (*findRoot)(struct QuickUnion *qu, int element);
    void (*unionPointsQU)(struct QuickUnion *qu, int p, int q);
    bool (*isConnectedQU)(struct QuickUnion *qu, int p, int q);
} quickunion;

/************************************************************************************
 * Method: initializeQU: 
 * 
 * - It takes two parameters:
 *   - quickunion *qu: A pointer to the quickunion structure.
 *   - int size: The number of elements in the data structure.
 * - It sets the size member of the qu structure to the value of the input size. 
 *   This indicates the total number of elements in the data structure.
 * - It allocates memory for an integer array, qu->id, of size size using the 
 *   malloc function. This array will be used to store the parent of each element. 
 *   Initially, each element is its own parent, representing a singleton set.
 * - It enters a loop that iterates through all elements from 0 to size - 1 and 
 *   initializes the qu->id array:
 * - qu->id[i] = i: It initializes the parent of each element to itself, meaning 
 *   each element starts as the root of its own tree.
 *
 * Input: quickunion *qu, int size.
 *
 * Output: Initialized Quick Union.
 *
************************************************************************************/
void initializeQU(quickunion *qu, int size) 
{
    qu->size = size;
    qu->id = (int*) malloc(sizeof(int) * size);
    int i;
    for (i = 0; i < size; i++)
        qu->id[i] = i;
}

/************************************************************************************
 * Method: findRoot: 
 * 
 * - It takes two parameters:
 *   - quickunion *qu: A pointer to the quickunion structure.
 *   - int element: The element for which you want to find the root (leader) of its set.
 * - It performs input validation:
 *   - It checks if the input qu is NULL, or if the input element is less than 0 or 
 *     greater than or equal to the size of the data structure (qu->size). If any of 
 *     these conditions is met, the function returns -1, indicating an error or an 
 *     invalid input.
 * - It enters a while loop that continues as long as the element is not equal to the 
 *   value stored in the id array at the same index. In a QU data structure, the 
 *   id array stores the parent of each element.
 * - Inside the loop, the code updates the element by setting it to the value stored 
 *   in the id array at that index. This process continues until element is equal 
 *   to the value stored in the id array at the same index. At this point, 
 *   element will represent the root of the set to which the original element belongs.
 * - Finally, the function returns the element, which is now the root of the set to 
 *   which the original element belongs.
 *
 * Input: quickunion *qu, int element.
 *
 * Output: Returns the root.
 *
************************************************************************************/
int findRoot(quickunion *qu, int element) 
{
    if (qu == NULL || element < 0 || element >= qu->size) 
        return -1;

    while (element != qu->id[element]) 
    {
        element = qu->id[element];
    }
    return element;
}

/************************************************************************************
 * Method: unionPointsQU: 
 * 
 * - It takes three parameters:
 *   - quickunion *qu: A pointer to the quickunion structure.
 *   - int p: An element from one of the sets that you want to union.
 *   - int q: Another element from the other set that you want to union.
 * - It performs input validation:
 *   - It checks if the input qu is NULL, and if so, it prints an error message and 
 *     returns. This is to handle cases where the qu pointer is invalid.
 *   - It also checks if p and q are out of bounds, meaning they are less than 0 or 
 *     greater than or equal to the size of the data structure (qu->size). If either 
 *     p or q is out of bounds, it prints an error message and returns. This is to 
 *     handle cases where the input elements are invalid.
 * - It then calls the findRoot function twice to find the roots of the sets to which 
 *   elements p and q belong. rootP and rootQ will represent the roots (leaders) of 
 *   these sets.
 * - It checks if rootP is not equal to rootQ. If they are not equal, it means that 
 *   elements p and q belong to different sets, and a union operation is needed.
 * - If rootP and rootQ are not the same, it performs the union operation by 
 *   updating the parent pointer of rootP to rootQ. This makes rootQ the parent 
 *   of the set containing element p, effectively merging the two sets.
 *
 * Input: quickunion *qu, int p, int q.
 *
 * Output: Unions the two inputted points p and q.
 *
************************************************************************************/
void unionPointsQU(quickunion *qu, int p, int q) 
{
    if (qu == NULL) 
    {
        printf("Error: quickunion pointer is null\n");
        return;
    }

    if (p < 0 || p >= qu->size || q < 0 || q >= qu->size) 
    {
        printf("Error: p or q is out of bounds\n");
        return;
    }

    int rootP = findRoot(qu, p);
    int rootQ = findRoot(qu, q);

    if (rootP != rootQ) 
        qu->id[rootP] = rootQ;
}

/************************************************************************************
 * Method: isConnectedQU: 
 * 
 * - It takes three parameters:
 *   - quickunion *qu: A pointer to the quickunion structure.
 *   - int p: An element you want to check for connectivity.
 *   - int q: Another element you want to check for connectivity.
 * - It calls the findRoot function twice with the input elements p and q. The
 *   purpose of this is to find the roots (leaders) of the sets to which elements p 
 *   and q belong. findRoot returns the root element for each element.
 * - It then compares the roots returned for elements p and q. If the roots are the 
 *   same, it means that both elements belong to the same set, and they are connected. 
 *   In this case, the function returns true to indicate connectivity.
 * - If the roots are different, it means that elements p and q belong to different 
 *   sets and are not connected. In this case, the function returns false to 
 *   indicate no connectivity.
 *
 * Input: quickunion* qu, int p, int q.
 *
 * Output: Returns true or false depending on whether the roots of p and q are
 * equal and thus unioned.
 *
************************************************************************************/
bool isConnectedQU(quickunion* qu, int p, int q)
{
    return findRoot(qu, p) == findRoot(qu, q);
}

/************************************************************************************
 * Method: freeQU: 
 * 
 * - Frees the allocated memory back to the heap for the id.
 *
 * Input: quickunion* qu.
 *
 * Output: Frees the allocated memory back to the heap.
 *
************************************************************************************/
void freeQU(quickunion* qu)
{
    free(qu->id);
}

/************************************************************************************
 * Method: quickUnionToString: 
 * 
 * - Creates a string with the id data.
 *
 * Input: quickunion* qu.
 *
 * Output: Creates a string with the id data.
 *
************************************************************************************/
char *quickUnionToString(quickunion* qu)
{
    int maxChar = (qu->size * 4) + 1;
    char *str = (char*) malloc(sizeof(char) * maxChar);

    if (str == NULL)
        return NULL;

    strcpy(str, "");

    int i;
    for (i = 0; i < qu->size; i++)
    {
        char temp[5];
        snprintf(temp, sizeof(temp), "%d ", qu->id[i]);
        strcat(str, temp);
    }

    return str;
}
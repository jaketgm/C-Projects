#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/************************************************************************************
 * We have pointers to functions in the structure to allow for 
 * "polymorphism"/function overloading if needed by the desired user. 
 * This makes it so that we can do something like: 
 * 
 * quickunion myQU1;
 * myQU1.findRoot = findRootImplementation1;
 * myQU1.unionPointsQU = unionPointsQUImplementation1;
 * myQU1.isConnectedQU = isConnectedQUImplementation1;
 * 
 * quickunion myQU2;
 * myQU2.findRoot = findRootImplementation2;
 * myQU2.unionPointsQU = unionPointsQUImplementation2;
 * myQU2.isConnectedQU = isConnectedQUImplementation2;
 * 
 * If that is what is desired, I will not be doing this; however I'am simply making
 * this program easily adaptable to depend on an arbitrary list of requirements.
 * (Note: I will continue to do this for the rest of the algorithms.)
************************************************************************************/
typedef struct QuickFind
{
    int *id;
    int size;
    void (*unionPoints)(struct QuickFind* qf, int p, int q);
    bool (*isConnected)(struct QuickFind* qf, int p, int q);
} quickfind;

/************************************************************************************
 * Method: initializeQF: 
 * 
 * - It takes two parameters:
 *   - quickfind *qf: A pointer to the quickfind structure.
 *   - int size: The number of elements in the data structure.
 * - It sets the size member of the qf structure to the value of the input size. 
 *   This indicates the total number of elements in the data structure.
 * - It allocates memory for an integer array, qf->id, of size size using the 
 *   malloc function. This array will be used to store the set membership information
 *   for each element. Initially, each element belongs to its own set, and the 
 *   value of qf->id[i] is set to i for each element.
 * - It enters a loop that iterates through all elements from 0 to size - 1 and 
 *   initializes the qf->id array:
 * - qf->id[i] = i: It initializes the set membership for each element such that 
 *   each element is in its own set, identified by its own unique identifier.
 *
 * Input: quickfind* qf, int size.
 *
 * Output: Initialized Quick Find.
 *
************************************************************************************/
void initializeQF(quickfind* qf, int size) 
{
    qf->size = size;
    qf->id = (int*) malloc(sizeof(int) * size);
    int i;
    for (i = 0; i < size; i++)
        qf->id[i] = i;
}

/************************************************************************************
 * Method: unionPoints: 
 * 
 * - It takes three parameters:
 *   - quickfind *qf: A pointer to the quickfind structure.
 *   - int p: An element from one of the sets that you want to union.
 *   - int q: Another element from the other set that you want to union.
 * - It initializes a temporary variable tempP to store the set identifier for 
 *   element p. This is done to make it easier to identify and update elements in 
 *   the same set as p to match the set identifier of element q.
 * - It retrieves the size of the data structure and stores it in the size 
 *   variable.
 * - It enters a loop that iterates through all elements from 0 to size - 1.
 * - Inside the loop, it checks if the set identifier (qf->id[i]) of an element 
 *   matches the set identifier of element p (tempP).
 * - If the set identifier of an element matches tempP, it means that the element 
 *   is in the same set as p.
 * - In this case, it updates the set identifier of that element (qf->id[i]) to 
 *   match the set identifier of element q (by setting it to qf->id[q]).
 * - The loop continues until all elements in the data structure have been 
 *   checked.
 *
 * Input: quickfind* qf, int p, int q.
 *
 * Output: Unions the two inputted points p and q.
 *
************************************************************************************/
void unionPoints(quickfind* qf, int p, int q)
{
    int tempP = qf->id[p];
    int size = qf->size;

    int i;
    for (i = 0; i < size; i++)
    {
        if (qf->id[i] == tempP)
        {
            qf->id[i] = qf->id[q];
        }
    }
}

/************************************************************************************
 * Method: isConnected: 
 * 
 * - It takes three parameters:
 *   - quickfind *qf: A pointer to the quickfind structure.
 *   - int p: An element you want to check for connectivity.
 *   - int q: Another element you want to check for connectivity.
 * - It compares the set identifiers (qf->id[p] and qf->id[q]) of elements p and 
 *   q to determine if they are the same.
 * - If the set identifiers are the same, it means that both elements belong to the 
 *   same set, and they are connected. In this case, the function returns true 
 *   to indicate connectivity.
 * - If the set identifiers are different, it means that elements p and q belong to 
 *   different sets and are not connected. In this case, the function returns false 
 *   to indicate no connectivity.
 *
 * Input: quickfind* qf, int p, int q.
 *
 * Output: Returns true or false depending on whether the roots of p and q are
 * equal and thus unioned.
 *
************************************************************************************/
bool isConnected(quickfind* qf, int p, int q)
{
    return qf->id[p] == qf->id[q];
}

/************************************************************************************
 * Method: freeQF: 
 * 
 * - Frees the allocated memory back to the heap for the id.
 *
 * Input: quickfind* qf.
 *
 * Output: Frees the allocated memory back to the heap.
 *
************************************************************************************/
void freeQF(quickfind* qf)
{
    free(qf->id);
}

/************************************************************************************
 * Method: quickFindToString: 
 * 
 * - Creates a string with the id data.
 *
 * Input: quickfind* qf.
 *
 * Output: Creates a string with the id data.
 *
************************************************************************************/
char *quickFindToString(quickfind* qf)
{
    int maxChar = (qf->size * 4) + 1;
    char *str = (char*) malloc(sizeof(char) * maxChar);

    if (str == NULL)
    {
        return NULL;
    }

    strcpy(str, "");

    int i;
    for (i = 0; i < qf->size; i++)
    {
        char temp[5];
        snprintf(temp, sizeof(temp), "%d ", qf->id[i]);
        strcat(str, temp);
    }

    return str;
}
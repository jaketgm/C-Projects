#define initialCapacity 10

typedef struct ArrayList
{
    int *list;
    int capacity;
    int load;
} arrayList;

/************************************************************************************
 * Method: createArrayList: 
 * 
 * - ArrayList *newArrayList = (arrayList*) malloc(sizeof(arrayList));: This line 
 * allocates memory on the heap for a new arrayList structure. The arrayList 
 * structure likely contains information about the ArrayList, such as its 
 * capacity, the number of elements it currently holds, and a pointer to the 
 * array that stores the elements.
 * - newArrayList->capacity = initialCapacity;: It sets the initial capacity of 
 * the ArrayList. initialCapacity is a variable or constant that represents the 
 * initial size of the array. This capacity determines how many elements the 
 * ArrayList can hold before it needs to be resized.
 * - newArrayList->load = 0;: It initializes the load attribute to 0. The load 
 * likely represents the number of elements currently stored in the ArrayList. 
 * Since the ArrayList is created empty, the load is set to 0 initially.
 * - newArrayList->list = (int*) malloc(sizeof(int) * initialCapacity);: This line 
 * allocates memory for the array that will hold the elements of the ArrayList. It 
 * allocates memory for an array of integers with a size of initialCapacity. The 
 * pointer to this array is stored in the list attribute of the newArrayList 
 * structure.
 * - Finally, the function returns a pointer to the newly created and initialized 
 * arrayList structure.
 *
 * Input: None.
 *
 * Output: newArrayList.
 *
************************************************************************************/
arrayList *createArrayList()
{
    arrayList *newArrayList = (arrayList*) malloc(sizeof(arrayList));
    newArrayList->capacity = initialCapacity;
    newArrayList->load = 0;
    newArrayList->list = (int*) malloc(sizeof(int) * initialCapacity);
    return newArrayList;
}

/************************************************************************************
 * Method: createArrayList: 
 * 
 * - void insert(int k, arrayList *myList): This is the function signature. It 
 * takes two parameters:
 *   - int k: The integer value to be inserted into the ArrayList.
 *   - arrayList *myList: A pointer to the ArrayList where the element will be 
 *     inserted.
 * - The function first checks if the current load (number of elements) in the 
 * ArrayList is equal to its capacity. If the load is equal to the capacity, it means 
 * that the ArrayList is full and needs to be resized to accommodate additional 
 * elements.
 * - Inside the if condition:
 * - myList->capacity *= 2;: The capacity of the ArrayList is doubled. This ensures 
 * that the ArrayList can hold more elements without frequent resizing.
 * - myList->list = (int*) realloc(myList->list, sizeof(int) * myList->capacity);: 
 * Memory is reallocated for the internal array of the ArrayList. The realloc 
 * function is used to change the size of the dynamically allocated array. In this 
 * case, it doubles the capacity by reallocating memory for an array of integers 
 * of the new size (myList->capacity).
 * - Regardless of whether the ArrayList needed resizing, the code continues:
 *   - myList->list[myList->load] = k;: The element k is inserted at the index 
 *     specified by the current load. The load attribute indicates the number of 
 *     elements in the ArrayList, and it is used as the index where the new element 
 *     should be placed.
 *   - myList->load++;: The load attribute is incremented to reflect that a 
 *     new element has been added to the ArrayList.
 *
 * Input: int k, arrayList *myList.
 *
 * Output: Inserts an Integer k Into my List.
 *
************************************************************************************/
void insert(int k, arrayList *myList)
{
    if (myList->load == myList->capacity)
    {
        myList->capacity *= 2;
        myList->list = (int*) realloc(myList->list, sizeof(int) * myList->capacity);
    }

    myList->list[myList->load] = k;
    myList->load++;
}

/************************************************************************************
 * Method: sortArrayList: 
 * 
 * - void sortArrayList(arrayList *myList): This is the function signature. It 
 * takes one parameter, which is a pointer to the ArrayList that needs to be sorted.
 * - The function uses two nested loops to perform the sorting. The outer loop, 
 * controlled by the variable i, iterates through the elements of the ArrayList from 
 * the first element to the second-to-last element (myList->load - 1 is the index of 
 * the last element, and it doesn't need to be considered after the first pass).
 * - Within the outer loop, there is an inner loop controlled by the variable j, 
 * which iterates from the first element to the last unsorted element in the 
 * ArrayList 
 * (myList->load - i - 1 represents the number of unsorted elements in each pass).
 * - The inner loop compares adjacent elements of the ArrayList using the condition 
 * if (myList->list[j] > myList->list[j + 1]). If the element at index j is greater 
 * than the element at index j + 1, it means that they are in the wrong order, 
 * and a swap is performed to rearrange them in ascending order. The temp variable 
 * is used to facilitate the swap.
 * - After the inner loop completes a pass, the largest element in the unsorted 
 * portion of the ArrayList has "bubbled up" to the end of the ArrayList. The 
 * outer loop then continues with the next pass.
 * - This process continues until the entire ArrayList is sorted in ascending order.
 *
 * Input: arrayList *myList.
 *
 * Output: Sorts the ArrayList.
 *
************************************************************************************/
void sortArrayList(arrayList *myList) 
{
    int i, j, temp;

    for (i = 0; i < myList->load - 1; i++) 
    {
        for (j = 0; j < myList->load - i - 1; j++) 
        {
            if (myList->list[j] > myList->list[j + 1]) 
            {
                temp = myList->list[j];
                myList->list[j] = myList->list[j + 1];
                myList->list[j + 1] = temp;
            }
        }
    }
}

/************************************************************************************
 * Method: freeArrayList: 
 * 
 * - void freeArrayList(arrayList *myList): This is the function signature. It 
 * takes one parameter, which is a pointer to the ArrayList (myList) that needs to
 * be deallocated.
 * - free(myList->list);: This line deallocates the memory for the internal array 
 * of the ArrayList. It uses the free function to release the memory that was 
 * previously allocated for the array. This is crucial to prevent memory leaks.
 * - free(myList);: This line deallocates the memory for the ArrayList itself. 
 * It releases the memory allocated for the arrayList structure, which contains 
 * information about the ArrayList, including its capacity and load.
 *
 * Input: arrayList *myList.
 *
 * Output: Frees Heap Memory Allocated to the List.
 *
************************************************************************************/
void freeArrayList(arrayList *myList)
{
    free(myList->list);
    free(myList);
}
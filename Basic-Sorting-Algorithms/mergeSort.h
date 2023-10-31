void merge(int *leftArray, int *rightArray, int *array, int leftArraySize, int rightArraySize, int size);

/************************************************************************************
 * Method: mergeSort: 
 * 
 * - The mergeSort function takes two parameters:
 *   - int *array: A pointer to an array of integers that you want to sort.
 *   - int size: The number of elements in the array.
 * - The function serves as a recursive implementation of the Merge Sort algorithm 
 * and operates as follows:
 * - The base case for the recursion is when the size of the array is 1 or less. In 
 * this case, no sorting is required, so the function simply returns.
 * - If the array has more than one element, it calculates the middle index of the 
 * array by dividing the size by 2. This determines where the array is divided into 
 * two sub-arrays, leftArray and rightArray.
 * - It then declares two new arrays, leftArray and rightArray, to store the 
 * elements of the left and right sub-arrays. The sizes of these sub-arrays are 
 * calculated based on the middle index.
 * - The function enters a loop that iterates through the original array. It copies 
 * elements from the original array to the leftArray until it reaches the middle 
 * index. After that, it starts copying elements to the rightArray.
 * - After the loop completes, the leftArray contains the left sub-array of elements, 
 * and the rightArray contains the right sub-array of elements.
 * - The function then recursively calls itself to sort the leftArray and 
 * rightArray. This step effectively divides the problem into smaller 
 * sub-problems.
 * - Finally, the merge function is called to merge the sorted leftArray and 
 * rightArray back into the original array in sorted order.
 *
 * Input: int *array, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void mergeSort(int *array, int size)
{
    if (size <= 1)
        return;

    int middle = size / 2;
    int leftArray[middle];
    int rightArray[size - middle];

    int i;
    int j = 0;

    for (i = 0; i < size; i++)
    {
        if (i < middle)
        {
            leftArray[i] = array[i];
        }
        else
        {
            rightArray[j] = array[i];
            j++;
        }
    }
    mergeSort(leftArray, middle);
    mergeSort(rightArray, size - middle);
    merge(leftArray, rightArray, array, middle, size - middle, size);
}

/************************************************************************************
 * Method: merge: 
 * 
 * - The merge function takes six parameters:
 *   - int *leftArray: A pointer to the left sub-array of integers.
 *   - int *rightArray: A pointer to the right sub-array of integers.
 *   - int *array: A pointer to the target array where the merged result will be 
 *     stored.
 *   - int leftArraySize: The number of elements in the left sub-array.
 *   - int rightArraySize: The number of elements in the right sub-array.
 *   - int size: The total number of elements to merge 
 *     (sum of leftArraySize and rightArraySize).
 * - The function begins by reassigning the values of leftArraySize and 
 * rightArraySize based on the size parameter. 
 * - It initializes three variables: i to keep track of the position in the merged 
 * array, l to keep track of the position in the left sub-array, and r to keep 
 * track of the position in the right sub-array.
 * - The function enters a loop that continues as long as both l 
 * (the position in the left sub-array) is less than leftArraySize and r 
 * (the position in the right sub-array) is less than rightArraySize. This loop 
 * is used to merge the two sub-arrays.
 * - Within the loop, the function compares the elements at positions l in the 
 * left sub-array and r in the right sub-array. If the element in the left sub-array 
 * is smaller, it is copied to the merged array at position i. If the element in the 
 * right sub-array is smaller, it is copied to the merged array at position i. In 
 * both cases, i, l, and r are incremented to move to the next position in their 
 * respective arrays.
 * - After the loop, there may still be remaining elements in either the left or right 
 * sub-array. Two additional loops are used to copy any remaining elements from the 
 * left and right sub-arrays to the merged array. This ensures that all elements from 
 * both sub-arrays are properly merged into the final sorted array.
 *
 * Input: int *leftArray, int *rightArray, int *array, int leftArraySize, 
 * int rightArraySize, int size.
 *
 * Output: Merged Lists.
 *
************************************************************************************/
void merge(int *leftArray, int *rightArray, int *array, int leftArraySize, int rightArraySize, int size)
{
    leftArraySize = size / 2;
    rightArraySize = size - leftArraySize;
    int i = 0, l = 0, r = 0;

    while (l < leftArraySize && r < rightArraySize)
    {
        if (leftArray[l] < rightArray[r])
        {
            array[i] = leftArray[l];
            i++;
            l++;
        }
        else
        {
            array[i] = rightArray[r];
            i++;
            r++;
        }
    }
    while (l < leftArraySize)
    {
        array[i] = leftArray[l];
        i++;
        l++;
    }
    while (r < rightArraySize)
    {
        array[i] = rightArray[r];
        i++;
        r++;
    }
}
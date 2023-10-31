/************************************************************************************
 * Method: selectionSort: 
 * 
 * - The selectionSort function takes two parameters:
 *   - int *array: A pointer to an array of integers that you want to sort.
 *   - int size: The number of elements in the array.
 * - The function uses two nested loops to sort the array:
 * - The outer loop iterates through the array from the first element (index 0) to 
 * the second-to-last element (index size - 2). The reason it stops at size - 2 is 
 * that, after the last element is considered in the second-to-last iteration, the 
 * entire array will be sorted, so there's no need to consider it again.
 * - Within the outer loop, a variable min is initialized to the current value of i, 
 * representing the index of the minimum element in the unsorted portion of the 
 * array. i is the current position of the element being considered as the 
 * minimum.
 * - The inner loop starts from the element next to the current element 
 * (at index i + 1) and continues to the end of the array (size - 1). It looks 
 * for an element that is smaller than the element at the current min index. If 
 * such an element is found, its index is assigned to min.
 * - After the inner loop completes, min contains the index of the smallest 
 * element in the unsorted portion of the array.
 * - If min is not equal to i, it means that a smaller element was found in 
 * the unsorted portion. In this case, a swap is performed to move the smallest 
 * element to its correct position in the sorted portion of the array. The 
 * element at index i is swapped with the element at index min.
 * - This process continues in the outer loop, where the next smallest element 
 * in the unsorted portion is found and moved to the appropriate position in 
 * the sorted portion.
 * - The result is that, after the outer loop completes, the entire array is 
 * sorted in ascending order, with the smallest element at the beginning.
 *
 * Input: int *array, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void selectionSort(int *array, int size)
{
    int i, j, min, temp;
    for (i = 0; i < size - 1; i++)
    {
        min = i;
        for (j = i+1; j < size; j++)
        {
            if (array[j] < array[min])
                min = j;
        }

        int temp = array[min];
        array[min] = array[i];
        array[i] = temp;
    }
}
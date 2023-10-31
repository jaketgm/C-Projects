/************************************************************************************
 * Method: quickSort: 
 * 
 * - The quickSort function takes two parameters:
 *   - int *array: A pointer to an array of integers that you want to sort.
 *   - int size: The number of elements in the array.
 * - The function serves as a recursive implementation of the Quick Sort algorithm 
 * and operates as follows:
 * - The base case for the recursion is when the size of the array is 1 or less. 
 * In this case, no sorting is required, so the function simply returns.
 * - If the array has more than one element, the function selects a pivot element. 
 * In this implementation, the pivot is the last element in the array 
 * (array[size - 1]).
 * - It initializes two pointers, i and j, where i is initially set to -1. i and j 
 * are used to divide the array into two sub-arrays: elements less than the pivot 
 * and elements greater than or equal to the pivot.
 * - The function enters a loop that iterates through the array from index 0 to 
 * size - 2. Within this loop, it compares each element with the pivot. If an 
 * element is less than the pivot, it swaps that element with the element at the 
 * position i + 1, effectively moving smaller elements to the left side of the 
 * sub-array.
 * - After the loop completes, all elements less than the pivot are on the left 
 * side of the array, and all elements greater than or equal to the pivot are 
 * on the right side.
 * - The pivot element is then moved to its correct position in the sorted 
 * array, which is between the two sub-arrays.
 * - The function then recursively calls itself to sort the left sub-array, 
 * which includes elements less than the pivot.
 * - It also recursively calls itself to sort the right sub-array, which 
 * includes elements greater than or equal to the pivot.
 * - The recursion continues until the base case is reached 
 * (i.e., until sub-arrays have only one element or less).
 *
 * Input: int *array, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void quickSort(int *array, int size)
{
    if (size <= 1)
        return;

    int pivot = array[size - 1];

    int i = -1;
    int j;
    
    for (j = 0; j < size - 1; j++)
    {
        if (array[j] < pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[size - 1];
    array[size - 1] = temp;

    quickSort(array, i + 1);
    quickSort(array + i + 2, size - i - 2); 
}
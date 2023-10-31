/************************************************************************************
 * Method: insertionSort: 
 * 
 * - The insertionSort function takes two parameters:
 *   - int *array: A pointer to an array of integers that you want to sort.
 *   - int size: The number of elements in the array.
 * - The function uses two nested loops to sort the array:
 * - The outer loop iterates through the array, starting from the second element 
 * (index 1) to the last element (index size - 1). The reason it starts from the 
 * second element is that a single element is considered sorted by default.
 * - Within the outer loop, the current element to be inserted is stored in a 
 * variable temp, and a variable j is initialized to the index of the element 
 * immediately before the current element (i.e., i - 1).
 * - The inner loop, which is a while loop, checks two conditions:
 *   - j is greater than or equal to 0, ensuring that we don't access an element 
 *     before the beginning of the array.
 *   - array[j] is greater than temp, indicating that the element at index j is 
 *     greater than the current element to be inserted.
 * - If both conditions are met, it means that the element at index j should be 
 * moved one position to the right to make room for the temp element. This is 
 * done by assigning array[j] to array[j+1].
 * - The loop continues to move elements to the right until a condition is met 
 * where either j is less than 0 
 * (indicating that no further movement is necessary) or the element at j is no 
 * longer greater than temp.
 * - After the inner loop completes, the element at index j+1 
 * (where j+1 is the correct position for the temp element) is assigned the 
 * value of temp.
 * - This process continues in the outer loop, where each element is taken 
 * from the unsorted portion and inserted into its correct position within 
 * the sorted portion of the array.
 * - The result is that, after the outer loop completes, the entire array 
 * is sorted in ascending order.
 *
 * Input: int *array, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void insertionSort(int *array, int size)
{
    int i, j, temp;
    for (i = 1; i < size; i++)
    {
        temp = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > temp)
        {
            array[j+1] = array[j];
            j -= 1;
        }
        array[j+1] = temp;
    }
}
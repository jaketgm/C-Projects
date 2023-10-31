/************************************************************************************
 * Method: bubbleSort: 
 * 
 * - The bubbleSort function takes two parameters:
 *   - int *array: A pointer to an array of integers that you want to sort.
 *   - int size: The number of elements in the array.
 * - The function uses two nested loops to sort the array:
 * - The outer loop, controlled by the variable i, iterates through the array from 
 * the beginning (index 0) to the second-to-last element (index size - 2). The reason 
 * it stops at size - 2 is that, after the last pass of the inner loop, the largest 
 * element will have "bubbled up" to the last position, so it doesn't need to be 
 * considered again.
 * - Within the outer loop, a boolean variable isSwapped is initialized to false. 
 * This variable is used to track whether any swaps were made during the pass. It is 
 * set to false at the beginning of each pass.
 * - The inner loop, controlled by the variable j, starts from the beginning of 
 * the array (index 0) and continues to the end of the unsorted portion 
 * (index size - i - 1). This inner loop is responsible for comparing adjacent 
 * elements and swapping them if they are in the wrong order.
 * - If array[j] is greater than array[j+1], it means that the current element is 
 * larger than the next element. In this case, a swap is performed to move the 
 * larger element to the right. The variables temp are used to facilitate the 
 * swap.
 * - After a swap is made, isSwapped is set to true, indicating that at least 
 * one swap occurred during this pass.
 * - After the inner loop completes, the largest element in the unsorted 
 * portion has "bubbled up" to the end of the array, so it is in its correct 
 * sorted position.
 * - The outer loop then checks if isSwapped is still false. If it is, that 
 * means no swaps were made during this pass, and the array is already sorted. 
 * In this case, the algorithm breaks out of the outer loop and terminates early.
 * - The result is that, after the outer loop completes, the entire array is 
 * sorted in ascending order. The algorithm optimizes by breaking out of the 
 * loop early if no swaps are made during a pass, as that indicates the array 
 * is already sorted.
 *
 * Input: int *array, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void bubbleSort(int *array, int size)
{
    int i, j, temp;
    bool isSwapped;
    for (i = 0; i < size - 1; i++)
    {
        isSwapped = false;
        for (j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j+1])
            {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                isSwapped = true;
            }
        }     

        if (!isSwapped)
            break;
    }
}
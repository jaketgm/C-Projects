/************************************************************************************
 * Method: cocktailSort: 
 * 
 * - The cocktailSort function takes two parameters:
 *   - int *array: A pointer to an array of integers that you want to sort.
 *   - int size: The number of elements in the array.
 * - The function starts with a variable isSwapped set to true, indicating that the 
 * algorithm should continue sorting.
 * - The outer loop continues until isSwapped is false, which means that no swaps 
 * were made during the last pass, indicating that the array is sorted. This loop 
 * handles the bidirectional pass of the Cocktail Sort.
 * - Inside the outer loop, the variable start is used to keep track of the starting 
 * point for the next pass. start is initially set to 0.
 * - The first inner loop moves from start to size - 1. It compares adjacent 
 * elements and swaps them if they are out of order. If a swap is made, 
 * isSwapped is set to true, indicating that at least one swap occurred during 
 * this pass.
 * - After the first inner loop completes, the function checks if isSwapped is 
 * still true. If it's not, that means no swaps were made during this pass, and 
 * the array is already sorted. In this case, the algorithm breaks out of the outer 
 * loop and terminates early.
 * - If isSwapped is still true, the function resets isSwappedtofalse` to 
 * prepare for the next pass.
 * - The variable size is decreased by 1 to reduce the range of elements to be 
 * considered in the next pass. This is because, after each pass, the largest 
 * (or smallest) element in the unsorted part of the array "bubbles" to its correct 
 * position, so it doesn't need to be considered in subsequent passes.
 * - The second inner loop starts from size - 1 and moves backward to start. 
 * Similar to the first inner loop, it compares adjacent elements and swaps them 
 * if necessary. If a swap occurs, isSwapped is set to true.
 * - After the second inner loop completes, the start variable is incremented to 
 * prepare for the next pass.
 * - The algorithm continues with the next bidirectional pass, and the process 
 * repeats until the entire array is sorted. If no swaps occur during a 
 * complete pass, the array is considered sorted, and the algorithm 
 * terminates early.
 *
 * Input: int *array, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void cocktailSort(int *array, int size)
{
    int i, start, temp;
    bool isSwapped = true;

    while (isSwapped == true)
    {
        isSwapped = false;

        for (i = start; i < size - 1; i++)
        {
            if (array[i] > array[i+1])
            {
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                isSwapped = true;
            }
        }

        if (!isSwapped)
            break;

        isSwapped = false;
        size -= 1;

        for (i = size - 1; i >= start; i--)
        {
            if (array[i] > array[i+1])
            {
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                isSwapped = true;
            }
        }

        start += 1;
    }
}
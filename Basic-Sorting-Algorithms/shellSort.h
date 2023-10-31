/************************************************************************************
 * Method: shellSort: 
 * 
 * - The shellSort function takes two parameters:
 *   - int *array: A pointer to an array of integers that you want to sort.
 *   - int size: The number of elements in the array.
 * - The sorting process begins by initializing a variable gap to be half of the 
 * size of the array. This is because Shell Sort uses a sequence of decreasing gaps 
 * to perform the sorting.
 * - The function enters an outer loop that continues as long as gap is greater 
 * than 0. In each iteration of this loop, the gap is reduced by half (gap /= 2).
 * - Within the outer loop, there is an inner loop that performs the sorting. It 
 * iterates over the elements of the array starting from the element at position 
 * gap (i.e., i = gap) and goes up to the last element (i < size).
 * - Inside the inner loop:
 *   - The value at the current position i in the array is stored in a temporary 
 *     variable temp.
 *   - A nested loop is used to compare and swap elements that are separated by 
 *     the current gap. The loop continues as long as j is greater than or equal 
 *     to gap and the element at array[j - gap] is greater than the temp value.
 * - If the condition in the nested loop is satisfied, the element at 
 * array[j - gap] is moved to the position j, effectively shifting it by gap 
 * positions to the right.
 * - This process repeats until the correct position for the temp value is found, 
 * and it is placed in the array at position j.
 * - After the inner loop finishes for the current gap, the elements in the 
 * array are partially sorted with that gap value.
 * - The outer loop then reduces the gap and repeats the inner sorting loop for 
 * the new gap value.
 * - This process continues with progressively smaller gap values until gap 
 * becomes 0, which signals the end of the sorting process.
 *
 * Input: int *array, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void shellSort(int *array, int size)
{
    int gap, i, j, temp;

    for (gap = size / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < size; i++)
        {
            temp = array[i];
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
            {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}
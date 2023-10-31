int findMax(int *array, int size);
void countingSort(int *array, int size, int exp);

/************************************************************************************
 * Method: radixSort: 
 * 
 * - This function is the main Radix Sort algorithm. It takes an array of integers 
 * and its size as input.
 * - It begins by finding the maximum value in the array using the findMax 
 * function. This maximum value is used to determine how many passes through the 
 * array are required, based on the number of digits in the maximum value.
 * - The outer loop iterates through each place value, starting from the ones 
 * place (1) and increasing by a factor of 10 in each iteration. It uses exp to 
 * determine the current place value.
 * - Inside the loop, the countingSort function is called to sort the array 
 * based on the current place value determined by exp.
 * - The loop continues until the maximum value divided by the current place 
 * value exp is greater than 0, meaning there are still more significant 
 * digits to sort.
 *
 * Input: int *array, int size.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void radixSort(int *array, int size)
{
    int max = findMax(array, size);
    int exp;

    for (exp = 1; max / exp > 0; exp *= 10)
        countingSort(array, size, exp);
}

/************************************************************************************
 * Method: findMax: 
 * 
 * - The findMax function is used to find the maximum element in the array.
 * - It takes the array and its size as input.
 * - It initializes a variable max to the value of the first element in the array.
 * - It then iterates through the array from the second element to the last.
 * - During the iteration, it checks if the current element is greater than the 
 * current max value. If it is, max is updated to the new maximum value.
 * - Once the loop finishes, the function returns the maximum value found in the 
 * array.
 *
 * Input: int *array, int size.
 *
 * Output: Maximum in List.
 *
************************************************************************************/
int findMax(int *array, int size)
{
    int max = array[0];
    int i;
    for (i = 1; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

/************************************************************************************
 * Method: countingSort: 
 * 
 * - The countingSort function is a modified counting sort algorithm used to sort 
 * the array based on a specific digit's place value (exp).
 * - It begins by defining base as 10 since we're working with base-10 digits 
 * (0-9).
 * - The function creates an auxiliary array output to store the sorted elements, 
 * as well as a counting array count to count the occurrences of each digit at the 
 * current place value.
 * - It initializes the count array with zeros.
 * - The first loop counts the occurrences of each digit based on the current place 
 * value by calculating (array[i] / exp) % base.
 * - The second loop updates the count array to represent the cumulative count of 
 * elements less than or equal to each digit.
 * - The third loop rearranges the elements in the output array based on their 
 * counts and the current place value.
 * - Finally, the last loop copies the elements back from the output array to the 
 * original array, effectively sorting the array based on the current digit's 
 * place value.
 *
 * Input: int *array, int size, int exp.
 *
 * Output: Sorted List.
 *
************************************************************************************/
void countingSort(int *array, int size, int exp)
{
    const int base = 10;
    int output[size];
    int count[base];

    int i;
    for (i = 0; i < base; i++)
        count[i] = 0;
    
    for (i = 0; i < size; i++)
        count[(array[i] / exp) % base]++;
    
    for (i = 1; i < base; i++)
        count[i] += count[i - 1];

    for (i = size - 1; i >= 0; i--)
    {
        output[count[(array[i] / exp) % base] - 1] = array[i];
        count[(array[i] / exp) % base]--;
    }

    for (i = 0; i < size; i++)
        array[i] = output[i];
}
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <time.h>
#include <stdio.h>
#include "sPrimes.h"
#include "bubbleSort.h"
#include "insertionSort.h"
#include "selectionSort.h"
#include "cocktailSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "heapSort.h"
#include "radixSort.h"
#include "shellSort.h"

#define NUM_TESTS 100

double measureTime(void (*sortingFunction)(int*, int), int *array, int size);
void shuffleArray(int *array, int size);

/************************************************************************************
 * @author Jake Brockbank
 * October 31st, 2023
 * This code is essentially responsible for comparing the performance of various
 * sorting algorithms on the same set of input data (S-prime numbers) and print 
 * out the average time taken by each algorithm for a specified number of test 
 * runs. This can be useful for benchmarking and comparing the efficiency of 
 * different sorting algorithms. Aswell as for people new to sorting algorithms
 * who wish to understand the intricacies of them.
 * 
 * What are S-primes? Let S be the set of positive integers of the form 4k+1, where
 * k is a nonnegative (k > 0) integer. An element n ≠ 1 in S is called an S-prime
 * if the only way it can be written as a product of two elements of S is n = n * 1
 * = 1 * n.
************************************************************************************/

/*---------------------------------------------------------------------------------*/

/************************************************************************************
 * Method: main: 
 * 
 * - This code includes several standard C libraries for file handling, random 
 * number generation, and time measurement, as well as custom header files for 
 * various sorting algorithms (Specifically: bubble sort, insertion sort, 
 * selection sort, cocktail sort, merge sort, quick sort, heap sort, radix sort,
 * and lastly shell sort).
 * - It defines a macro NUM_TESTS with a value of 100, which represents the number 
 * of times each sorting algorithm will be tested.
 * - The measureTime function is defined to measure the execution time of a given 
 * sorting algorithm applied to an array. It takes a function pointer to the sorting 
 * algorithm, the array to be sorted, and its size as parameters. It uses the clock 
 * function to measure the time taken for sorting and returns the time in 
 * milliseconds.
 * - The shuffleArray function is defined to shuffle the elements of an array. It 
 * is used to randomize the order of the input array before sorting to ensure that 
 * the sorting algorithms are tested with different input orders.
 * - In the main function, the program performs the following steps:
 *   - a. It generates an array of S-prime numbers (primality patterns) using the 
 *        findSPrimes function. These S-primes are stored in the sPrimes array.
 *   - b. The S-primes are written to a file named "sPrimes.txt" using the 
 *        writeSPrimesToFile function.
 *   - c. The program then opens the "sPrimes.txt" file for reading and reads the 
 *        S-prime numbers into an array named buffer.
 *   - d. It calculates the size of the buffer array based on how many S-primes 
 *        were successfully read.
 *   - e. An array named avgTimes is created to store the average times for sorting 
 *        algorithms. It is initialized to all zeros.
 *   - f. The random number generator is seeded based on the current time.
 *   - g. A loop is executed NUM_TESTS times, where the following steps are 
 *        repeated for each test:
 *   - h. After the tests are completed, the code calculates and prints the average 
 *        execution times for each sorting algorithm over all the tests.
 *   - A copy of the buffer array is created as testBuffer.
 * - The shuffleArray function shuffles the testBuffer to randomize the order of elements.
 * - The measureTime function is called for various sorting algorithms, and the 
 * execution times are accumulated in the avgTimes array.
 * - The sorting algorithms tested include Bubble Sort, Insertion Sort, Selection Sort, 
 * Cocktail Sort, Merge Sort, Quick Sort, Heap Sort, Radix Sort, and Shell Sort.
 * - The code finally returns 0, indicating successful execution.
 *
 * Input: None.
 *
 * Output: The Sorting Algorithm Timing Results.
 *
************************************************************************************/
int main() 
{
    int sPrimeCount = 20000;
    int sPrimes[sPrimeCount];

    // Find S-primes and save them to an array
    findSPrimes(sPrimeCount, sPrimes);

    writeSPrimesToFile(sPrimes, sPrimeCount, "sPrimes.txt");

    // Open and read the S-primes file
    FILE *file = fopen("sPrimes.txt", "r");
    if (file == NULL) 
    {
        printf("Failed to open the file.\n");
        return 1;
    }

    int buffer[sPrimeCount];
    int i = 0;
    char line[20];

    while (fgets(line, sizeof(line), file) != NULL && i < sPrimeCount) 
    {
        // Use sscanf to parse the cleaned line and convert it to an integer
        int value;
        if (sscanf(line, "%d", &value) == 1) 
        {
            buffer[i] = value;
            i++;
        }
    }

    fclose(file);

    int size = i;
    printf("SIZE: %d\n", size);

    // Array to store average times
    double avgTimes[NUM_TESTS] = {0};

    srand((unsigned)time(NULL)); // Seed the random number generator

    for (int test = 0; test < NUM_TESTS; test++) 
    {
        int testBuffer[size];
        for (int j = 0; j < size; j++) 
        {
            testBuffer[j] = buffer[j];
        }

        shuffleArray(testBuffer, size);

        // Measure and store times for each sorting algorithm
        avgTimes[test] += measureTime(bubbleSort, testBuffer, size);
        avgTimes[test] += measureTime(insertionSort, testBuffer, size);
        avgTimes[test] += measureTime(selectionSort, testBuffer, size);
        avgTimes[test] += measureTime(cocktailSort, testBuffer, size);
        avgTimes[test] += measureTime(mergeSort, testBuffer, size);
        avgTimes[test] += measureTime(quickSort, testBuffer, size);
        avgTimes[test] += measureTime(heapSort, testBuffer, size);
        avgTimes[test] += measureTime(radixSort, testBuffer, size);
        avgTimes[test] += measureTime(shellSort, testBuffer, size);
    }

    // Calculate and print the average times
    printf("Average Times (over %d tests):\n", NUM_TESTS);
    printf("Bubble Sort: %.3f ms\n", avgTimes[0] / NUM_TESTS);
    printf("Insertion Sort: %.3f ms\n", avgTimes[1] / NUM_TESTS);
    printf("Selection Sort: %.3f ms\n", avgTimes[2] / NUM_TESTS);
    printf("Cocktail Sort: %.3f ms\n", avgTimes[3] / NUM_TESTS);
    printf("Merge Sort: %.3f ms\n", avgTimes[4] / NUM_TESTS);
    printf("Quick Sort: %.3f ms\n", avgTimes[5] / NUM_TESTS);
    printf("Heap Sort: %.3f ms\n", avgTimes[6] / NUM_TESTS);
    printf("Radix Sort: %.3f ms\n", avgTimes[7] / NUM_TESTS);
    printf("Shell Sort: %.3f ms\n", avgTimes[9] / NUM_TESTS);

    return 0;
}

/************************************************************************************
 * Method: shuffleArray: 
 * 
 * - The shuffleArray function takes two parameters:
 *   - int *array: a pointer to the array whose elements need to be shuffled.
 *   - int size: the number of elements in the array.
 * - The function initializes a loop that iterates from i equal to size - 1 down to 
 * 0. This loop is used to shuffle the elements in reverse order.
 * - Inside the loop, it generates a random integer j using rand() % (i + 1). This 
 * random integer j will be in the range from 0 to i, inclusive.
 * - The function swaps the element at index i with the element at index j. This is 
 * done by using a temporary variable temp to hold the value of array[i], then setting 
 * array[i] to the value of array[j, and finally, setting array[j] to the value of 
 * temp.
 * - The loop continues to iterate, moving backward from the end of the array toward 
 * the beginning, shuffling the elements randomly.
 *
 * Input: int *array, int size.
 *
 * Output: Shuffled Array.
 *
************************************************************************************/
void shuffleArray(int *array, int size) 
{
    for (int i = size - 1; i >= 0; i--) 
    {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/************************************************************************************
 * Method: measureTime: 
 * 
 * - The function measureTime takes three parameters:
 * - void (*sortingFunction)(int*, int): A function pointer that represents the 
 * sorting algorithm to be tested. This parameter allows you to pass a sorting 
 * function as an argument to the measureTime function.
 * - int *array: A pointer to the array of integers that have to be sorted.
 * - int size: The number of elements in the array.
 * - The function records the current time using clock() and stores it in the 
 * start_time variable. This marks the starting point for measuring the 
 * execution time.
 * - It then calls the sorting algorithm provided as a function pointer, passing the 
 * array and its size as arguments. This effectively sorts the array using the 
 * chosen sorting algorithm.
 * - After the sorting algorithm has completed its work, the function records the 
 * current time again using clock() and stores it in the end_time variable. 
 * This marks the end point for measuring the execution time.
 * - The function calculates the elapsed time by subtracting start_time from 
 * end_time. The result is the number of clock ticks that elapsed during the 
 * sorting process.
 * - The elapsed time is then converted from clock ticks to milliseconds by 
 * multiplying it by 1000.0 and dividing by CLOCKS_PER_SEC. This is done to 
 * express the time in milliseconds for better readability and comparison with 
 * other time measurements.
 * - Finally, the function returns the elapsed time in milliseconds as a 
 * double value.
 *
 * Input: void (*sortingFunction)(int*, int), int *array, int size.
 *
 * Output: Measured Time for Desired Algorithm.
 *
************************************************************************************/
double measureTime(void (*sortingFunction)(int*, int), int *array, int size) 
{
    clock_t start_time = clock();
    sortingFunction(array, size);
    clock_t end_time = clock();

    return ((double)(end_time - start_time) * 1000.0) / CLOCKS_PER_SEC;
}
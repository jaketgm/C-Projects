#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

/******************************************************************************
 * @author Jake Brockbank
 * Sep 26th, 2023
 * Creates an array with random double values of a specified size 
 * (Chosen by the user to be anywhere between 10 and 20). Then, sorting the 
 * array from smallest to largest via insertion sort.
******************************************************************************/

//All functional prototypes
double randomDoubleGen();
void insertionSort(double *array, int answer);

/******************************************************************************
 * Method: main: Sets up the random seed to be used to generate the random
 * elements within the array, creates the array with a specified size chosen by
 * the user, sets all elements in said array to randomized double values from 
 * 10.0000 (inclusive) and 100.0000(exclusive). Then, sorts this array via
 * insertion sort from smallest to largest. Lastly, it prints out the
 * unsorted array and the sorted one.
 *
 * Input: None.
 *
 * Output: The printed arrays.
 *
******************************************************************************/
int main()
{
    int answer;
    bool valid = false;

    // Initializes the random seed
    srand(time(NULL));  

    do
    {
        printf("Enter an integer between 10 and 20: ");
        scanf("%d", &answer);

        if (answer >= 10 && answer <= 20)
        {
            valid = true;
        }
        else
        {
            valid = false;
            printf("Invalid input. Please enter an integer between 10 and 20.\n");
        }
    } while (!valid);
    
    double array[answer];

    for (int i = 0; i < answer; i++)
    {
        //sets all elements in the array to randomized doubles via this function call
        array[i] = randomDoubleGen();
    }
    
    //prints the unsorted array on the same line
    printf("\n\nUnsorted array:\n");
    printf("\n[  ");
    for (int i = 0; i < answer; i++)
    {
        printf("%.4lf  ", array[i]);
    }
    printf("]");

    insertionSort(array, answer);

    //prints the sorted array on the same line
    printf("\n\nSorted array:\n");
    printf("\n[  ");
    for (int i = 0; i < answer; i++)
    {
        printf("%.4lf  ", array[i]);
    }
    printf("]\n\n");

    return 0;
}

/******************************************************************************
 * Method: randomDoubleGen: Generates a randomized double value from 10.0000 
 * (inclusive) and 100.0000(exclusive).
 *
 * Input: None.
 *
 * Output: A random double between 10.0000 (inclusive) and 100.0000(exclusive).
 *
******************************************************************************/
double randomDoubleGen()
{
    int randomInt = rand() % 90000;
    double randomDouble = 10.0000 + (randomInt / 90000.0) * 90.0000;
    return randomDouble;
}

/******************************************************************************
 * Method: insertionSort: Takes in the adress of our array via a pointer, and
 * also that arrays size. Then, sorts all the elements in our array from
 * smallest to largest via insertion sort.
 * 
 * Input: double *array, int answer.
 *
 * Output: Sorted array.
 *
******************************************************************************/
void insertionSort(double *array, int answer)
{
    for (int i = 1; i < answer; i++)
    {
        double key = array[i];
        int j = i - 1;

        /* Shift elements in the array from index 0 to i-1 that are larger than the 
        'key' value one position forward in the array, effectively creating space 
        for the 'key' to be inserted in its correct sorted position. */
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/******************************************************************************
 * @author Jake Brockbank
 * Sep 26th, 2023
 * Applies a set of functions to an array with randomized elements. This is done
 * via passing the arrays address to these functionals, and then allowing them
 * to void return.
******************************************************************************/

//All functional prototypes
int randomDoubleGen();
void addElements(int *x, int size);
void absoluteValue(int *x, int size);
void copySort(int *x, int size);
void squareElements(int *x, int size);

/******************************************************************************
 * Method: main: Sets up the random seed to be used to generate the random
 * elements within the array, creates the array with a size of 10, sets all
 * elements in said array to randomized values from -20 to 20 via a function 
 * call. Lastly, it prints out all the functionals and there associated
 * manipulations of our defined array. Namely, addElements, absoluteValue, 
 * copySort, and squareElements.
 *
 * Input: None.
 *
 * Output: The printed arrays.
 *
******************************************************************************/
int main()
{
    // Initializes the random seed
    srand(time(NULL));  
    int size = 10;
    int x[size];

    for (int i = 0; i < size; i++)
    {
        x[i] = randomDoubleGen();
    }
    
    //print regular array
    printf("\nOriginal array: ");
    printf("[  ");
    for (int i = 0; i < size; i++)
    {
        printf("%d  ", x[i]);
    }
    printf("]\n");

    //print array with all elements changed to their value add 5
    addElements(x, size);
    printf("\nAdded Elements Array: ");
    printf("[  ");
    for (int i = 0; i < size; i++)
    {
        printf("%d  ", x[i]);
    }
    printf("]\n\n");

    //print array with absolute value applied to each value in the array
    absoluteValue(x, size);
    printf("Absolute Value Array: ");
    printf("[  ");
    for (int i = 0; i < size; i++)
    {
        printf("%d  ", x[i]);
    }
    printf("]\n\n");

    //print sorted copied array
    copySort(x, size);
    printf("Copied & Sorted Array: ");
    printf("[  ");
    for (int i = 0; i < size; i++)
    {
        printf("%d  ", x[i]);
    }
    printf("]\n\n");

    //print squared elements array
    squareElements(x, size);
    printf("Squared Elements Array: ");
    printf("[  ");
    for (int i = 0; i < size; i++)
    {
        printf("%d  ", x[i]);
    }
    printf("]\n\n");

    return 0;
}

/******************************************************************************
 * Method: randomDoubleGen: Generates a random integer from -20 to 20. Then,
 * returns this integer to be used in the code.
 *
 * Input: None.
 *
 * Output: A random integer between -20 and 20.
 *
******************************************************************************/
int randomDoubleGen()
{
    /* Serves to limit the range of the random numbers to the values 
    between 0 and 40 (inclusive). The subtraction of 20 serves to
    shift the range of random numbers so that we can match our expected
    behaviour of having the numbers be generated between -20 and 20. */ 
    int randomInteger = rand() % 41 - 20;
    return randomInteger;
}

/******************************************************************************
 * Method: addElements: This method simply receives the address of our array
 * via a pointer, and also its defined size. With this, it then adds the number
 * 5 to each element within the array.
 * 
 * Input: int *x, int size.
 *
 * Output: Array with each element being added by 5.
 *
******************************************************************************/
void addElements(int *x, int size)
{
    for (int i = 0; i < size; i++)
    {
        x[i] += 5;
    }
}

/******************************************************************************
 * Method: absoluteValue: Takes in the original array via a pointer, and its
 * predefined size. Addiditonally, this method calculates the absolute value
 * via checking whether each element in the array is less than 0 
 * (implying negative), and then changing it to positive via negation (-- = +).
 * 
 * Input: int *x, int size.
 *
 * Output: Absolute value of the array.
 *
******************************************************************************/
void absoluteValue(int *x, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (x[i] < 0)
        {
            x[i] = -x[i];
        }
    }
}

/******************************************************************************
 * Method: copySort: Takes in the original array via a pointer, and its
 * predefined size. Furthermore, this method copys all the elements over to a 
 * new array called arrayCpy which is initialized with the same size as the 
 * original array we are passing in. It then simply iterates over all elements
 * and effictevely sets both arrays equal to one another. Next, we use insertion
 * sort to sort the elements within the array. Lastly, we copy over the elements
 * for the new array arrapCpy we made in this method back into our original array
 * x.
 * 
 * Input: int *x, int size.
 *
 * Output: Sorted array.
 *
******************************************************************************/
void copySort(int *x, int size)
{
    int arrayCpy[size];
    for (int i = 0; i < size; i++)
    {
        arrayCpy[i] = x[i];
    }

    for (int i = 1; i < size; i++)
    {
        double key = arrayCpy[i];
        int j = i - 1;

        /* Shift elements in the array from index 0 to i-1 that are larger than the 
        'key' value one position forward in the array, effectively creating space 
        for the 'key' to be inserted in its correct sorted position. */
        while (j >= 0 && arrayCpy[j] > key)
        {
            arrayCpy[j + 1] = arrayCpy[j];
            j = j - 1;
        }
        arrayCpy[j + 1] = key;
    }

    for (int i = 0; i < size; i++)
    {
        x[i] = arrayCpy[i];
    }
}

/******************************************************************************
 * Method: squareElements: Takes in the original array via a pointer, and its
 * predefined size. Furthermore, this method squares the elements of the array
 * via multiplying them together.
 * x.
 * 
 * Input: int *x, int size.
 *
 * Output: Array with squared elements.
 *
******************************************************************************/
void squareElements(int *x, int size)
{
    for (int i = 0; i < size; i++)
    {
        x[i] *= x[i];
    }
}
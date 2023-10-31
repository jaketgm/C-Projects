#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/************************************************************************************
 * Method: isSPrime: 
 * 
 * - The isSPrime function takes one parameter, n, which is the integer to be 
 * checked.
 * - It starts with several conditional checks:
 *   - If n is equal to 1, the function returns false. In most prime definitions, 
 *     1 is not considered a prime number.
 *   - If n is equal to 2 or 3, the function returns true immediately. These are 
 *     the first two prime numbers, and they are considered S-primes.
 * - If n doesn't meet the previous conditions, it checks the next condition: if 
 * (n % 4 != 1). This condition checks if n has a remainder of 1 when divided by 4. 
 * If not, the function returns false. This is one of the properties of S-primes.
 * - If n satisfies the above conditions, the function enters a for loop:
 *   - It initializes an integer i to 5 and iterates while i * i is less than or 
 *     equal to n. In each iteration, it checks two conditions:
 *       - if (n % i == 0): This checks if n is divisible by i. If it is, the 
 *         function returns false because prime numbers should not have divisors 
 *         other than 1 and themselves.
 *       - if (n % (i + 2) == 0): This checks if n is divisible by i + 2. If it 
 *         is, the function returns false as well.
 * - If none of the conditions inside the loop are triggered, the function returns 
 * true. This means that the input integer n is an S-prime based on the given 
 * conditions.
 *
 * Input: int n.
 *
 * Output: True or False Value Depending on Whether n is an S-prime.
 *
************************************************************************************/
bool isSPrime(int n) 
{
    if (n == 1) 
    {
        return false;
    }
    if (n == 2 || n == 3) 
    {
        return true;
    }
    if (n % 4 != 1) 
    {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6) 
    {
        if (n % i == 0 || n % (i + 2) == 0) 
        {
            return false;
        }
    }
    return true;
}

/************************************************************************************
 * Method: writeSPrimesToFile: 
 * 
 * - The writeSPrimesToFile function takes three parameters:
 *   - int sPrimes[]: An array of S-prime numbers that you want to write to the file.
 *   - int limit: The number of elements (S-primes) in the array that you want to 
 *     write to the file.
 *   - const char *filename: The name of the file to which the S-primes will be 
 *     written.
 * - The function begins by attempting to open the specified file for writing 
 * using fopen. It uses the mode "w" to open the file for writing, and if the file 
 * cannot be opened, it prints an error message and returns without writing 
 * anything to the file.
 * - It then seeds the random number generator by calling srand with the current 
 * time as the seed. This is done to shuffle the S-prime numbers in the array 
 * randomly before writing them to the file.
 * - The function enters a loop to shuffle the elements in the sPrimes array. 
 * It iterates through the array, and for each element at index i, it swaps it 
 * with another element chosen randomly from the elements between indices 0 and 
 * i. This shuffling process randomizes the order of the S-prime numbers in the 
 * array.
 * - After shuffling the array, the function proceeds to write the S-prime numbers 
 * to the file. It uses a for loop to iterate through the elements in the array. 
 * For each element, it uses fprintf to write the S-prime as a 19-character string 
 * to the file, left-padded with zeros if necessary. This ensures that each line 
 * in the file has a consistent width of 20 characters.
 * - Once all the S-prime numbers are written to the file, the function closes the 
 * file using fclose.
 * - Finally, it prints a message to the console, indicating that the S-primes 
 * have been successfully saved to the specified file.
 *
 * Input: int sPrimes[], int limit, const char *filename.
 *
 * Output: Created File with S-primes.
 *
************************************************************************************/
void writeSPrimesToFile(int sPrimes[], int limit, const char *filename) 
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
    {
        printf("Failed to create the file.\n");
        return;
    }

    srand(time(NULL));

    int i, j, temp;
    for (i = limit - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        temp = sPrimes[i];
        sPrimes[i] = sPrimes[j];
        sPrimes[j] = temp;
    }

    // Write the array to the file with left-padding to ensure each line has 20 characters
    for (i = 0; i < limit; i++) 
        fprintf(file, "%019d\n", sPrimes[i]);

    // Close the file
    fclose(file);

    printf("\nS-primes saved to %s\n", filename);
}

/************************************************************************************
 * Method: findSPrimes: 
 * 
 * - The function findSPrimes takes two parameters:
 *   - int limit: The number of S-prime numbers to find and store in the array 
 *     sPrimes.
 *   - int sPrimes[]: An array that will store the found S-prime numbers. Inside 
 *     the function, it initializes two variables:
 *       - int n is initialized to 1. This variable represents the current number 
 *         being checked to determine if it's an S-prime.
 *       - int count is initialized to 0. This variable keeps track of how many 
 *         S-prime numbers have been found and stored in the sPrimes array.
 * - The function enters a while loop that continues until count reaches the 
 * specified limit, i.e., until the desired number of S-prime numbers have been 
 * found and stored.
 * - Inside the loop, it calls the isSPrime function to check if the current 
 * number n is an S-prime. If isSPrime(n) returns true, it means that n is an 
 * S-prime, and it proceeds to the next step.
 * - If n is determined to be an S-prime, it is stored in the sPrimes array at 
 * the position indicated by the count variable, and count is incremented to 
 * keep track of the number of S-prime numbers found.
 * - After this, n is incremented by 4. This is because S-prime numbers follow 
 * a pattern where they are of the form 4k + 1, so the code checks numbers of 
 * this form. By incrementing n by 4, the code is moving on to the next 
 * candidate number to be checked for S-primality.
 * - The loop continues until count reaches the specified limit, at which 
 * point the desired number of S-prime numbers have been found and stored in 
 * the sPrimes array.
 *
 * Input: int limit, int sPrimes[].
 *
 * Output: Finds S-primes.
 *
************************************************************************************/
void findSPrimes(int limit, int sPrimes[]) 
{
    int n = 1;
    int count = 0;

    while (count < limit) 
    {
        if (isSPrime(n)) 
        {
            sPrimes[count] = n;
            count++;
        }
        n += 4; // Increment by 4 to check the next number of the form 4k+1
    }
}
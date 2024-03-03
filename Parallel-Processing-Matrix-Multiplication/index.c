#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 834

#include "matrixOperations.h"

/************************************************************************************
 * @author Jake Brockbank
 * January 17th, 2024
 * This program multiplies two N x N matricies and stores the result of said
 * calculation in an associated N x N resultant matrix. It then takes the time in
 * which takes to compute the multiplication operation. Then reports this value
 * back. Note N can be chosen arbitrarily in the macro defined above. However, since
 * memory is on the stack it typically will result in a stack overflow if the value
 * of N is too large. I check on my machine using the ulimit -s, and found that my
 * machines stack size was ~8176 kilobytes or 8.176 MB. So, we have the total 
 * memory required to be 3 x N^2 x 4 (bytes). Coupling this with the knowledge of
 * my machines stack size. I can solve for N in the equation: 3 x N^2 x 4 = 8,176
 * x 1024. Doing this results in N ~ 834, so this is the "tightest/largest" N we
 * can choose without getting a stack overflow error.
************************************************************************************/
int main()
{
    int matrixOne[N][N], matrixTwo[N][N], resultantMatrix[N][N];

    srand(time(NULL));

    clock_t startingTime, endingTime;
    double cpuTime;

    createMatrix(matrixOne);
    createMatrix(matrixTwo);

    startingTime = clock();

    multiplyMatricies(matrixOne, matrixTwo, resultantMatrix);

    endingTime = clock();

    cpuTime = ((double) (endingTime - startingTime)) / CLOCKS_PER_SEC;

    printf("Time taken (N=%d): %f seconds\n", N, cpuTime);

    char filename[] = "result.txt";

    printMatrixToFile(matrixOne, matrixTwo, resultantMatrix, cpuTime, filename);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "stdNormalCalcs.h"


/************************************************************************************
 * @author Jake Brockbank
 * January 17th, 2024
 * This program approximates the integral of the normal distribution curve from
 * statistics. This is tested on a plethora of A values and h step sizes.
************************************************************************************/
int main()
{
    double A, stepSize, riemannProb;
    /* I use clock_t here due to the fact that it is a more precise way
    of storing time on a computer. */
    clock_t startingTime, endingTime;
    double cpuTime;

    printf("Enter the step size (h): ");
    scanf("%lf", &stepSize);

    printf("Enter A: ");
    scanf("%lf", &A);

    startingTime = clock();

    riemannProb = riemannApprox(stepSize, A);

    endingTime = clock();

    // Converts the time from cpu time to that of seconds
    cpuTime =  ((double) (endingTime - startingTime)) / CLOCKS_PER_SEC;

    printf("P(Z <= %f) = %f\n", A, riemannProb);
    printf("Time (seconds): %f\n", cpuTime);

    return 0;
}
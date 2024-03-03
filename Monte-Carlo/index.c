#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double estimPi(int numPoints);

/************************************************************************************
 * @author Jake Brockbank
 * January 17th, 2024
 * This program utilizes the Monte Carlo estimation for PI, it times said
 * approximations, and simultaneously finds the absolute error per iteration
 * of points.
************************************************************************************/
int main()
{
    srand(time(NULL));

    int arrayOfPoints[] = {1000, 10000, 100000, 1000000, 10000000, 
                           100000000, 1000000000, INT32_MAX };

    int numTests = sizeof(arrayOfPoints) / sizeof(arrayOfPoints[0]);
    
    double pi, error;
    clock_t startingTime, endingTime;
    double cpuTime;
    
    int i;

    for (i = 0; i < numTests; i++) 
    {
        startingTime = clock();

        pi = estimPi(arrayOfPoints[i]);

        endingTime = clock();

        cpuTime = ((double) (endingTime - startingTime)) / CLOCKS_PER_SEC;
        error = fabs(pi - M_PI); // Absolute error

        printf("Number of Points: %d, Estimated Pi: %f, Error: %f, Time Taken: %f seconds\n", arrayOfPoints[i], pi, error, cpuTime);
    }

    return 0;
}

/************************************************************************************
 * Method: estimPi: This method estimates the value of pi using the Monte Carlo 
 * method by simulating random points within a unit square and counting how many 
 * fall inside a quarter circle within it. The ratio of points inside the quarter 
 * circle to the total number of points, multiplied by 4, approximates pi.
 *
 * Input: int numPoints.
 *
 * Output: The estimation for pi.
 *
************************************************************************************/
double estimPi(int numPoints)
{
    double radius = 1.0;
    int i, pointsInCircle = 0;
    double x, y;

    for (i = 0; i < numPoints; i++)
    {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;

        if (x * x + y * y <= radius)
            pointsInCircle++;
    }

    return (double) pointsInCircle / numPoints * 4;
}
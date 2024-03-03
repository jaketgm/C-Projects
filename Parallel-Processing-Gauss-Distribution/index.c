/******************************************************************************
 * @author Jake Brockbank
 * Feb 20th, 2024
 * This program performs the following set of tasks about standard normal 
 * random variables using a pre-programmed gaussianRand method.
 *  - A) Determines the minimum number generated among 10,000,000 numbers.
 *  - B) Determines the maximum number generated among 10,000,000 numbers.
 *  - C) Determine the percentage of numbers between -1 and +1 among 10,000,000 
 *       numbers.
 *  - D) Determine the percentage of numbers above 0 among 10,000,000 numbers.
 *  - E) Determine the percentage of numbers more than 2 away from the mean 
 *       among 10,000,000 numbers.
 *  - F) Determine the number of values generated whose first digit is a 1 
 *       among 10,000,000 numbers.
 *  - (b) Rework the above program in parallel so that you use 2 processors 
 *        and each processor does 3 of the tasks.
 *  - (c) Rework the above program so parallel that you use 3 processors and 
 *        each processor does 2 of the tasks.
 *  - (d) Rework the above program so parallel that you use 6 processors 
 *        and each processor does 1 of the tasks
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"
#define N 10000000
#define LOWER_BOUND -1.0
#define UPPER_BOUND 1.0
#define NUMTIMES 14

double gaussianRand(double mean, double stddev);
double determineMinNum(double startingGuess);
double determineMaxNum(double startingGuess);
double percentageBetween();
double percentageAbvZero();
double percentageTwoFromMean();
int numFirstDigitOne();

void quickSort(double *array, int left, int right);

/******************************************************************************
 * Method: main: 
 * 
 * - This method executes the sequential part of a gauss randomization 
 * program, and times the results. It then, runs in parallel on 2, 3, 6
 * processors, and times the results.
 *
 * Input: int argc, char** argv.
 *
 * Output: None.
 *
******************************************************************************/
int main(int argc, char** argv) 
{
    MPI_Init(&argc, &argv);

    int rank, num_processes;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    srand((time(NULL) + rank)); // Seed

    double times[NUMTIMES];
    double minimum, maximum, perBetween, perAbove, perFromMean;
    int firstDigitOneCount;
    double startingGuess;

    // The sequential part is run only by processor 0
    if (rank == 0) 
    {
        printf("\nSequential Part:\n");
        double seqTimes[NUMTIMES];
        for (int i = 0; i < NUMTIMES; i++) 
        {
            double startTime = MPI_Wtime();

            minimum = determineMinNum(gaussianRand(0, 1));
            maximum = determineMaxNum(gaussianRand(0, 1));
            perBetween = percentageBetween();
            perAbove = percentageAbvZero();
            perFromMean = percentageTwoFromMean();
            firstDigitOneCount = numFirstDigitOne();

            double endTime = MPI_Wtime();
            seqTimes[i] = endTime - startTime;
        }

        // Calculate the average sequential execution time
        quickSort(seqTimes, 0, NUMTIMES - 1);
        double avgSeqTime = 0;
        for (int i = 2; i < NUMTIMES - 2; i++) 
        {
            avgSeqTime += seqTimes[i];
        }
        avgSeqTime /= (NUMTIMES - 4);

        // Print results
        printf("Average Sequential Execution Time: %f seconds\n", avgSeqTime);
    }

    MPI_Barrier(MPI_COMM_WORLD); 

    for (int i = 0; i < NUMTIMES; i++) 
    {
        MPI_Barrier(MPI_COMM_WORLD); // Synchronize
        double start = MPI_Wtime();

        startingGuess = gaussianRand(0, 1); // Each process gets an initial guess

        if (num_processes == 2)
        {
            if (rank == 0)
            {
                minimum = determineMinNum(startingGuess);
                perBetween = percentageBetween();
                // Receive results from rank 1
                MPI_Recv(&maximum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&perFromMean, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&firstDigitOneCount, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            else if (rank == 1)
            {
                maximum = determineMaxNum(startingGuess);
                perFromMean = percentageTwoFromMean();
                firstDigitOneCount = numFirstDigitOne();
                // Send results to rank 0
                MPI_Send(&maximum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
                MPI_Send(&perFromMean, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
                MPI_Send(&firstDigitOneCount, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
            }
        }
        else if (num_processes == 3)
        {
            if (rank == 0)
            {
                minimum = determineMinNum(startingGuess);
            }
            else if (rank == 1)
            {
                maximum = determineMaxNum(startingGuess);
                perBetween = percentageBetween();
            }
            else if (rank == 2)
            {
                perAbove = percentageAbvZero();
                perFromMean = percentageTwoFromMean();
                firstDigitOneCount = numFirstDigitOne();
            }
            // Collect results at rank 0
            MPI_Reduce(&minimum, &minimum, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
            MPI_Reduce(&maximum, &maximum, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
            MPI_Reduce(&perBetween, &perBetween, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(&perAbove, &perAbove, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(&perFromMean, &perFromMean, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(&firstDigitOneCount, &firstDigitOneCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        }
        else if (num_processes == 6)
        {
            if (rank == 0)
            {
                minimum = determineMinNum(startingGuess);
            }
            else if (rank == 1)
            {
                maximum = determineMaxNum(startingGuess);
            }
            else if (rank == 2)
            {
                perBetween = percentageBetween();
            }
            else if (rank == 3)
            {
                perAbove = percentageAbvZero();
            }
            else if (rank == 4)
            {
                perFromMean = percentageTwoFromMean();
            }
            else if (rank == 5)
            {
                firstDigitOneCount = numFirstDigitOne();
            }
            
            double mainMinimum, mainMaximum, mainPerBetween, mainPerAbove, mainPerFromMean, mainFirstDigit;

            MPI_Reduce(&minimum, &mainMinimum, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
            MPI_Reduce(&maximum, &mainMaximum, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
            MPI_Reduce(&perBetween, &mainPerBetween, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(&perAbove, &mainPerAbove, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(&perFromMean, &mainPerFromMean, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(&firstDigitOneCount, &mainFirstDigit, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        }

        if (rank == 0)
        {
            printf("Global minimum: %f\n", minimum);
            printf("Global maximum: %f\n", maximum);
            printf("Percentage between: %f%%\n", perBetween / num_processes); 
            printf("Percentage above zero: %f%%\n", perAbove / num_processes); 
            printf("Percentage more than two from mean: %f%%\n", perFromMean / num_processes); 
            printf("Count of first digit one: %d\n", firstDigitOneCount);
            printf("\n");
        }

        MPI_Barrier(MPI_COMM_WORLD);
        double end = MPI_Wtime();
        times[i] = end - start;
    }

    // Calculate average parallel execution time for each processor
    quickSort(times, 0, NUMTIMES - 1);
    double avgTime = 0;
    for (int i = 2; i < NUMTIMES - 2; i++) 
    {
        avgTime += times[i];
    }
    avgTime /= (NUMTIMES - 4);
    printf("Rank %d Average Parallel Execution Time: %f seconds\n", rank, avgTime);

    MPI_Finalize();
    return 0;
}

/******************************************************************************
 * Method: determineMinNum: 
 * 
 * - This method takes in a starting guess, then grabs a new guess 
 * and compares thr two, this process continues doing this N times, and 
 * produces the minimum number.
 *
 * Input: double startingGuess.
 *
 * Output: startingGuess.
 *
******************************************************************************/
double determineMinNum(double startingGuess)
{
    int i;
    for (i = 0; i < N; i++)
    {
        double newGuess = gaussianRand(0, 1);
        if (newGuess < startingGuess)
        {
            startingGuess = newGuess;
        }
    }
    return startingGuess;
}

/******************************************************************************
 * Method: determineMaxNum: 
 * 
 * - This method is very similar to the determineMinNum, the only difference 
 * being that we compare via the (>) operator to find the largest number.
 *
 * Input: double startingGuess.
 *
 * Output: startingGuess.
 *
******************************************************************************/
double determineMaxNum(double startingGuess)
{
    int i;
    for (i = 0; i < N; i++)
    {
        double newGuess = gaussianRand(0, 1);
        if (newGuess > startingGuess)
        {
            startingGuess = newGuess;
        }
    }
    return startingGuess;
}

/******************************************************************************
 * Method: percentageBetween: 
 * 
 * - This method calculates the percentage of numbers generated by the Gaussian
 * distribution that fall within a -1.0 and 1.0.
 *
 * Input: None.
 *
 * Output: perBetween * 100.
 *
******************************************************************************/
double percentageBetween()
{
    double perBetween = 0;
    int i, count = 0;
    for (i = 0; i < N; i++)
    {
        double num = gaussianRand(0, 1);
        if (num >= LOWER_BOUND && num <= UPPER_BOUND)
        {
            count++;
        }
    }
    perBetween = (double)count / N;
    return perBetween * 100;
}

/******************************************************************************
 * Method: percentageAbvZero: 
 * 
 * - This method finds the percentage of numbers above zero in the Gaussian 
 * distribution.
 *
 * Input: None.
 *
 * Output: perAbove * 100.
 *
******************************************************************************/
double percentageAbvZero()
{
    double perAbove = 0;
    int i, count = 0;
    for (i = 0; i < N; i++)
    {
        double num = gaussianRand(0, 1);
        if (num > 0)
        {
            count++;
        }
    }
    perAbove = (double)count / N;
    return perAbove * 100;
}

/******************************************************************************
 * Method: percentageTwoFromMean: 
 * 
 * - This method calculates the percentage of numbers more than 2 away from 
 * the mean.
 *
 * Input: None.
 *
 * Output: perFromMean * 100.
 *
******************************************************************************/
double percentageTwoFromMean()
{
    double perFromMean = 0;
    double lower = LOWER_BOUND * 2; // Since it would be \mu + 2\sigma and \mu - 2\sigma (And \mu = 0, \sigma = 1 (Since Normal Distribution))
    double upper = UPPER_BOUND * 2;
    int i, count = 0;
    for (i = 0; i < N; i++)
    {
        double num = gaussianRand(0, 1);
        if (num >= lower && num <= upper)
        {
            count++;
        }
    }
    perFromMean = (double)count / N;
    return perFromMean * 100;
}

/******************************************************************************
 * Method: quickSort: 
 * 
 * - This method sorts the given data via quicksort.
 *
 * Input: double *array, int left, int right.
 *
 * Output: None.
 *
******************************************************************************/
void quickSort(double *array, int left, int right) 
{
    if (left < right) 
    {
        double pivot = array[right];
        int i = left - 1;

        for (int j = left; j <= right - 1; j++) 
        {
            if (array[j] <= pivot) 
            {
                i++;
                double tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
        double tmp = array[i + 1];
        array[i + 1] = array[right];
        array[right] = tmp;

        quickSort(array, left, i); 
        quickSort(array, i + 1, right);
    }
}

/******************************************************************************
 * Method: numFirstDigitOne: 
 * 
 * - This method calculates the amount of numbers whose first digit is one.
 *
 * Input: None.
 *
 * Output: count.
 *
******************************************************************************/
int numFirstDigitOne()
{
    int i, count = 0;
    for (i = 0; i < N; i++)
    {
        double num = fabs(gaussianRand(0, 1));
        while (num >= 10)
        {
            num /= 10;
        }
        while (num < 1)
        {
            num *= 10;
        }

        int firstDigit = (int) num;
        if (firstDigit == 1)
            count++;
    }
    return count;
}

/******************************************************************************
 * Method: gaussianRand: 
 * 
 * - This method generates random points on a Gaussian distribution.
 *
 * Input: double mean, double stddev.
 *
 * Output: result or n2 * stddev + mean.
 *
******************************************************************************/
double gaussianRand(double mean, double stddev)
{
    static double n2 = 0.0;
    static int n2_cached = 0;
    if (!n2_cached)
    {
        double x, y, r;
        do {
            // Generate two random numbers in the range [0, 1]
            x = 2.0 * rand() / RAND_MAX - 1;
            y = 2.0 * rand() / RAND_MAX - 1;
            // Compute the squared Euclidean distance from the origin
            r = x * x + y * y;
        } while (r >= 1 || r == 0);
        // Box-Muller transform to get two normal distributed numbers
        double d = sqrt(-2.0 * log(r) / r);
        double n1 = x * d;
        n2 = y * d;
        double result = n1 * stddev + mean;
        n2_cached = 1;
        return result;
    }
    else
    {
        n2_cached = 0;
        return n2 * stddev + mean;
    }
}
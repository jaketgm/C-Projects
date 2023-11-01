#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "quickFind.h"
#include "quickUnion.h"
#include "weightedQuickUnion.h"
#include "weightedQuickUnionWithPathCompression.h"

/************************************************************************************
 * @author Jake Brockbank
 * Nov 1st, 2023
 * This code tests Quick Find, Quick Union, Weighted Quick
 * Union, and Weighted Quick Union With Path Compression Algorithms. These
 * algorithms are responsible for solving the dynamic connectivity (Union Find) 
 * problem. We simply test their union and isConnected functions for each one, 
 * and also print out the current state of the structure. Since in my implementation
 * I decided to make structures associated to each of the algorithms.
************************************************************************************/

/*---------------------------------------------------------------------------------*/

/************************************************************************************
 * Method: main: 
 * 
 * - Tests Quick Find: This is the simplest union-find data structure. It 
 * uses an integer array to represent the elements. The unionPoints function 
 * connects two elements by changing the values in the array, and the isConnected 
 * function checks whether two elements are connected by comparing their 
 * array values.
 * - Tests Quick Union: This data structure uses a tree-like structure to represent 
 * sets of elements. The unionPointsQU function connects two elements by making 
 * one element the root of the other's tree, and the isConnectedQU function checks 
 * whether two elements are connected by checking if they have the same root.
 * - Tests Weighted Quick Union: Similar to Quick Union, this data structure also 
 * uses a tree-like structure, but it balances the trees by connecting the smaller 
 * tree to the larger one when performing unions. This prevents tall trees and 
 * improves performance. The unionPointsWQU function is used to connect two 
 * elements, and the isConnectedWQU function checks for connectivity.
 * - Tests Weighted Quick Union With Path Compression: This data structure is an 
 * improvement over Weighted Quick Union. In addition to the weight-balancing 
 * mechanism, it also applies path compression during the isConnectedWQUWPC 
 * function to make the tree structure more balanced. Path compression involves 
 * making each element point directly to its root when checking for connectivity.
 * It finally utilizes each built in toString method to display the results to
 * the console.
 *
 * Input: None.
 *
 * Output: The Outputs for Tests of the Quick Find, Quick Union, Weighted Quick
 * Union, and Weighted Quick Union With Path Compression Algorithms.
 *
************************************************************************************/
int main() 
{
    int size = 100;
    int sizeQU = 100;
    int sizeWQU = 100;
    int sizeWQUWPC = 100;

    quickfind myQF;
    quickunion myQU;
    weightedQU myWQU;
    weightedQUWPC myWQUWPC;

    initializeQF(&myQF, size);
    initializeQU(&myQU, sizeQU);
    initializeWeightedQU(&myWQU, sizeWQU);
    initializeWeightedQUWPC(&myWQUWPC, sizeWQUWPC);

    // Perform union operations for Quick Find
    unionPoints(&myQF, 1, 2);
    unionPoints(&myQF, 3, 4);
    unionPoints(&myQF, 4, 5);

    // Perform union operations for Quick Union
    unionPointsQU(&myQU, 1, 2);
    unionPointsQU(&myQU, 3, 4);
    unionPointsQU(&myQU, 4, 5);

    // Perform union operations for Weighted Quick Union
    unionPointsWQU(&myWQU, 1, 2);
    unionPointsWQU(&myWQU, 3, 4);
    unionPointsWQU(&myWQU, 4, 5);

    // Perform union operations for Weighted Quick Union With Path Compression
    unionPointsWQUWPC(&myWQUWPC, 1, 2);
    unionPointsWQUWPC(&myWQUWPC, 3, 4);
    unionPointsWQUWPC(&myWQUWPC, 4, 5);

    // Check if elements are connected for Quick Find
    printf("\n1 and 2 are connected (Quick Find): %s\n", isConnected(&myQF, 1, 2) ? "Yes" : "No");
    printf("2 and 3 are connected (Quick Find): %s\n", isConnected(&myQF, 2, 3) ? "Yes" : "No");
    printf("4 and 5 are connected (Quick Find): %s\n", isConnected(&myQF, 4, 5) ? "Yes" : "No");
    printf("1 and 4 are connected (Quick Find): %s\n\n", isConnected(&myQF, 1, 4) ? "Yes" : "No");

    // Check if elements are connected for Quick Union
    printf("1 and 2 are connected (Quick Union): %s\n", isConnectedQU(&myQU, 1, 2) ? "Yes" : "No");
    printf("2 and 3 are connected (Quick Union): %s\n", isConnectedQU(&myQU, 2, 3) ? "Yes" : "No");
    printf("4 and 5 are connected (Quick Union): %s\n", isConnectedQU(&myQU, 4, 5) ? "Yes" : "No");
    printf("1 and 4 are connected (Quick Union): %s\n", isConnectedQU(&myQU, 1, 4) ? "Yes" : "No");

    // Check if elements are connected for Weighted Quick Union
    printf("\n1 and 2 are connected (Weighted Quick Union): %s\n", isConnectedWQU(&myWQU, 1, 2) ? "Yes" : "No");
    printf("2 and 3 are connected (Weighted Quick Union): %s\n", isConnectedWQU(&myWQU, 2, 3) ? "Yes" : "No");
    printf("4 and 5 are connected (Weighted Quick Union): %s\n", isConnectedWQU(&myWQU, 4, 5) ? "Yes" : "No");
    printf("1 and 4 are connected (Weighted Quick Union): %s\n", isConnectedWQU(&myWQU, 1, 4) ? "Yes" : "No");

    // Check if elements are connected for Weighted Quick Union With Path Compression
    printf("\n1 and 2 are connected (Weighted Quick Union With Path Compression): %s\n", isConnectedWQUWPC(&myWQUWPC, 1, 2) ? "Yes" : "No");
    printf("2 and 3 are connected (Weighted Quick Union With Path Compression): %s\n", isConnectedWQUWPC(&myWQUWPC, 2, 3) ? "Yes" : "No");
    printf("4 and 5 are connected (Weighted Quick Union With Path Compression): %s\n", isConnectedWQUWPC(&myWQUWPC, 4, 5) ? "Yes" : "No");
    printf("1 and 4 are connected (Weighted Quick Union With Path Compression): %s\n", isConnectedWQUWPC(&myWQUWPC, 1, 4) ? "Yes" : "No");

    // Print the current state of the Quick Find structure
    char *strRepresentationQF = quickFindToString(&myQF);
    if (strRepresentationQF) 
    {
        printf("\nQuick Find Structure: %s\n", strRepresentationQF);
        free(strRepresentationQF);
    }
    else 
    {
        printf("Error: Memory allocation failed.\n");
    }

    // Print the current state of the Quick Union structure
    char *strRepresentationQU = quickUnionToString(&myQU);
    if (strRepresentationQU) 
    {
        printf("\nQuick Union Structure: %s\n\n", strRepresentationQU);
        free(strRepresentationQU);
    } 
    else 
    {
        printf("Error: Memory allocation failed.\n");
    }

    // Print the current state of the Weighted Quick Union structure (For ID)
    char *strRepresentationWQU = weightedQuickUnionToString(&myWQU, sizeWQU);
    if (strRepresentationWQU) 
    {
        printf("Weighted Quick Union Structure: %s\n\n", strRepresentationWQU);
        free(strRepresentationWQU);
    } 
    else 
    {
        printf("Error: Memory allocation failed.\n");
    }

    // Print the current state of the Weighted Quick Union structure (For Size)
    char *strRepresentationWQUSize = weightedQuickUnionToStringSize(&myWQU, sizeWQU);
    if (strRepresentationWQUSize) 
    {
        printf("Weighted Quick Union Structure: %s\n\n", strRepresentationWQUSize);
        free(strRepresentationWQUSize);
    } 
    else 
    {
        printf("Error: Memory allocation failed.\n");
    }

    // Print the current state of the Weighted Quick Union With Path Compression structure (For ID)
    char *strRepresentationWQUWPC = weightedQuickUnionWPCToString(&myWQUWPC, sizeWQUWPC);
    if (strRepresentationWQUWPC) 
    {
        printf("Weighted Quick Union With Path Compression Structure: %s\n\n", strRepresentationWQUWPC);
        free(strRepresentationWQUWPC);
    } 
    else 
    {
        printf("Error: Memory allocation failed.\n");
    }

    // Print the current state of the Weighted Quick Union structure (For Size)
    char *strRepresentationWQUWPCSize = weightedQuickUnionWPCToStringSize(&myWQUWPC, sizeWQUWPC);
    if (strRepresentationWQUWPCSize) 
    {
        printf("Weighted Quick Union With Path Compression Structure: %s\n\n", strRepresentationWQUWPCSize);
        free(strRepresentationWQUWPCSize);
    } 
    else 
    {
        printf("Error: Memory allocation failed.\n");
    }

    freeQF(&myQF);
    freeQU(&myQU);
    freeWQU(&myWQU);
    freeWQUWPC(&myWQUWPC);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "startGraphics.h"
#include "mergeSort.h"

#define MAX_ID_NUMBERS 32
#define MIN_ID_DIGITS 10
#define MAX_ID_DIGITS 20
#define MAX_NAME_LENGTH 19

typedef struct Id
{
    char name[MAX_NAME_LENGTH + 1];
    char idString[MAX_ID_NUMBERS][MAX_ID_DIGITS + 1]; // +1 for the null terminator
    int numOfIDS; // Number of ID numbers stored
} id;

void sortIdNumbers(char idString[][MAX_ID_DIGITS + 1], int numOfIDS);
void validityCheck(char idString[][MAX_ID_DIGITS + 1], int numOfIDS);

/*************************************************************************************
 *
 * How to Use:
 *           - Start by inputting the name of the person (user) overseeing the 
 *             validation of the ID's, and aswell the person inputting said ID's 
 *             for verification.
 *           - Input the number of ID's the user wishes to validate, note if you
 *             want this to work, the number of ID's inputted must be 1 or more, 
 *             and less than 32.
 *           - Next, insert each individual ID, these can have differing lengths;
 *             however, ensure that they are not less than 10 digits long nor
 *             greater than 19 digits long.
 *           - The program will do the rest!
 *
 *
 * Test Cases (That Will Work):
 *           ID 1: 1922010110911 (High School Teacher)  
 *           ID 2: 2819191919111 (High School Student)
 *           ID 3: 420756633778 (Middle School Teacher)
 *           ID 4: 421756633778 (Middle School Student)
 *
 * Test Cases (Will Not Work)
 *           ID 1: 19220101 (Length < 10)
 *           ID 2: 281919191911191919177 (Will Work, but Cuts Off any Digits After 19)
 *           ID 3: 429756633779 (When Sorted Doesn't Start with Either a 0 or 1)
 *           ID 4: 421756633774 (When Sorted Doesn't End with Either a 8 or 9)
 *
*************************************************************************************/

/*---------------------------------------------------------------------------------*/

/************************************************************************************
 * @author Jake Brockbank
 * October 24th, 2023
 * This is a re-vamp/re-do of one of my highschool computer science projects, we
 * were tasked with making an ID verification system for an imaginary high school/
 * middle school, we could create our own way of validating the ID's of students and
 * teachers at this school. The way I approached this in my re-vamp is by merge
 * sorting the ID's, and having conditionals as to whther the ID would be valid or
 * not. I choose to check validation via just checking essentially the smallest 
 * (first when sorted) digit in the inputted ID's, and the largest 
 * (last when sorted) digit in the inputted ID's. Furthermore, I allocated 
 * designations for whether the digits were equal to a certain predefined number,
 * in my case I made this to be 0 (Smallest)(Indicates Teacher), 1 
 * (Smallest)(Indicates Student), aswell as 8 (Largest)(Indicates Middle School)
 * and 9 (Largest)(Indicates High School). Below you will find the full code for
 * this program. Hope you enjoy!
************************************************************************************/

/*---------------------------------------------------------------------------------*/

/************************************************************************************
 * Method: main: 
 * 
 * - Initializes variables to be used throughout the program:
 *         - i: A loop counter. numIDSInputted: Stores the number of ID 
 *           numbers the user wants to validate. thisID: A pointer 
 *           to a dynamically allocated structure of type id.
 * - Calls a function named startGraphics(), which is inputted via a header 
 *   file.
 * - Dynamically allocates memory for the thisID structure and initializes its 
 *   numOfIDS field to 0.
 * - Prompts the user to enter their name and the number of ID numbers they 
 *   want to validate. It checks if the entered number of IDs is within a 
 *   specified range (between 1 and MAX_ID_NUMBERS).
 * - If the number of IDs entered by the user is not within the valid range, 
 *   the program prints an error message and frees the dynamically allocated 
 *   memory for thisID. It then returns with an exit status of 1, indicating 
 *   an error.
 * - If the number of IDs is valid, the program proceeds to store the user's 
 *   name and the entered ID numbers in the thisID structure.
 * - It checks the length of each entered ID number, ensuring they are 
 *   between MIN_ID_DIGITS and MAX_ID_DIGITS digits. If an invalid ID length is 
 *   detected, it prints an error message, frees the dynamically allocated 
 *   memory, and returns with an exit status of 1.
 * - It clears the console screen using the "clear" system command.
 * - It prints the user's name and the entered ID numbers. Then, it sorts 
 *   the entered ID numbers using a function called sortIdNumbers.
 * - It prints the sorted ID numbers.
 * - It calls a function named validityCheck to check the validity of the 
 *   sorted ID numbers.
 * - Finally, it frees the dynamically allocated memory for thisID and 
 *   returns with an exit status of 0, indicating successful execution.
 *
 * Input: None.
 *
 * Output: The ID Program.
 *
************************************************************************************/
int main()
{
    int i;
    int numIDSInputted;

    startGraphics();

    id* thisID = (id*) malloc(sizeof(id));

    thisID->numOfIDS = 0;

    printf("\n\nEnter Your Name: ");
    scanf("%19s", thisID->name);

    printf("Enter the Number of ID's you Wish to Validate (1 to %d): ", MAX_ID_NUMBERS);
    scanf("%d", &numIDSInputted);

    if (numIDSInputted < 1 || numIDSInputted > MAX_ID_NUMBERS)
    {
        printf("Invalid Number of ID's.\n");
        free(thisID);
        return 1;
    }

    thisID->numOfIDS = numIDSInputted;

    for (i = 0; i < numIDSInputted; i++)
    {
        printf("\nEnter an ID Number %d (between 10 and 20 digits): ", i + 1);
        scanf("%20s", thisID->idString[i]);

        // Check the length of the entered ID
        int numDigits = strlen(thisID->idString[i]);

        if (numDigits < MIN_ID_DIGITS || numDigits > MAX_ID_DIGITS)
        {
            printf("\nInvalid number of digits. ID must be between %d and %d digits.\n", MIN_ID_DIGITS, MAX_ID_DIGITS);
            free(thisID);
            return 1;
        }
    }

    system("clear");
    printf("Here are your ID's %s: ", thisID->name);
    for (int i = 0; i < numIDSInputted; i++)
    {
        printf("ID %d: %s", i + 1, thisID->idString[i]);
        if (i < numIDSInputted - 1)
        {
            printf(", ");
        }
    }
    printf("\n");

    sortIdNumbers(thisID->idString, thisID->numOfIDS);
    
    printf("\nHere are your Sorted ID's %s: ", thisID->name);
    for (int i = 0; i < numIDSInputted; i++)
    {
        printf("ID %d: %s", i + 1, thisID->idString[i]);
        if (i < numIDSInputted - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
    printf("\n");

    validityCheck(thisID->idString, thisID->numOfIDS);

    printf("\n");
    free(thisID);
    return 0;
}

/************************************************************************************
 * Method: sortIdNumbers: Iterates throught the number of ID's, then calls merge
 * sort to sort them from smallest to largest. Merges sort is included via the
 * header file at the top of the program.
 *
 * Input: char idString[][MAX_ID_DIGITS + 1], int numOfIDS.
 *
 * Output: Sorted ID's.
 *
************************************************************************************/
void sortIdNumbers(char idString[][MAX_ID_DIGITS + 1], int numOfIDS)
{
    for (int i = 0; i < numOfIDS; i++)
    {
        mergeSort(idString[i], strlen(idString[i]));
    }
}

/************************************************************************************
 * Method: validityCheck: Checks the validity via the criteria defined in the
 * "Author Header" comment at the top of the program.
 *
 * Input: char idString[][MAX_ID_DIGITS + 1], int numOfIDS.
 *
 * Output: Validity of Inputted ID's.
 *
************************************************************************************/
void validityCheck(char idString[][MAX_ID_DIGITS + 1], int numOfIDS)
{
    int originalIndices[MAX_ID_NUMBERS]; // To store the original indices
    for (int i = 0; i < numOfIDS; i++)
    {
        originalIndices[i] = i; // Store the original index
    }

    for (int i = 0; i < numOfIDS; i++)
    {
        char *id = idString[i];
        int originalIndex = originalIndices[i]; // Get the original index
        
        if (id[0] == '0')
        {
            if (id[strlen(id) - 1] == '9')
            {
                printf("ID %d: %s belongs to a high school teacher.\n", originalIndex + 1, id);
            }
            else if (id[strlen(id) - 1] == '8')
            {
                printf("ID %d: %s belongs to a middle school teacher.\n", originalIndex + 1, id);
            }
            else
            {
                printf("ID %d: %s is an invalid ID for a teacher.\n", originalIndex + 1, id);
            }
        }
        else if (id[0] == '1')
        {
            if (id[strlen(id) - 1] == '9')
            {
                printf("ID %d: %s belongs to a high school student.\n", originalIndex + 1, id);
            }
            else if (id[strlen(id) - 1] == '8')
            {
                printf("ID %d: %s belongs to a middle school student.\n", originalIndex + 1, id);
            }
            else
            {
                printf("ID %d: %s is an invalid ID for a student.\n", originalIndex + 1, id);
            }
        }
        else
        {
            printf("ID %d: %s is an invalid ID, it does not belong to a teacher or student.\n", originalIndex + 1, id);
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 * @author Jake Brockbank
 * Sep 19th, 2023
 * Takes a user input for month and a day, and produces whether that day, and
 * month is valid or not. If it is the case that it is valid, this is printed
 * for the user to see, if not it informs them of such.
 ******************************************************************************/
void monthSwitch(int month, char monthName[]);
int daySwitch(int day, int month);

/******************************************************************************
 * Method: main: Prompts the user to enter the day and month, stoes these
 * values to be used in the validity checks for both. Also prints the result,
 * and loops for multiple inputs.
 *
 * Input: None.
 *
 * Output: The printed month and day if valid, if not valid then prints That 
 * is not a valid date.
 *
******************************************************************************/
int main()
{
    int month;
    int day;
    int enterResult;
    do
    {
        printf("\nWhat is the month ==> ");
        scanf("%d", &month);
        printf("What is the day ==> ");
        scanf("%d", &day);

        char monthName[20];
        monthSwitch(month, monthName);
        int dayValidity = daySwitch(day, month);

        /* 
            Checks whether the day is valid or not, since we can't use boolean values without an additional 
            include statement. So, we will instead use 0 as invalid, and 1 as valid. Making a psuedo-boolean
            evaluation through binary means, and acheived with ints.
        */
        if (dayValidity == 0)
        {
            printf("That is not a valid date\n");
        }
        else
        {
            printf("That is the %dth of %s\n", day, monthName);
        }

        printf("\nDo you have another date to enter (1 for yes, any other number for no) ==> ");
        scanf("%d", &enterResult);
    } while (enterResult == 1);
    
    return 0;
}

/******************************************************************************
 * Method: monthSwitch: This method utilizes a switch case, and goes through
 * all the possible months, and uses strcpy. Which essentially transfers the 
 * content of the string referenced by source (including the null character) to 
 * the destination. In our case we ascribe the string name of the month to
 * the array we define in our main method.
 *
 * Input: int month, char monthName[].
 *
 * Output: copied information in char monthName[].
 *
******************************************************************************/
void monthSwitch(int month, char monthName[])
{
    switch(month)
    {
        case 1:
            strcpy(monthName, "January");
            break;
        case 2:
            strcpy(monthName, "February");
            break;
        case 3:
            strcpy(monthName, "March");
            break;
        case 4:
            strcpy(monthName, "April");
            break;
        case 5:
            strcpy(monthName, "May");
            break;
        case 6:
            strcpy(monthName, "June");
            break;
        case 7:
            strcpy(monthName, "July");
            break;
        case 8:
            strcpy(monthName, "August");
            break;
        case 9:
            strcpy(monthName, "September");
            break;
        case 10:
            strcpy(monthName, "October");
            break;
        case 11:
            strcpy(monthName, "November");
            break;
        case 12:
            strcpy(monthName, "December");
            break;
        default:
            strcpy(monthName, "That is not a valid date");
    }
}

/******************************************************************************
 * Method: daySwitch: This method utilizes a switch case, and goes through
 * all the possible days corresponding to their associated months.
 *
 * Input: int day, int month.
 *
 * Output: The day corresponding to the month, and its validity.
 *
******************************************************************************/
int daySwitch(int day, int month)
{
    int daysOfTheMonth;
    int dayIsValid;

    switch(month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            daysOfTheMonth = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            daysOfTheMonth = 30;
            break;
        case 2:
            daysOfTheMonth = 28;
            break;
        default:
            daysOfTheMonth = 0;
    }

    if (day >= 1 && day <= daysOfTheMonth)
    {
        dayIsValid = 1; //Indicating true
    }
    else
    {
        dayIsValid = 0; //Indicating false
    }

    return dayIsValid;
}
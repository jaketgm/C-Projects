#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 * @author Jake Brockbank
 * Sep 28th, 2023
 * Simulates a scenario where you have three employees with different ages and 
 * salaries, and it calculates their final salaries based on their ages and a 
 * fixed tax rate. It then writes this information to a text file for 
 * record-keeping or reporting purposes.
******************************************************************************/
struct Employee
{
    char name[50];
    char role[50];
    int age;
    double salary;
    double finalSalary;
};

double taxCalculation(double tax, double salary, int age);

/******************************************************************************
 * Method: main:
 * - Defines a structure struct Employee to represent an employee's 
 *   information, including their name, role, age, salary, and final salary.
 * - It declares a function double 
 *   taxCalculation(double tax, double salary, int age); for calculating an 
 *   employee's final salary based on their age and an applied tax rate.
 * - In the main function, it opens a file named "Employees.txt" for writing.
 * - It initializes a tax rate tax to 1.25.
 * - It creates three struct Employee instances (employeeOne, employeeTwo, 
 *   and employeeThree) and populates their data (name, role, age, salary) 
 *   using strcpy and assigns the final salary by calling the taxCalculation 
 *   function.
 * - It prints the employee information and final salary for each employee to 
 *   the "Employees.txt" file using fprintf.
 * - It closes the "Employees.txt" file and returns 0 to indicate successful 
 *   program execution.
 *
 * Input: None.
 *
 * Output: Returns New TXT File With Changes Made.
 *
******************************************************************************/
int main() 
{
    FILE *fPointer = fopen("Employees.txt", "w");

    double tax = 1.25;

    struct Employee employeeOne;
    strcpy(employeeOne.name, "Jim");
    strcpy(employeeOne.role, "Salesman");
    employeeOne.age = 35;
    employeeOne.salary = 45000.00;
    employeeOne.finalSalary = taxCalculation(tax, employeeOne.salary, employeeOne.age);
    
    struct Employee employeeTwo;
    strcpy(employeeTwo.name, "Pam"); 
    strcpy(employeeTwo.role, "Receptionist");
    employeeTwo.age = 26;
    employeeTwo.salary = 20000.00;
    employeeTwo.finalSalary = taxCalculation(tax, employeeTwo.salary, employeeTwo.age);

    struct Employee employeeThree;
    strcpy(employeeThree.name, "Oscar");
    strcpy(employeeThree.role, "Accounting");
    employeeThree.age = 64;
    employeeThree.salary = 45433.00;
    employeeThree.finalSalary = taxCalculation(tax, employeeThree.salary, employeeThree.age);
    
    fprintf(fPointer, "Name: %s\n", employeeOne.name);
    fprintf(fPointer, "Role: %s\n", employeeOne.role);
    fprintf(fPointer, "Age: %d\n", employeeOne.age);
    fprintf(fPointer, "Salary: %.2lf\n\n", employeeOne.salary);
    fprintf(fPointer, "Final Salary: %.2lf\n\n", employeeOne.finalSalary);
    
    fprintf(fPointer, "Name: %s\n", employeeTwo.name);
    fprintf(fPointer, "Role: %s\n", employeeTwo.role);
    fprintf(fPointer, "Age: %d\n", employeeTwo.age);
    fprintf(fPointer, "Salary: %.2lf\n\n", employeeTwo.salary);
    fprintf(fPointer, "Final Salary: %.2lf\n\n", employeeTwo.finalSalary);

    fprintf(fPointer, "Name: %s\n", employeeThree.name);
    fprintf(fPointer, "Role: %s\n", employeeThree.role);
    fprintf(fPointer, "Age: %d\n", employeeThree.age);
    fprintf(fPointer, "Salary: %.2lf\n\n", employeeThree.salary);
    fprintf(fPointer, "Final Salary: %.2lf\n\n", employeeThree.finalSalary);

    fclose(fPointer);
    return 0;
}

/******************************************************************************
 * Method: taxCalculation:
 * - Takes the tax rate, employee salary, and age as input and calculates the 
 *   final salary. If the age is 50 or younger, it applies the tax rate to the 
 *   salary; otherwise, it leaves the salary unchanged.
 *
 * Input: double tax, double salary, int age.
 *
 * Output: Updated Tax.
 *
******************************************************************************/
double taxCalculation(double tax, double salary, int age)
{
    double finalSalary;
    if (age <= 50)
    {
        finalSalary = salary * tax;
    }
    else
    {
        finalSalary = salary;
    }
    return finalSalary;
}
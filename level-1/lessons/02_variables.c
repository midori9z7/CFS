/* 02_variables.c
 * Storing data in variables.
 *
 * A variable is a named box in memory where your program can
 * store a value. Before you can use a variable you must DECLARE it:
 * you tell C its type (what kind of data it holds) and its name.
 *
 * Compile:
 *     gcc 02_variables.c -o variables
 * Run:
 *     ./variables
 *
 * Lesson 02 - README.md:
 *     int    -> whole numbers          (print/read with %d)
 *     double -> decimals, double precision (print %f, read %lf)
 *     float  -> decimals, single precision (%f)
 *     char   -> ONE character, in ' '  (%c)
 *     %.2f   -> print a decimal with 2 digits after the dot
 *     sizeof -> how many bytes a type uses
 */

#include <stdio.h>

int main(void)
{
    /* ---- Declaring variables ------------------------------------- */
    int    age    = 25;    // int   : whole numbers (no decimals)
    float  height = 1.78f; // float : decimal numbers (single precision)
    double weight = 72.5;  // double: decimal numbers (double precision)
    char   grade  = 'A';   // char  : ONE single character, in ' ' quotes

    /* ---- Printing variables --------------------------------------- */
    // printf uses a FORMAT STRING with placeholders:
    //   %d  prints an int
    //   %f  prints a float or double
    //   %c  prints a char
    //   %s  prints a string (text) -- you will see this later!
    // Each placeholder must match the value you pass, in order.

    printf("Age   : %d\n", age);
    printf("Height: %.2f meters\n", height);  // %.2f = 2 decimal places
    printf("Weight: %.1f kg\n", weight);      // %.1f = 1 decimal place
    printf("Grade : %c\n", grade);

    /* ---- Changing a variable -------------------------------------- */
    age = 26;             // Assign a NEW value (no type keyword again!)
    printf("Next year I will be %d years old.\n", age);

    /* ---- A quick look at memory size (bonus) ----------------------- */
    // sizeof() tells you how many bytes a type uses on your machine.
    printf("An int uses %zu bytes, a char uses %zu byte.\n",
           sizeof(int), sizeof(char));

    return 0;
}

/* circle.c
 * Your first "real" little program:
 * compute the area and circumference of a circle.
 *
 * This program combines everything from this level:
 * variables, constants, scanf() input, math and printf().
 *
 * Geometry reminder:
 *     circumference = 2 * pi * r
 *     area          = pi * r * r
 *
 * Compile:
 *     gcc circle.c -o circle
 * Run:
 *     ./circle
 *
 * Lessons used: 02, 03, 04.
 */

#include <stdio.h>

#define PI 3.14159265358979
// #define creates a CONSTANT: a name that is replaced by its
// value everywhere in the file. It is not a variable and it
// cannot change. By convention, constants are written in
// UPPERCASE.

int main(void)
{
    double radius = 0.0;
    double area;
    double circumference;

    // 1. Ask for the radius.
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);   // %lf reads a double (l = "long" f = float)
    // Note: printf prints doubles with %f, but scanf reads them
    // with %lf. This is a classic beginner trap!

    // 2. Compute.
    area          = PI * radius * radius;
    circumference = 2.0 * PI * radius;

    // 3. Report.
    printf("Radius         : %.2f\n", radius);
    printf("Area           : %.2f\n", area);
    printf("Circumference  : %.2f\n", circumference);

    return 0;
}

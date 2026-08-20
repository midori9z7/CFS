/* addition.c
 * Reads two numbers and prints their sum.
 * The first project with real input and a real calculation.
 *
 * Compile:
 *     gcc addition.c -o addition
 * Run:
 *     ./addition
 *
 * Lessons used: 02, 03, 04.
 */

#include <stdio.h>

int main(void)
{
    double a, b, s;

    printf("Enter two numbers: ");
    scanf("%lf %lf", &a, &b);     /* one scanf can read several values */

    s = a + b;
    printf("Sum = %.2f\n", s);

    return 0;
}

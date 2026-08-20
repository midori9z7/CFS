/* 03_arithmetic.c
 * Doing math with C.
 *
 * The basic operators:
 *     +   addition
 *     -   subtraction
 *     *   multiplication
 *     /   division
 *     %   modulo (the REMAINDER of a division)
 *
 * Watch out! If you divide two ints, C performs INTEGER division:
 * the fractional part is TRUNCATED (cut off), not rounded.
 *
 * Compile:
 *     gcc 03_arithmetic.c -o arithmetic
 * Run:
 *     ./arithmetic
 *
 * Lesson 03 - README.md:
 *     a / b   -> integer division when both are ints (17/5 == 3)
 *     17.0/5  -> real division as soon as one side has a decimal point
 *     a % b   -> the remainder of a / b
 *     %%      -> how to print a % sign
 *     * / %   bind tighter than + - ; parentheses ( ) always win
 */

#include <stdio.h>

int main(void)
{
    int a = 17;
    int b = 5;

    printf("a = %d, b = %d\n", a, b);
    printf("\n");

    printf("a + b = %d\n", a + b);   // 22
    printf("a - b = %d\n", a - b);   // 12
    printf("a * b = %d\n", a * b);   // 85
    printf("a / b = %d\n", a / b);   // 3   <-- integer division!
    printf("a %% b = %d\n", a % b);  // 2   (the remainder of 17 / 5)
    // Note: to print a real % sign with printf, write %% .

    printf("\n");

    /* ---- Integer vs. floating-point division ----------------------- */
    printf("17 / 5 as ints    = %d\n", 17 / 5);        // 3
    printf("17 / 5 as doubles = %.1f\n", 17.0 / 5.0);  // 3.4
    // As soon as ONE of the numbers has a decimal point,
    // C uses real (floating-point) division.

    printf("\n");

    /* ---- Order of operations --------------------------------------- */
    // C follows the normal math rules: * / % before + - ,
    // and parentheses ( ) always win.
    int result = 2 + 3 * 4;        // 14, not 20
    int withP  = (2 + 3) * 4;      // 20
    printf("2 + 3 * 4     = %d\n", result);
    printf("(2 + 3) * 4   = %d\n", withP);

    return 0;
}

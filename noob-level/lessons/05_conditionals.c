/* 05_conditionals.c
 * Making decisions with if / else.
 *
 * C decides by asking TRUE/FALSE questions. A test is true or false;
 * if it is true, the first branch runs, otherwise the else branch.
 *
 * Comparison operators:
 *     ==  equal        !=  not equal
 *     >   greater      <   less
 *     >=  greater or equal    <=  less or equal
 *
 * Logical operators:
 *     &&  and          ||  or          !   not
 *
 * Compile:
 *     gcc 05_conditionals.c -o conditionals
 * Run:
 *     ./conditionals
 *
 * Lesson 05 - README.md:
 *     if (test) { ... } else if (test) { ... } else { ... }
 *     %  -> the remainder, perfect for even/odd checks
 *     &&  and  ||  combine tests
 *     !   flips a test
 */

#include <stdio.h>

int main(void)
{
    int number;

    printf("Enter an integer: ");
    scanf("%d", &number);

    /* --- if / else if / else ------------------------------------ */
    if (number > 0) {
        printf("%d is positive\n", number);
    } else if (number < 0) {
        printf("%d is negative\n", number);
    } else {
        printf("%d is zero\n", number);
    }

    /* --- even / odd using the % operator ------------------------- */
    if (number % 2 == 0) {
        printf("%d is even\n", number);
    }
    if (number % 2 != 0) {
        printf("%d is odd\n", number);
    }

    /* --- combining tests ------------------------------------------ */
    if (number > 0 && number % 2 == 0) {
        printf("%d is a positive even number\n", number);
    }

    if (number == 7 || number == 13) {
        printf("%d is a lucky number!\n", number);
    }

    /* --- ! (not) flips a test ------------------------------------- */
    if (!(number == 0)) {
        printf("%d is not zero\n", number);
    }

    /* --- one-line if: no braces needed for a single statement ------ */
    if (number > 1000) {
        printf("%d is BIG\n", number);
    }

    return 0;
}

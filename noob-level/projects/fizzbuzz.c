/* fizzbuzz.c
 * The famous beginner exercise.
 * Count 1 to 100; replace multiples of 3 with "Fizz",
 * multiples of 5 with "Buzz", multiples of both with "FizzBuzz".
 *
 * Compile:
 *     gcc fizzbuzz.c -o fizzbuzz
 * Run:
 *     ./fizzbuzz
 *
 * Lessons used: 03, 05, 07.
 */

#include <stdio.h>

int main(void)
{
    int i;

    for (i = 1; i <= 100; i++) {
        if (i % 15 == 0) {          /* 15 = 3 * 5: a multiple of both */
            printf("%3d FizzBuzz\n", i);
        } else if (i % 3 == 0) {
            printf("%3d Fizz\n", i);
        } else if (i % 5 == 0) {
            printf("%3d Buzz\n", i);
        } else {
            printf("%3d\n", i);
        }
    }

    return 0;
}

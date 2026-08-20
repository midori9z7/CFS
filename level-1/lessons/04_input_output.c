/* 04_input_output.c
 * Reading input from the user with scanf().
 *
 * scanf() is the "opposite" of printf(): it reads what the user
 * types on the keyboard and stores it into a variable.
 *
 * IMPORTANT: in scanf you must put & before the variable name.
 * & means "the address of" -- scanf needs to know WHERE in memory
 * to store the value. If you forget the &, the program will
 * misbehave (or crash). We will explain why in a later level.
 *
 * Compile:
 *     gcc 04_input_output.c -o input_output
 * Run:
 *     ./input_output
 *
 * Lesson 04 - README.md:
 *     scanf("%d", &x) -> read an int  (note the & !)
 *     scanf("%lf",&x) -> read a double (note: %lf, not %f !)
 *     scanf(" %c",..) -> the space eats the leftover newline
 *     printf: %d int, %f double, %c char, %s string
 */

#include <stdio.h>

int main(void)
{
    int  yourAge = 0;    // Start at 0; scanf will overwrite it.
    char initial = '?';  // '?' so we can tell if reading failed.

    // Ask a question first -- otherwise the user stares at a
    // blinking cursor and does not know what to do!
    printf("How old are you? ");
    scanf("%d", &yourAge);        // %d matches an int

    printf("What is the first letter of your name? ");
    scanf(" %c", &initial);       // Note the SPACE before %c.
                                  // It eats the leftover newline from
                                  // the previous scanf. (More on this
                                  // in the README.)

    // Print everything back.
    printf("\nNice to meet you, %c! You are %d years old.\n",
           initial, yourAge);

    return 0;
}

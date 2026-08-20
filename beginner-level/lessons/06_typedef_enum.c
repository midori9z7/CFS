/* 06_typedef_enum.c
 * typedef and enum: naming types and named constants.
 *
 * enum creates a list of NAMED constants. Under the hood they are
 * just ints, numbered from 0. They turn magic numbers into words.
 *
 * typedef gives a type a shorter or clearer name. It shines with
 * structs: no more typing "struct" everywhere.
 *
 * Compile:
 *     gcc 06_typedef_enum.c -o typedef_enum
 * Run:
 *     ./typedef_enum
 *
 * Lesson 06 - README.md:
 *     enum Day { MON, TUE, ... };  -> MON is 0, TUE is 1, ...
 *     enum Day today = WED;        -> declare a variable of it
 *     switch (today) { case MON: } -> enums pair with switch
 *     typedef struct { ... } Time; -> shorter name, no "struct" keyword
 *     enums are ints: loop over them
 */

#include <stdio.h>

/* enum: named constants, numbered from 0 */
enum Day { MON, TUE, WED, THU, FRI, SAT, SUN };

/* typedef: give a type a shorter name */
typedef struct {
    int hours;
    int minutes;
} Time;

int main(void)
{
    enum Day today = WED;
    enum Day d;

    printf("WED = %d (enums are just numbers)\n", WED);

    switch (today) {
        case MON:
            printf("Mondays...\n");
            break;
        case FRI:
            printf("Finally Friday!\n");
            break;
        case SAT:
        case SUN:
            printf("Weekend!\n");
            break;
        default:
            printf("A working day.\n");
    }

    /* enums are ints: you can loop over them */
    printf("All days:");
    for (d = MON; d <= SUN; d++) {
        printf(" %d", d);
    }
    printf("\n");

    /* typedef makes declarations short and clean */
    Time now;
    now.hours = 14;
    now.minutes = 30;
    printf("Time: %02d:%02d\n", now.hours, now.minutes);

    return 0;
}

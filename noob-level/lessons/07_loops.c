/* 07_loops.c
 * Repeating things with loops: for, while, do-while.
 *
 *     for (start; condition; step)   -- count a known number of rounds
 *     while (condition)              -- check FIRST, then run
 *     do { ... } while (condition)   -- run AT LEAST ONCE, then check
 *
 * Inside any loop:
 *     break     -- leave the loop immediately
 *     continue  -- skip the rest of THIS round, start the next one
 *
 * Compile:
 *     gcc 07_loops.c -o loops
 * Run:
 *     ./loops
 *
 * Lesson 07 - README.md:
 *     for (i = 1; i <= 10; i++)   -> the counting loop
 *     i += 2  -> step by 2 ;  i-- -> count down
 *     total = total + i           -> the accumulator pattern
 *     while vs do-while           -> check before vs after
 *     break / continue
 */

#include <stdio.h>

int main(void)
{
    int i;
    int total;
    int counter;

    /* --- for: "i starts at 1; run while i <= 10; add 1 each round" - */
    printf("Counting from 1 to 10:\n");
    for (i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }

    /* --- stepping by 2 --------------------------------------------- */
    printf("Even numbers from 0 to 20:\n");
    for (i = 0; i <= 20; i += 2) {
        printf("%d ", i);
    }
    printf("\n");

    /* --- countdown --------------------------------------------------- */
    printf("Countdown:\n");
    for (i = 10; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("Liftoff!\n");

    /* --- the classic accumulator: total = total + i ------------------ */
    total = 0;
    for (i = 1; i <= 100; i++) {
        total = total + i;
    }
    printf("Sum of 1 to 100 = %d\n", total);

    /* --- while: check first, then run -------------------------------- */
    counter = 1;
    while (counter <= 5) {
        printf("while: counter = %d\n", counter);
        counter = counter + 1;
    }

    /* --- do-while: runs at least once, then checks -------------------- */
    counter = 10;
    do {
        printf("do-while: counter = %d (runs even though 10 < 10 is false)\n",
               counter);
        counter = counter + 1;
    } while (counter < 10);

    /* --- break stops the loop, continue skips one round --------------- */
    printf("Using continue and break:\n");
    for (i = 1; i <= 10; i++) {
        if (i == 3) {
            continue;       /* skip 3, keep going */
        }
        if (i == 8) {
            break;          /* stop completely at 8 */
        }
        printf("i = %d\n", i);
    }

    return 0;
}

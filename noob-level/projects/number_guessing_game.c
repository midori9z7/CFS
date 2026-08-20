/* number_guessing_game.c
 * The computer picks a secret number; you guess.
 * The loop ends only when you win.
 *
 * Also introduces checking scanf()'s RETURN VALUE -- the polite way
 * to handle wrong input instead of crashing.
 *
 * Compile:
 *     gcc number_guessing_game.c -o number_guessing_game
 * Run:
 *     ./number_guessing_game
 *
 * Lessons used: 04, 05, 07. New: rand, srand, time.
 */

#include <stdio.h>
#include <stdlib.h>      /* rand, srand */
#include <time.h>        /* time */

int main(void)
{
    int secret;
    int guess;
    int tries = 0;

    srand((unsigned)time(NULL));   /* seed the random generator once */
    secret = rand() % 100 + 1;     /* a number from 1 to 100 */

    printf("==========================================\n");
    printf("  I am thinking of a number from 1 to 100.\n");
    printf("  Can you guess it?\n");
    printf("==========================================\n");

    for (;;) {                     /* loop forever... */
        printf("Your guess: ");
        {
            int read = scanf("%d", &guess);
            if (read == EOF) {
                /* end of input: nothing left to read */
                printf("Thanks for playing!\n");
                break;
            }
            if (read != 1) {
                /* scanf returns how many values it managed to read.
                 * 0 means the user typed something that is not a
                 * number. Throw it away and ask again. */
                scanf("%*s");      /* %*s reads AND discards a word */
                printf("Please type a whole number.\n");
                continue;
            }
        }

        tries = tries + 1;

        if (guess < secret) {
            printf("Too low!\n");
        } else if (guess > secret) {
            printf("Too high!\n");
        } else {
            printf("Correct! The secret number was %d\n", secret);
            printf("It took you %d tries.\n", tries);
            break;                 /* ...until we win */
        }
    }

    return 0;
}

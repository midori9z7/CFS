/* 06_switch_case.c
 * Choosing between many cases with switch.
 *
 * Fortran has "select case"; C calls it switch. It picks ONE branch
 * out of many, based on the value of a variable.
 *
 * Rules:
 *     - switch works on ints and chars (not doubles, not strings)
 *     - every branch ends with break, or execution "falls through"
 *       into the next branch -- that is a feature, use it on purpose
 *     - default catches everything not listed above it; put it last
 *
 * Compile:
 *     gcc 06_switch_case.c -o switch_case
 * Run:
 *     ./switch_case
 *
 * Lesson 06 - README.md:
 *     switch (x) { case 1: ... break; default: ... }
 *     score / 10  -> the C trick for turning ranges into cases
 *     break       -> leave the switch
 *     fall-through: case 10: case 9: share one body
 */

#include <stdio.h>

int main(void)
{
    int score;
    int tens;
    char grade = '?';

    printf("Enter a score (0-100): ");
    scanf("%d", &score);

    /* score / 10 collapses ranges into single values:
     *     95 -> 9    87 -> 8    73 -> 7    100 -> 10    5 -> 0
     * This is the C way to write "case (90:100)" from Fortran.
     */
    tens = score / 10;

    switch (tens) {
        case 10:            /* falls through to case 9 -- on purpose */
        case 9:
            grade = 'A';
            break;
        case 8:
            grade = 'B';
            break;
        case 7:
            grade = 'C';
            break;
        case 6:
            grade = 'D';
            break;
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            grade = 'F';
            break;
        default:
            grade = '?';    /* 101, -3, anything weird */
            break;
    }

    if (grade != '?') {
        printf("Your grade is %c\n", grade);
    } else {
        printf("Invalid score. Try a number from 0 to 100.\n");
    }

    /* switch on a char works the same way */
    switch (grade) {
        case 'A':
            printf("Excellent!\n");
            break;
        case 'B':
            printf("Good job!\n");
            break;
        case 'C':
            printf("Not bad.\n");
            break;
        case 'D':
            printf("Almost failing...\n");
            break;
        case 'F':
            printf("Time to study more!\n");
            break;
        default:
            printf("No comment.\n");
            break;
    }

    return 0;
}

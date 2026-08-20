/* multiplication_table.c
 * Two nested loops build a neatly aligned multiplication table.
 * The %4d format prints every number in a field 4 characters wide,
 * which lines the columns up.
 *
 * Compile:
 *     gcc multiplication_table.c -o multiplication_table
 * Run:
 *     ./multiplication_table
 *
 * Lessons used: 03, 04, 07.
 */

#include <stdio.h>

int main(void)
{
    int n, i, j;

    printf("Table size (e.g. 10): ");
    scanf("%d", &n);

    /* --- header row ----------------------------------------------- */
    printf("%4s", "");            /* a blank corner, 4 wide */
    for (i = 1; i <= n; i++) {
        printf("%4d", i);
    }
    printf("\n");

    /* --- the table ------------------------------------------------- */
    for (i = 1; i <= n; i++) {
        printf("%4d", i);         /* row label */
        for (j = 1; j <= n; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }

    return 0;
}

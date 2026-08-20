/* 08_arrays.c
 * Lists of values: arrays.
 *
 * An array is many boxes of the SAME type under one name.
 * C numbers the boxes starting at 0: the first box is a[0].
 * (Fortran starts at 1; C starts at 0. A classic confusion!)
 *
 * Arrays pair perfectly with loops: the loop variable becomes the
 * index that walks through the boxes.
 *
 * Compile:
 *     gcc 08_arrays.c -o arrays
 * Run:
 *     ./arrays
 *
 * Lesson 08 - README.md:
 *     double scores[5] = { ... }  -> declare + fill in one go
 *     scores[0] is the FIRST element (indexing starts at 0!)
 *     array + loop  -> the loop variable is the index
 *     no built-in max in C: write the loop yourself
 *     int matrix[3][3]  -> a 2D array: rows and columns
 */

#include <stdio.h>

int main(void)
{
    int i;
    double scores[5] = {88.0, 92.5, 79.0, 95.0, 85.5};
    double sum = 0.0;
    double average;
    double max;
    int matrix[3][3];
    int row, col;

    /* scores[0] is 88.0, scores[1] is 92.5, ... scores[4] is 85.5 */

    /* --- arrays + loops: the loop variable becomes the index ---------- */
    for (i = 0; i < 5; i++) {
        sum = sum + scores[i];
    }
    average = sum / 5.0;
    printf("Average score = %.2f\n", average);

    /* --- find the maximum (no built-in max in C -- write the loop) ---- */
    max = scores[0];
    for (i = 1; i < 5; i++) {
        if (scores[i] > max) {
            max = scores[i];
        }
    }
    printf("Maximum      = %.2f\n", max);

    /* --- a 2D array: a grid with rows and columns ---------------------- */
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            matrix[row][col] = (row + 1) * 10 + (col + 1);
        }
    }

    printf("Matrix:\n");
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            printf("%4d", matrix[row][col]);
        }
        printf("\n");
    }

    /* --- changing an element -------------------------------------------- */
    scores[0] = 100.0;
    printf("After a re-test, the first score is %.1f\n", scores[0]);

    return 0;
}

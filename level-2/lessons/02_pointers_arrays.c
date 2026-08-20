/* 02_pointers_arrays.c
 * Pointers and arrays are best friends.
 *
 * The name of an array IS a pointer to its first element. That is
 * why you can pass an array to a function without any special
 * syntax: the array "decays" into a pointer.
 *
 * Pointer arithmetic: adding 1 to a pointer moves it to the NEXT
 * element of the array, not the next byte.
 *
 *     numbers[i]  is the same as  *(numbers + i)
 *
 * Compile:
 *     gcc 02_pointers_arrays.c -o pointers_arrays
 * Run:
 *     ./pointers_arrays
 *
 * Lesson 02 - README.md:
 *     int *p = numbers;      -> array name = address of element 0
 *     *(p + 2)               -> the same as p[2] and numbers[2]
 *     p[2]                   -> index a POINTER like an array
 *     for (p = a; p < a + n; p++)  -> walk an array with a pointer
 *     &numbers[2] == numbers + 2  -> addresses add up like this
 */

#include <stdio.h>

int main(void)
{
    int numbers[5] = {10, 20, 30, 40, 50};
    int *p = numbers;        /* points at numbers[0] */
    int *walk;
    int i;

    printf("numbers[0] = %d\n", numbers[0]);   /* 10 */
    printf("*p         = %d\n", *p);           /* 10 */
    printf("*(p + 2)   = %d\n", *(p + 2));     /* 30 -- pointer arithmetic */
    printf("p[2]       = %d\n", p[2]);         /* 30 -- p[2] IS *(p+2) */

    /* walk the array with a pointer */
    printf("Pointer walk: ");
    for (walk = numbers; walk < numbers + 5; walk++) {
        printf("%d ", *walk);
    }
    printf("\n");

    /* the same walk with an index -- they are the same thing */
    printf("Index walk:   ");
    for (i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);   /* or *(numbers + i) */
    }
    printf("\n");

    /* addresses really do add up this way */
    printf("&numbers[2] == numbers + 2 : %d (1 = true)\n",
           (&numbers[2] == numbers + 2));

    return 0;
}

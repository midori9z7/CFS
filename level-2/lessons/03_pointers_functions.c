/* 03_pointers_functions.c
 * Passing variables BY REFERENCE with pointers.
 *
 * A function that takes an int gets a COPY -- changing it inside
 * the function changes nothing outside. To really change the
 * caller's variable, pass its ADDRESS and write through the pointer.
 *
 * That is exactly why scanf needs &x, and now you know why.
 *
 * Compile:
 *     gcc 03_pointers_functions.c -o pointers_functions
 * Run:
 *     ./pointers_functions
 *
 * Lesson 03 - README.md:
 *     void swap(int *a, int *b)   -> parameters are pointers
 *     swap(&x, &y);               -> pass ADDRESSES, not values
 *     *a = *b;                    -> write through the pointer
 *     scanf("%d", &age)           -> "pass by reference", at last!
 */

#include <stdio.h>

/* swap takes POINTERS so it can change the caller's variables */
void swap(int *a, int *b);

int main(void)
{
    int x = 5;
    int y = 10;

    printf("Before: x = %d, y = %d\n", x, y);
    swap(&x, &y);          /* pass ADDRESSES */
    printf("After:  x = %d, y = %d\n", x, y);

    /* ---- the mystery of scanf, solved ------------------------------ */
    int age = 0;
    printf("Enter your age: ");
    scanf("%d", &age);     /* scanf is a function too: it needs the
                            * ADDRESS of age to store the number. */
    printf("You are %d years old.\n", age);

    return 0;
}

void swap(int *a, int *b)
{
    int temp = *a;         /* read what a points to */
    *a = *b;               /* write through the pointer */
    *b = temp;
}

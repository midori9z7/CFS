/* 07_memory.c
 * Dynamic memory: asking the operating system for memory
 * WHILE THE PROGRAM RUNS, with malloc() and free().
 *
 * So far every array had a size fixed at compile time. malloc
 * lets the SIZE be decided at run time -- by the user, by the
 * data, by anything.
 *
 * RULES:
 *     - check the result: malloc returns NULL when it fails
 *     - malloc takes BYTES: multiply the count by sizeof(type)
 *     - the memory works exactly like an array (index it with [])
 *     - give it back with free() when done -- every malloc needs
 *       exactly one free, or your program leaks memory
 *
 * Compile:
 *     gcc 07_memory.c -o memory
 * Run:
 *     ./memory
 *
 * Lesson 07 - README.md:
 *     int *numbers = malloc(n * sizeof(int));
 *     if (numbers == NULL) { ... }      -> check for failure
 *     numbers[i]                        -> index it like an array
 *     free(numbers);                    -> give the memory back
 *     stack vs heap: locals live on the stack, malloc lives on the heap
 */

#include <stdio.h>
#include <stdlib.h>      /* malloc, free */

int main(void)
{
    /* fixed size: known at compile time */
    int fixed[10];
    printf("A fixed array of 10 ints uses %zu bytes (size known at compile time).\n",
           sizeof(fixed));

    /* dynamic size: decided while the program runs */
    int n;
    int i;

    printf("How many numbers? ");
    scanf("%d", &n);

    /* ask for n ints' worth of bytes; the result is a pointer */
    int *numbers = malloc((size_t)n * sizeof(int));
    if (numbers == NULL) {
        printf("Out of memory!\n");
        return 1;
    }

    /* from here on it behaves exactly like an array */
    for (i = 0; i < n; i++) {
        numbers[i] = i * i;
    }
    for (i = 0; i < n; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    /* ALWAYS give the memory back */
    free(numbers);

    return 0;
}

/* 01_pointers.c
 * Pointers: variables that hold ADDRESSES of memory.
 *
 * Every variable lives somewhere in memory. &variable gives you
 * its ADDRESS; a pointer stores that address; *pointer follows
 * it back to the variable.
 *
 *     &  -> "address of"
 *     *  -> "the thing this pointer points to" (dereference)
 *
 * This is why scanf needs &x: scanf is a function, and functions
 * can only change variables through pointers (Lesson 03).
 *
 * Compile:
 *     gcc 01_pointers.c -o pointers
 * Run:
 *     ./pointers
 *
 * Lesson 01 - README.md:
 *     int *ptr;          -> declare a pointer to an int
 *     ptr = &number;     -> store the ADDRESS of number
 *     *ptr               -> read the value number holds
 *     *ptr = 99;         -> write THROUGH the pointer
 *     %p                 -> print an address
 */

#include <stdio.h>

int main(void)
{
    int number = 42;
    int *ptr;              /* ptr is a pointer to an int */

    ptr = &number;         /* &number = the ADDRESS of number */

    printf("number   = %d\n", number);                 /* 42      */
    printf("&number  = %p\n", (void *)&number);        /* 0x...   */
    printf("ptr      = %p\n", (void *)ptr);            /* same    */
    printf("*ptr     = %d\n", *ptr);                   /* 42      */

    *ptr = 99;             /* write through the pointer */
    printf("number is now %d\n", number);              /* 99      */
    printf("number changed, but we never touched it directly!\n");

    return 0;
}

/* 08_strings_deep.c
 * Strings, now that you know pointers.
 *
 * A string is a char array ending in '\0'. The "string functions"
 * all take char pointers. Two ways to make a string:
 *
 *     char *greeting = "Hello";   -> points at READ-ONLY text
 *     char buffer[32] = "Hello";  -> copies the text into your own
 *                                    WRITABLE array
 *
 * Compile:
 *     gcc 08_strings_deep.c -o strings_deep
 * Run:
 *     ./strings_deep
 *
 * Lesson 08 - README.md:
 *     char *p = "text";         -> read-only string literal
 *     char buf[32] = "text";    -> writable copy
 *     char names[3][20]         -> an ARRAY of strings
 *     strlen(s)                 -> length (from string.h)
 *     walk a string: while (*p != '\0') p++;
 */

#include <stdio.h>
#include <string.h>      /* strlen */

int main(void)
{
    /* a string literal lives in read-only memory: never write to it */
    char *greeting = "Hello";

    /* an array copies the text into writable memory: safe to change */
    char buffer[32] = "Hello";
    char names[3][20] = {"Ada", "Grace", "Linus"};
    char *p;
    int i;

    /* buffer can be changed... */
    buffer[0] = 'J';
    printf("%s (writable)\n", buffer);

    /* ...and its name is a pointer, so functions take it directly */
    printf("%zu letters in \"%s\"\n", strlen(greeting), greeting);

    /* an array of strings: each row is a char array */
    for (i = 0; i < 3; i++) {
        printf("name %d: %s (%zu letters)\n",
               i, names[i], strlen(names[i]));
    }

    /* walking a string with a pointer */
    printf("Letter walk: ");
    for (p = buffer; *p != '\0'; p++) {
        printf("[%c] ", *p);
    }
    printf("\n");

    return 0;
}

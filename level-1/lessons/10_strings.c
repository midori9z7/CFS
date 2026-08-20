/* 10_strings.c
 * Working with text: strings.
 *
 * In C a string is just an array of char, ending with a special '\0'
 * (the null character) that marks where the text stops. The string.h
 * functions do the heavy lifting for us.
 *
 *     char name[30] = "Ada";   -> room for 29 letters + the '\0'
 *
 * Compile:
 *     gcc 10_strings.c -o strings
 * Run:
 *     ./strings
 *
 * Lesson 10 - README.md:
 *     %s       -> print a string
 *     strlen   -> how many characters (no '\0' counted)
 *     strcpy   -> copy one string into an array
 *     strcat   -> join a string onto the end of another
 *     strcmp   -> compare; returns 0 when the strings are EQUAL
 *     '\0'     -> the invisible end-of-string marker
 *     toupper  -> uppercase a letter (from ctype.h)
 */

#include <stdio.h>
#include <string.h>      /* strlen, strcpy, strcmp, strcat */
#include <ctype.h>       /* toupper */

int main(void)
{
    char first[30] = "Ada";       /* a string is an array of char */
    char last[30]  = "Lovelace";
    char full[60];
    int i;

    /* --- strcpy: copy text into an array ----------------------------- */
    strcpy(full, first);
    strcat(full, " ");            /* strcat: join text onto the end */
    strcat(full, last);
    printf("Full name: %s\n", full);

    /* --- strlen: how many characters (not counting '\0') ------------- */
    printf("'%s' has %zu letters\n", first, strlen(first));
    /* %zu is the format for size_t, the type strlen returns */

    /* --- strcmp: compare two strings; 0 means "equal" ----------------- */
    if (strcmp(first, "Ada") == 0) {
        printf("Yes, this really is Ada.\n");
    }
    if (strcmp(first, "Bob") != 0) {
        printf("And it is definitely not Bob.\n");
    }

    /* --- a string is an array -- walk it with a loop ------------------ */
    printf("Letter by letter: ");
    for (i = 0; first[i] != '\0'; i++) {
        printf("[%c] ", first[i]);
    }
    printf("\n");

    /* --- uppercase machine with toupper() from ctype.h ----------------- */
    for (i = 0; first[i] != '\0'; i++) {
        first[i] = toupper(first[i]);
    }
    printf("Uppercase: %s\n", first);

    return 0;
}

/* word_counter.c
 * A mini "wc": counts lines, words and characters in a text file.
 * The word count is a classic: a "word" starts whenever a
 * non-space character follows a space (or the start of the file).
 *
 * Usage:
 *     word_counter <filename>
 *
 * Compile:
 *     gcc word_counter.c -o word_counter
 * Run:
 *     ./word_counter poem.txt
 *
 * Lessons used: 07, 08, 09. New: argc/argv, fgetc.
 */

#include <stdio.h>
#include <ctype.h>       /* isspace */

int main(int argc, char *argv[])
{
    /* argc = how many words were typed on the command line;
     * argv[0] = the program's own name, argv[1] = first argument */
    FILE *file;
    int ch;
    int lines = 0;
    int words = 0;
    int chars = 0;
    int in_word = 0;     /* am I currently inside a word? */

    if (argc != 2) {
        printf("Usage: word_counter <filename>\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    /* fgetc reads ONE character; EOF means "end of file" */
    while ((ch = fgetc(file)) != EOF) {
        chars++;

        if (ch == '\n') {
            lines++;
        }

        if (isspace(ch)) {
            in_word = 0;              /* a space ends the word */
        } else if (!in_word) {
            in_word = 1;              /* first letter of a new word */
            words++;
        }
    }

    fclose(file);

    printf("%d lines, %d words, %d characters\n", lines, words, chars);
    return 0;
}

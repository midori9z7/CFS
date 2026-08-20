/* file_copier.c
 * Copies a file byte by byte.
 * Uses "rb"/"wb" (binary mode) so it works on every file type,
 * including images -- on Windows, text mode would corrupt \n.
 *
 * Usage:
 *     file_copier <source> <destination>
 *
 * Compile:
 *     gcc file_copier.c -o file_copier
 * Run:
 *     ./file_copier photo.bmp photo_copy.bmp
 *
 * Lessons used: 09. New: fgetc/fputc, binary mode, argc/argv.
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *in;
    FILE *out;
    int ch;

    if (argc != 3) {
        printf("Usage: file_copier <source> <destination>\n");
        return 1;
    }

    in = fopen(argv[1], "rb");
    if (in == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    out = fopen(argv[2], "wb");
    if (out == NULL) {
        printf("Could not create %s\n", argv[2]);
        fclose(in);
        return 1;
    }

    /* the copy itself: one byte at a time until EOF */
    while ((ch = fgetc(in)) != EOF) {
        fputc(ch, out);
    }

    fclose(in);
    fclose(out);
    printf("Copied %s -> %s\n", argv[1], argv[2]);

    return 0;
}

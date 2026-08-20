/* 09_files.c
 * Working with files: fopen, fprintf, fscanf, fclose.
 *
 * To touch a file you open it (getting a FILE *), do your work,
 * then close it. ALWAYS check that fopen did not return NULL --
 * the file may not exist, or you may not have permission.
 *
 * Modes:
 *     "r"  read   (file must exist)
 *     "w"  write  (creates the file, or TRUNCATES it to zero)
 *     "a"  append (writes at the end, keeps what is there)
 *
 * Compile:
 *     gcc 09_files.c -o files
 * Run:
 *     ./files
 *
 * Lesson 09 - README.md:
 *     FILE *f = fopen("output.txt", "w");
 *     if (f == NULL) { ... }       -> ALWAYS check
 *     fprintf(f, "text %d\n", x);  -> printf into a FILE
 *     fgets(line, size, f)         -> read one line
 *     fclose(f);                   -> always close
 *     "w" truncates, "a" appends, "r" reads
 */

#include <stdio.h>

int main(void)
{
    char line[100];

    /* --- write: "w" creates the file or truncates it ---------------- */
    FILE *out = fopen("output.txt", "w");
    if (out == NULL) {
        printf("Could not open output.txt for writing.\n");
        return 1;
    }
    fprintf(out, "Hello, file!\n");
    fprintf(out, "2 + 2 = %d\n", 2 + 2);
    fclose(out);
    printf("Wrote output.txt\n");

    /* --- read: "r" needs the file to exist -------------------------- */
    FILE *in = fopen("output.txt", "r");
    if (in == NULL) {
        printf("Could not open output.txt for reading.\n");
        return 1;
    }

    /* fgets reads one LINE at a time; NULL means "end of file" */
    while (fgets(line, sizeof line, in) != NULL) {
        printf("read: %s", line);   /* fgets keeps the newline */
    }
    fclose(in);

    return 0;
}

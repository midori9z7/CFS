/* caesar_cipher.c
 * The classic Caesar cipher: shift every letter by N positions.
 * Encrypts a message, then decrypts it again to prove it works.
 *
 * The wrap-around uses modulo: (letter + shift) % 26 stays inside
 * the alphabet. The double %26 + 26 %26 trick handles negative
 * shifts (decryption) correctly.
 *
 * Compile:
 *     gcc caesar_cipher.c -o caesar_cipher
 * Run:
 *     ./caesar_cipher
 *
 * Lessons used: 08, 10. New: isalpha, isupper, fgets, strcspn.
 */

#include <stdio.h>
#include <ctype.h>       /* isalpha, isupper */
#include <string.h>      /* strcspn */

/* shift ONE letter by shift positions; leave non-letters alone */
char shift_char(char c, int shift)
{
    if (isalpha((unsigned char)c)) {
        char base = isupper((unsigned char)c) ? 'A' : 'a';
        /* (c - base) is 0..25; add the shift; wrap with modulo;
         * the + 26 and second % keep NEGATIVE results positive */
        int pos = (c - base + shift) % 26;
        if (pos < 0) {
            pos += 26;
        }
        return (char)(pos + base);
    }
    return c;
}

/* shift every character of a string, walking it with a pointer */
void shift_string(char *text, int shift)
{
    char *p;
    for (p = text; *p != '\0'; p++) {
        *p = shift_char(*p, shift);
    }
}

int main(void)
{
    char message[200];
    int shift;

    printf("Message: ");
    fgets(message, sizeof message, stdin);   /* keeps the spaces */

    printf("Shift (e.g. 3): ");
    scanf("%d", &shift);

    /* fgets kept the trailing newline -- cut it off */
    message[strcspn(message, "\n")] = '\0';

    shift_string(message, shift);
    printf("Encrypted: %s\n", message);

    shift_string(message, -shift);           /* shift back */
    printf("Decrypted: %s\n", message);

    return 0;
}

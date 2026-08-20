/* basic_calculator.c
 * Your first real interactive program.
 * It reads lines like "12.5 + 3", checks the input, guards against
 * division by zero, and loops until you type q.
 *
 * - fgets reads a whole LINE of text from the keyboard
 * - sscanf parses that text: "a number, an operator, a number"
 *   (the same %d/%f/%c codes as scanf, but reading FROM a string)
 * - switch picks the operation
 *
 * Compile:
 *     gcc basic_calculator.c -o basic_calculator
 * Run:
 *     ./basic_calculator
 *
 * Lessons used: 04, 05, 06, 07, 10.
 */

#include <stdio.h>

int main(void)
{
    char line[100];
    double a, b;
    char op;

    printf("=== C Basic Calculator ===\n");
    printf("Type an expression like: 12.5 + 3\n");
    printf("Type q to quit.\n");

    while (1) {
        printf("> ");
        if (fgets(line, sizeof line, stdin) == NULL) {
            break;                /* end of input (Ctrl+Z on Windows) */
        }
        if (line[0] == 'q' || line[0] == 'Q') {
            break;
        }

        /* sscanf returns how many pieces matched (here: 3) */
        if (sscanf(line, "%lf %c %lf", &a, &op, &b) != 3) {
            printf("Enter something like: 12.5 + 3\n");
            continue;
        }

        switch (op) {
            case '+':
                printf("%.4f + %.4f = %.4f\n", a, b, a + b);
                break;
            case '-':
                printf("%.4f - %.4f = %.4f\n", a, b, a - b);
                break;
            case '*':
                printf("%.4f * %.4f = %.4f\n", a, b, a * b);
                break;
            case '/':
                if (b == 0.0) {
                    printf("Error: division by zero!\n");
                } else {
                    printf("%.4f / %.4f = %.4f\n", a, b, a / b);
                }
                break;
            default:
                printf("Unknown operator '%c' (use + - * /)\n", op);
        }
    }

    printf("Goodbye!\n");
    return 0;
}

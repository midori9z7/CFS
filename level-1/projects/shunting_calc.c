/* shunting_calc.c
 * The boss fight of Level 1.
 * It reads a full expression like "(1 + 2) * 3 ^ 2" and evaluates it
 * using the shunting-yard algorithm -- a clever way to handle operator
 * precedence and parentheses with two stacks.
 *
 * This one is much longer than the lessons, but look closely and you
 * will recognize almost everything:
 *   - functions (lesson 09)
 *   - switch (lesson 06)
 *   - arrays used as stacks: push = top + 1, pop = top - 1 (lesson 08)
 *   - while loops (lesson 07)
 *   - strings and characters (lesson 10)
 *
 * Sample session:
 *   >> 3 + 4 * 2
 *   = 11
 *   >> (1 + 2) * 3 ^ 2
 *   = 27
 *   >> 2 ^ 3 ^ 2
 *   = 512
 *   >> quit
 *   Goodbye!
 *
 * If you can explain to a friend how this program works, you have
 * officially finished Level 1.
 *
 * Compile:
 *     gcc shunting_calc.c -o shunting_calc -lm
 * Run:
 *     ./shunting_calc
 *
 * Lessons used: 04, 06, 07, 08, 09, 10.
 */

#include <stdio.h>
#include <stdlib.h>      /* atof */
#include <string.h>      /* strlen, strchr, strncmp */
#include <ctype.h>       /* isspace, isdigit */
#include <math.h>        /* pow -- needs -lm on Linux/macOS */

#define MAX 100

/* --- two stacks ----------------------------------------------------- */
/* An array can be used as a stack: a pile of values where you can
 * only touch the TOP. push puts something on top, pop takes it off. */

double value_stack[MAX];
int    value_top = -1;        /* -1 means "empty" */

char   op_stack[MAX];
int    op_top = -1;

void value_push(double v) { value_stack[++value_top] = v; }
double value_pop(void)    { return value_stack[value_top--]; }

void op_push(char c)   { op_stack[++op_top] = c; }
char op_pop(void)      { return op_stack[op_top--]; }
char op_peek(void)     { return op_stack[op_top]; }

/* --- operator helpers ------------------------------------------------ */

/* how strongly does an operator bind? higher = stronger */
int precedence(char op)
{
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

/* should the new operator op1 make the stack's op2 run first?
 * In other words: is op2 at least as strong as op1? */
int op_ge(char op1, char op2)
{
    if (op2 == '(') {
        return 0;               /* never pop a '(' from the stack */
    }
    if (precedence(op1) != precedence(op2)) {
        return precedence(op1) <= precedence(op2);
    }
    /* equal strength: normal operators are left-associative (pop),
     * but '^' is right-associative, so a second '^' does NOT pop. */
    return op2 != '^';
}

double apply(char op, double a, double b)
{
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default:  return 0.0;
    }
}

/* --- the evaluator ---------------------------------------------------- */

/* evaluate("(1 + 2) * 3 ^ 2") returns 27 */
double evaluate(const char *expr)
{
    int i = 0;
    int len = (int)strlen(expr);

    value_top = -1;             /* reset both stacks */
    op_top = -1;

    while (i < len) {
        char c = expr[i];

        /* skip spaces */
        if (isspace((unsigned char)c)) {
            i++;
            continue;
        }

        /* a number: collect digits (and one dot) into a buffer */
        if (isdigit((unsigned char)c) || c == '.') {
            char buffer[32];
            int j = 0;
            while (i < len && (isdigit((unsigned char)expr[i]) || expr[i] == '.')) {
                buffer[j++] = expr[i++];
            }
            buffer[j] = '\0';
            value_push(atof(buffer));
            continue;
        }

        /* opening parenthesis: push it, wait for the ')'. */
        if (c == '(') {
            op_push(c);
            i++;
            continue;
        }

        /* closing parenthesis: run everything until the '(' */
        if (c == ')') {
            while (op_top >= 0 && op_peek() != '(') {
                double b = value_pop();
                double a = value_pop();
                value_push(apply(op_pop(), a, b));
            }
            op_pop();           /* pop the '(' itself */
            i++;
            continue;
        }

        /* unary minus: "-5" means (0 - 5). A '-' is unary when the
         * previous significant character (skipping spaces) is the
         * start of the expression, a '(', or another operator. */
        if (c == '-') {
            int j = i - 1;
            while (j >= 0 && isspace((unsigned char)expr[j])) {
                j--;
            }
            if (j < 0 || expr[j] == '(' || strchr("+-*/^", expr[j])) {
                value_push(0.0);
                op_push('-');
                i++;
                continue;
            }
        }

        /* a normal operator: let stronger-or-equal operators on the
         * stack run first, then push this one. */
        if (strchr("+-*/^", c)) {
            while (op_top >= 0 && op_ge(c, op_peek())) {
                double b = value_pop();
                double a = value_pop();
                value_push(apply(op_pop(), a, b));
            }
            op_push(c);
            i++;
            continue;
        }

        /* unknown character: skip it */
        i++;
    }

    /* drain whatever is left on the operator stack */
    while (op_top >= 0) {
        double b = value_pop();
        double a = value_pop();
        value_push(apply(op_pop(), a, b));
    }

    return value_pop();
}

/* --- main loop --------------------------------------------------------- */

int main(void)
{
    char line[100];

    printf("=== Shunting-Yard Calculator ===\n");
    printf("Operators: + - * / ^ ( )   Example: (1 + 2) * 3 ^ 2\n");
    printf("Type quit to exit.\n");

    while (1) {
        printf(">> ");
        if (fgets(line, sizeof line, stdin) == NULL) {
            break;              /* end of input (Ctrl+Z on Windows) */
        }
        if (strncmp(line, "quit", 4) == 0) {
            break;
        }
        if (line[0] == '\n') {
            continue;           /* empty line: just ask again */
        }

        printf("= %g\n", evaluate(line));
        /* %g prints numbers the short way: 27, not 27.000000 */
    }

    printf("Goodbye!\n");
    return 0;
}

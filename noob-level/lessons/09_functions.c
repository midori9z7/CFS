/* 09_functions.c
 * Your own reusable building blocks: functions.
 *
 * A function is a named chunk of code you can call again and again.
 * It takes inputs (parameters), does something, and can return
 * exactly one value.
 *
 *     return type + name + (parameters)
 *     double square(double x)   -> takes one double, returns one double
 *     void describe_number(int) -> "void" = returns NOTHING, just acts
 *
 * A PROTOTYPE up top tells the compiler "this function exists, here
 * is its shape"; the real body comes after main().
 *
 * Compile:
 *     gcc 09_functions.c -o functions -lm
 *     (the -lm links the math library; Linux/macOS need it for sqrt)
 * Run:
 *     ./functions
 *
 * Lesson 09 - README.md:
 *     prototype  -> the shape of the function, before main()
 *     definition -> the body, after main()
 *     return     -> send one value back
 *     void       -> returns nothing
 *     parameters are COPIES: the caller's variables never change
 */

#include <stdio.h>
#include <math.h>      /* for sqrt() */

/* --- prototypes: "these functions exist, here is their shape" -------- */
double add(double a, double b);
double hypotenuse(double a, double b);
double square(double x);
void   describe_number(int n);

int main(void)
{
    printf("add(3, 4)        = %.1f\n", add(3.0, 4.0));
    printf("hypotenuse(3, 4) = %.2f\n", hypotenuse(3.0, 4.0));
    printf("square(2.5)      = %.2f\n", square(2.5));

    describe_number(7);
    describe_number(8);

    return 0;
}

/* --- definitions: the actual bodies ---------------------------------- */

double add(double a, double b)
{
    return a + b;        /* return sends the result back to the caller */
}

double hypotenuse(double a, double b)
{
    return sqrt(a * a + b * b);
}

double square(double x)
{
    return x * x;
}

/* void: performs an action, returns nothing */
void describe_number(int n)
{
    if (n % 2 == 0) {
        printf("%d is even\n", n);
    } else {
        printf("%d is odd\n", n);
    }
}

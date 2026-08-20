/* 10_recursion.c
 * Recursion: a function that calls ITSELF.
 *
 * Every recursive function needs two parts:
 *     1. a BASE CASE  -- a situation so small the answer is known,
 *        no recursive call needed. Without it, the function calls
 *        itself forever and the program crashes (stack overflow).
 *     2. a RECURSIVE CASE -- break the problem into a smaller
 *        version of itself.
 *
 * Compile:
 *     gcc 10_recursion.c -o recursion
 * Run:
 *     ./recursion
 *
 * Lesson 10 - README.md:
 *     countdown(n) -> countdown(n - 1)   : call itself with n-1
 *     base case    -> if (n == 0) return; : where the calls stop
 *     factorial:   n! = n * (n-1)!
 *     fibonacci:   f(n) = f(n-1) + f(n-2)
 *     every call gets its own copy of the parameters (the stack)
 */

#include <stdio.h>

/* countdown: print n, then count down from n-1 */
void countdown(int n)
{
    if (n == 0) {                  /* base case: stop */
        printf("Liftoff!\n");
        return;
    }
    printf("%d ", n);
    countdown(n - 1);              /* recursive case */
}

/* factorial: n! = n * (n-1)!  with 0! = 1 */
long long factorial(int n)
{
    if (n <= 1) {
        return 1;                  /* base case */
    }
    return n * factorial(n - 1);   /* recursive case */
}

/* fibonacci: f(0)=0, f(1)=1, f(n)=f(n-1)+f(n-2) */
int fibonacci(int n)
{
    if (n <= 1) {
        return n;                  /* base case */
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void)
{
    int i;

    printf("Countdown:\n");
    countdown(5);

    printf("\nFactorials:\n");
    for (i = 0; i <= 10; i++) {
        printf("%2d! = %lld\n", i, factorial(i));
    }

    printf("Fibonacci:\n");
    for (i = 0; i < 15; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");

    return 0;
}

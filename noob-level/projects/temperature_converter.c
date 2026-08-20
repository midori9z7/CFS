/* temperature_converter.c
 * A small project combining: input, output, conditionals, formulas.
 *
 * Converts temperatures between Celsius and Fahrenheit.
 *     C -> F :  F = C * 9 / 5 + 32
 *     F -> C :  C = (F - 32) * 5 / 9
 *
 * Try it:
 *     Enter C, then a Celsius value like 100
 *     Enter F, then a Fahrenheit value like 98.6
 *
 * Compile:
 *     gcc temperature_converter.c -o temperature_converter
 * Run:
 *     ./temperature_converter
 *
 * Lessons used: 02, 03, 04, 05.
 */

#include <stdio.h>

int main(void)
{
    double celsius, fahrenheit;
    char choice;

    printf("===========================\n");
    printf("  Temperature Converter\n");
    printf("===========================\n");
    printf("Enter C to convert Celsius -> Fahrenheit\n");
    printf("Enter F to convert Fahrenheit -> Celsius\n");
    printf("Your choice: ");
    scanf(" %c", &choice);        /* space before %c eats the newline */

    if (choice == 'C' || choice == 'c') {
        printf("Temperature in Celsius: ");
        scanf("%lf", &celsius);
        fahrenheit = celsius * 9.0 / 5.0 + 32.0;
        printf("%.1f C = %.1f F\n", celsius, fahrenheit);
    } else if (choice == 'F' || choice == 'f') {
        printf("Temperature in Fahrenheit: ");
        scanf("%lf", &fahrenheit);
        celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
        printf("%.1f F = %.1f C\n", fahrenheit, celsius);
    } else {
        printf("Invalid choice. Please enter C or F.\n");
    }

    return 0;
}

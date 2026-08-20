/* 01_hello_world.c
 * Your very first C program.
 *
 * Compile:
 *     gcc 01_hello_world.c -o hello_world
 * Run:
 *     ./hello_world        (Linux / macOS / Git Bash / MSYS2)
 *     .\hello_world.exe    (Windows)
 *
 * Lesson 01 - README.md:
 *     #include <stdio.h>  -> gives us the printf() function
 *     int main(void)      -> every program starts running here
 *     printf("...")       -> print text to the screen
 *     return 0;           -> tell the OS: everything went fine
 *     \n                  -> "new line" inside a string
 */

#include <stdio.h>   // stdio = STanDard Input Output.
                     // This line "includes" the functions we need
                     // to print text to the screen (printf).

int main(void)       // Every program needs a main() function.
{                    // { opens the body of main().

    printf("Hello, World!\n");
    // printf() prints text to the screen.
    // \n means "new line": move to the next line after printing.
    // Every statement in C ends with a semicolon ; -- do not forget it!

    return 0;
    // "return 0" tells the operating system: the program
    // finished successfully. 0 means "no error".

}                    // } closes the body of main().

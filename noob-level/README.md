# C Noob Level

> From "I know nothing" to "I can write a calculator."
> This level assumes zero programming experience. Every lesson is one small,
> runnable program. Read the lesson, run the program, change it, break it,
> fix it. That last part is how you actually learn.

---s

## 0. Setup

### 0.1 Get a compiler

C source code is plain text. A *compiler* turns that text into a program
you can run. We use **gcc**, which is free and works on Windows, macOS
and Linux.

- **Windows**: install [MSYS2](https://www.msys2.org/), then in the MSYS2
  terminal run `pacman -S mingw-w64-ucrt-x86_64-gcc`.
  (Alternatively use the standalone
  [MinGW-w64 builds](https://github.com/niXman/mingw-builds-binaries/releases).)
- **macOS**: `xcode-select --install` (gives you `clang`, which works the
  same way), or `brew install gcc`
- **Linux (Debian/Ubuntu)**: `sudo apt install gcc`

Check that it worked:

```text
$ gcc --version
gcc (GCC) 15.2.0
```

### 0.2 Compile and run a program

Every program in this folder is compiled the same way:

```text
gcc 01_hello_world.c -o hello_world
```

- `gcc` — the compiler
- `01_hello_world.c` — the source file (the code you write)
- `-o hello_world` — "put the finished program in a file named
  `hello_world`" (on Windows the file becomes `hello_world.exe`)

Then run it:

```text
# Linux / macOS
./hello_world

# Windows
.\hello_world.exe
```

You should see:

```text
Hello, World!
```

> **Tip**: there is also a `build.ps1` script in this folder that compiles
> every program at once. See section 3.

---

## 1. The Lessons

| # | File | You will learn |
|---|------|----------------|
| 01 | `lessons/01_hello_world.c` | The skeleton of a C program |
| 02 | `lessons/02_variables.c` | Variables and data types |
| 03 | `lessons/03_arithmetic.c` | Doing math with numbers |
| 04 | `lessons/04_input_output.c` | Asking the user for input |
| 05 | `lessons/05_conditionals.c` | `if` / `else` decisions |
| 06 | `lessons/06_switch_case.c` | Choosing between many cases |
| 07 | `lessons/07_loops.c` | Repeating things with loops |
| 08 | `lessons/08_arrays.c` | Lists of values: arrays |
| 09 | `lessons/09_functions.c` | Your own functions |
| 10 | `lessons/10_strings.c` | Working with text |

### Lesson 01 — Hello, C!

**Goals:** see the shape of a program, write your first line of code.

```c
#include <stdio.h>   // stdio = STanDard Input Output.

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```

What is happening:

- `#include <stdio.h>` — a *preprocessor directive*. It pastes in the
  "standard input/output" library, which gives us `printf()`. Anything
  starting with `#` is handled before compilation.
- `int main(void)` — every program needs exactly one `main()`. Execution
  starts at the first line of `main()` and ends when it returns.
- `printf("...")` — print text to the screen. `\n` inside the string is
  an escape sequence meaning "new line".
- `return 0;` — hands the number 0 back to the operating system. By
  convention, 0 means "everything went fine".
- Every statement ends with a semicolon `;`. Forgetting one is the single
  most common beginner error.
- `//` and `/* ... */` are comments — the compiler ignores them. Comments
  explain *why* code exists.

**Exercise:** change the message, recompile, run it again. Print two
lines. Print a number: `printf("%d\n", 42);`.

### Lesson 02 — Variables

**Goals:** store values in named boxes.

```c
#include <stdio.h>

int main(void)
{
    int    age    = 25;    // int   : whole numbers (no decimals)
    float  height = 1.78f; // float : decimals (single precision)
    double weight = 72.5;  // double: decimals (double precision)
    char   grade  = 'A';   // char  : ONE single character

    printf("Age   : %d\n", age);
    printf("Height: %.2f meters\n", height);  // %.2f = 2 decimal places
    printf("Weight: %.1f kg\n", weight);
    printf("Grade : %c\n", grade);

    age = 26;              // assign a NEW value (no type keyword again!)
    printf("Next year I will be %d years old.\n", age);

    printf("An int uses %zu bytes, a char uses %zu byte.\n",
           sizeof(int), sizeof(char));
    return 0;
}
```

The basic types:

| Type | Holds | Example | Print with | Read with |
|------|-------|---------|-----------|-----------|
| `int` | whole numbers | `-3, 0, 42` | `%d` | `%d` |
| `double` | decimals, double precision | `72.5` | `%f` | `%lf` |
| `float` | decimals, single precision | `1.78f` | `%f` | `%f` |
| `char` | ONE character | `'A'` | `%c` | `%c` |

Rules that matter right now:

1. Declare once with its type, then use. To change the value later, do
   **not** repeat the type: `age = 26;`, not `int age = 26;` again.
2. `char` uses **single quotes** `'A'`. Double quotes `"A"` would be a
   *string* — a different thing (that's `%s`, Lesson 10).
3. Prefer `double` over `float` for all math. `float` exists mainly for
   saving memory.
4. `sizeof()` tells you how many bytes a type uses on your machine.

**Exercise:** add a `double` variable called `weight`, set it to your
weight, print it with `%.2f`. What happens if you put a decimal number
into an `int` variable?

### Lesson 03 — Arithmetic

**Goals:** do math, and discover the most famous C trap:
integer division.

```c
#include <stdio.h>

int main(void)
{
    int a = 17;
    int b = 5;

    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", a + b);   // 22
    printf("a - b = %d\n", a - b);   // 12
    printf("a * b = %d\n", a * b);   // 85
    printf("a / b = %d\n", a / b);   // 3  <-- integer division!
    printf("a %% b = %d\n", a % b);  // 2  (remainder of 17 / 5)

    printf("17 / 5 as ints    = %d\n", 17 / 5);        // 3
    printf("17 / 5 as doubles = %.1f\n", 17.0 / 5.0);  // 3.4

    printf("2 + 3 * 4     = %d\n", 2 + 3 * 4);   // 14
    printf("(2 + 3) * 4   = %d\n", (2 + 3) * 4); // 20
    return 0;
}
```

The rules that matter right now:

1. **`17 / 5` is `3`, not `3.4`.** When both numbers are integers, C
   does integer division and simply drops the fraction. Write `17.0 / 5`
   (or `17 / 5.0`) when you want a real answer. This mistake has wrecked
   many scientific programs — remember it.
2. `a % b` gives the remainder: `17 % 5` is `2`.
3. To print a real `%` sign, write `%%` in the format string.
4. Multiply/divide before add/subtract (`* / %` bind tighter than `+ -`),
   and parentheses `( )` always win.
5. There is no `**` power operator in C — that is `pow(a, b)`, and it
   lives in `math.h` (see Lesson 09).

**Exercise:** print `10 / 4` and `10.0 / 4` and `10 % 4` and compare.
Print the area of a circle with radius 5: `3.14159 * 5 * 5`.

### Lesson 04 — Input and Output

**Goals:** make the program talk back and forth with the user.

```c
#include <stdio.h>

int main(void)
{
    int  yourAge = 0;    // start at 0; scanf will overwrite it
    char initial = '?';

    printf("How old are you? ");
    scanf("%d", &yourAge);

    printf("What is the first letter of your name? ");
    scanf(" %c", &initial);   // note the SPACE before %c

    printf("\nNice to meet you, %c! You are %d years old.\n",
           initial, yourAge);
    return 0;
}
```

- `scanf(...)` — stop and wait for the user to type something. Program
  execution *pauses* until they press Enter.
- **The `&`.** scanf needs to know *where in memory* to put the value,
  so you pass the address of the variable: `&yourAge`. If you forget the
  `&`, the program may crash or silently corrupt memory. (Why exactly?
  You will understand `&` fully in the pointers level.)
- **`%lf` vs `%f`.** printf prints a `double` with `%f`, but scanf reads
  a `double` with `%lf`. Mixing them up produces garbage values.
- **The leftover newline.** Pressing Enter leaves a newline in the input
  buffer. Reading a `char` right after a number would grab that newline
  instead of the letter. The fix is a space before `%c`: `scanf(" %c",
  &c);` — the space tells scanf to skip whitespace first.

**Exercise:** read a `double` (e.g. your height in meters) and print it
back with 2 decimals. What happens if you type a letter when the program
expects a number?

### Lesson 05 — Conditionals

**Goals:** make decisions with `if`.

```c
#include <stdio.h>

int main(void)
{
    int number;

    printf("Enter an integer: ");
    scanf("%d", &number);

    if (number > 0) {
        printf("%d is positive\n", number);
    } else if (number < 0) {
        printf("%d is negative\n", number);
    } else {
        printf("%d is zero\n", number);
    }

    if (number % 2 == 0) printf("%d is even\n", number);
    if (number % 2 != 0) printf("%d is odd\n", number);

    if (number > 0 && number % 2 == 0) {
        printf("%d is a positive even number\n", number);
    }
    if (number == 7 || number == 13) {
        printf("%d is a lucky number!\n", number);
    }
    if (!(number == 0)) printf("%d is not zero\n", number);

    if (number > 1000) printf("%d is BIG\n", number);

    return 0;
}
```

- Comparison operators: `==` equal, `!=` not equal, `>` greater, `<`
  less, `>=` and `<=`.
- Logical operators: `&&` (and), `||` (or), `!` (not).
- A one-line `if` needs no braces; `if (cond) statement;` runs that one
  statement only when `cond` is true. With more than one statement, you
  need `{ }`.
- `%` is perfect for even/odd checks: a number is even when `n % 2 == 0`.

**Exercise:** extend the program to also say "BIG" when the number is
greater than 1000 (already there — now make it say "tiny" when the number
is between 1 and 10). Print "is divisible by 5" when appropriate.

### Lesson 06 — switch

**Goals:** replace long chains of `else if` with one clean `switch`.

```c
#include <stdio.h>

int main(void)
{
    int score;
    int tens;
    char grade = '?';

    printf("Enter a score (0-100): ");
    scanf("%d", &score);

    tens = score / 10;    // 95 -> 9, 87 -> 8, 100 -> 10, 5 -> 0

    switch (tens) {
        case 10:          // falls through on purpose
        case 9:
            grade = 'A';
            break;
        case 8:
            grade = 'B';
            break;
        case 7:
            grade = 'C';
            break;
        case 6:
            grade = 'D';
            break;
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            grade = 'F';
            break;
        default:
            grade = '?';  // 101, -3, anything weird
            break;
    }

    if (grade != '?') {
        printf("Your grade is %c\n", grade);
    } else {
        printf("Invalid score. Try a number from 0 to 100.\n");
    }

    switch (grade) {
        case 'A': printf("Excellent!\n");            break;
        case 'B': printf("Good job!\n");             break;
        case 'C': printf("Not bad.\n");              break;
        case 'D': printf("Almost failing...\n");     break;
        case 'F': printf("Time to study more!\n");   break;
        default:  printf("No comment.\n");           break;
    }

    return 0;
}
```

- `switch` works on `int`s and `char`s — **not** on `double`s, and not on
  strings.
- C's `switch` cannot do ranges like Fortran's `case (90:100)`. The C
  trick is integer division: `score / 10` collapses every range into one
  number.
- Every branch ends with `break`. Without it, execution **falls through**
  into the next branch — that is a feature (see `case 10: case 9:`),
  use it on purpose.
- `default` catches everything not listed above it. Put it last.

**Exercise:** rewrite it so a score of exactly 100 prints an extra
"Perfect score!". Add a `case` that says "Impossible!" for scores above
100.

### Lesson 07 — Loops

**Goals:** repeat code with `for`, `while` and `do-while`.

```c
#include <stdio.h>

int main(void)
{
    int i, total, counter;

    printf("Counting from 1 to 10:\n");
    for (i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }

    printf("Even numbers from 0 to 20:\n");
    for (i = 0; i <= 20; i += 2) {
        printf("%d ", i);
    }
    printf("\n");

    printf("Countdown:\n");
    for (i = 10; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("Liftoff!\n");

    total = 0;
    for (i = 1; i <= 100; i++) {
        total = total + i;
    }
    printf("Sum of 1 to 100 = %d\n", total);

    counter = 1;
    while (counter <= 5) {
        printf("while: counter = %d\n", counter);
        counter = counter + 1;
    }

    counter = 10;
    do {
        printf("do-while: counter = %d\n", counter);
        counter = counter + 1;
    } while (counter < 10);

    printf("Using continue and break:\n");
    for (i = 1; i <= 10; i++) {
        if (i == 3) continue;   // skip 3, keep going
        if (i == 8) break;      // stop completely at 8
        printf("i = %d\n", i);
    }

    return 0;
}
```

- `for (start; condition; step)` — `i` starts at 1; while `i <= 10` the
  body runs; after every round `i++` adds 1.
- `i += 2` steps by 2; `i--` counts down.
- `while (condition)` — checks *first*, then runs. If the condition never
  becomes false, the program loops forever — a real bug.
- `do { ... } while (condition)` — runs *at least once*, then checks.
- `break` leaves the loop immediately; `continue` skips the rest of this
  round and starts the next one.
- The classic accumulator pattern: `total = total + i`.

**Exercise:** print the first 10 square numbers (`i * i`). Use a loop to
print the multiplication table for 7.

### Lesson 08 — Arrays

**Goals:** hold many values in one variable.

```c
#include <stdio.h>

int main(void)
{
    int i;
    double scores[5] = {88.0, 92.5, 79.0, 95.0, 85.5};
    double sum = 0.0, average, max;
    int matrix[3][3];
    int row, col;

    for (i = 0; i < 5; i++) {
        sum = sum + scores[i];
    }
    average = sum / 5.0;
    printf("Average score = %.2f\n", average);

    max = scores[0];
    for (i = 1; i < 5; i++) {
        if (scores[i] > max) max = scores[i];
    }
    printf("Maximum      = %.2f\n", max);

    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            matrix[row][col] = (row + 1) * 10 + (col + 1);
        }
    }
    printf("Matrix:\n");
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            printf("%4d", matrix[row][col]);
        }
        printf("\n");
    }

    scores[0] = 100.0;
    printf("After a re-test, the first score is %.1f\n", scores[0]);

    return 0;
}
```

- `double scores[5] = { ... };` — five `double` boxes under one name,
  numbered `scores[0]` ... `scores[4]`. **C indexing starts at 0.**
  (Fortran starts at 1 — if you are coming from the FFS repo, this is
  the biggest mental switch.)
- Arrays pair perfectly with loops: the loop variable becomes the index.
- There is no built-in `max()` in C — you write the loop yourself.
- `int matrix[3][3]` is a 2D array: a grid of rows and columns.
- Going past the end (`scores[5]` in this program) is *undefined
  behavior*: the program compiles, then misbehaves or crashes. The
  compiler does not catch it — you must keep the bounds straight.

**Exercise:** read 5 numbers from the user into an array, then print
them in reverse order. Print the sum of the matrix's diagonal
(`matrix[0][0] + matrix[1][1] + matrix[2][2]`).

### Lesson 09 — Functions

**Goals:** write your own reusable building blocks.

```c
#include <stdio.h>
#include <math.h>       /* for sqrt() -- needs -lm on Linux/macOS */

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

double add(double a, double b)
{
    return a + b;        /* return sends the result back */
}

double hypotenuse(double a, double b)
{
    return sqrt(a * a + b * b);
}

double square(double x)
{
    return x * x;
}

void describe_number(int n)
{
    if (n % 2 == 0) {
        printf("%d is even\n", n);
    } else {
        printf("%d is odd\n", n);
    }
}
```

- **Prototype** (before `main`): "this function exists, here is its
  shape." The compiler needs it to check your calls.
- **Definition** (after `main`): the actual body.
- **`return`** sends exactly one value back to the caller. A function
  whose type is `void` returns nothing — it just performs an action.
- Parameters are **copies**: the function can change its own `a` and `b`
  without touching the caller's variables.
- `sqrt` (and `pow`, `sin`, ...) live in `math.h`. On Linux/macOS you
  must add `-lm` to the compile command to link the math library.

**Exercise:** write a function `square(n)` (done — now write
`celsius_to_fahrenheit(c)`) and a `void` function that prints a number
and its square.

### Lesson 10 — Strings

**Goals:** handle text: join, measure, compare, transform.

```c
#include <stdio.h>
#include <string.h>     /* strlen, strcpy, strcmp, strcat */
#include <ctype.h>      /* toupper */

int main(void)
{
    char first[30] = "Ada";
    char last[30]  = "Lovelace";
    char full[60];
    int i;

    strcpy(full, first);
    strcat(full, " ");
    strcat(full, last);
    printf("Full name: %s\n", full);

    printf("'%s' has %zu letters\n", first, strlen(first));

    if (strcmp(first, "Ada") == 0) printf("Yes, this really is Ada.\n");
    if (strcmp(first, "Bob") != 0) printf("And it is definitely not Bob.\n");

    printf("Letter by letter: ");
    for (i = 0; first[i] != '\0'; i++) {
        printf("[%c] ", first[i]);
    }
    printf("\n");

    for (i = 0; first[i] != '\0'; i++) {
        first[i] = toupper(first[i]);
    }
    printf("Uppercase: %s\n", first);

    return 0;
}
```

- A string in C is just an **array of char** ending with the invisible
  `'\0'` (the null character) that marks where the text stops. `%s`
  prints everything up to the `'\0'`.
- `strcpy(dest, src)` copies; `strcat(dest, src)` joins onto the end.
- `strcmp(a, b)` compares and returns **0 when the strings are equal**
  (not 1! — a classic beginner trap). Any nonzero value means different.
- `strlen` returns a `size_t`, printed with `%zu`.
- `toupper(c)` (from `ctype.h`) uppercases one letter. The loop turns
  the whole string into uppercase.

**Exercise:** make it print "Ms. " before the name. Find the position of
the space in the full name with a loop. Count how many times the letter
"r" appears in `"Fortran"`.

---

## 2. The Projects

Now that you know the pieces, build real little programs. Each project
uses several lessons at once. Try to write each one yourself before
looking at the solution file.

### Project A — addition (`projects/addition.c`)

Reads two numbers and prints their sum. The first program with real
input and a real calculation.

```c
#include <stdio.h>

int main(void)
{
    double a, b, s;

    printf("Enter two numbers: ");
    scanf("%lf %lf", &a, &b);   // one scanf can read several values

    s = a + b;
    printf("Sum = %.2f\n", s);

    return 0;
}
```

**Lessons used:** 02, 03, 04.

### Project B — temperature converter (`projects/temperature_converter.c`)

Ask for C or F, read a temperature, convert it with one of two
formulas. `if / else` picks the formula.

```c
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
    scanf(" %c", &choice);        // space before %c eats the newline

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
```

**Lessons used:** 02, 03, 04, 05.

### Project C — circle (`projects/circle.c`)

Read a radius, compute area and circumference. Introduces `#define` —
a **constant**: a name replaced by its value everywhere in the file,
written in UPPERCASE by convention.

```c
#include <stdio.h>

#define PI 3.14159265358979

int main(void)
{
    double radius = 0.0;
    double area;
    double circumference;

    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);        // note: %lf for scanf, %f for printf

    area          = PI * radius * radius;
    circumference = 2.0 * PI * radius;

    printf("Radius         : %.2f\n", radius);
    printf("Area           : %.2f\n", area);
    printf("Circumference  : %.2f\n", circumference);

    return 0;
}
```

**Lessons used:** 02, 03, 04.

### Project D — multiplication table (`projects/multiplication_table.c`)

Two nested loops, plus the `%4d` field width, build a neatly aligned
table. This is where formatted output finally pays off.

```c
#include <stdio.h>

int main(void)
{
    int n, i, j;

    printf("Table size (e.g. 10): ");
    scanf("%d", &n);

    printf("%4s", "");            /* blank corner, 4 wide */
    for (i = 1; i <= n; i++) {
        printf("%4d", i);
    }
    printf("\n");

    for (i = 1; i <= n; i++) {
        printf("%4d", i);         /* row label */
        for (j = 1; j <= n; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }

    return 0;
}
```

**Lessons used:** 03, 04, 07.

### Project E — number guessing game (`projects/number_guessing_game.c`)

The computer picks a secret number; you guess. The loop ends only when
you win. Also introduces checking scanf()'s **return value** — the
polite way to handle wrong input instead of crashing.

```c
#include <stdio.h>
#include <stdlib.h>      /* rand, srand */
#include <time.h>        /* time */

int main(void)
{
    int secret;
    int guess;
    int tries = 0;

    srand((unsigned)time(NULL));   /* seed the random generator once */
    secret = rand() % 100 + 1;     /* a number from 1 to 100 */

    printf("==========================================\n");
    printf("  I am thinking of a number from 1 to 100.\n");
    printf("  Can you guess it?\n");
    printf("==========================================\n");

    for (;;) {                     /* loop forever... */
        printf("Your guess: ");
        {
            int read = scanf("%d", &guess);
            if (read == EOF) {     /* input ran out: stop politely */
                printf("Thanks for playing!\n");
                break;
            }
            if (read != 1) {       /* not a number: discard & retry */
                scanf("%*s");
                printf("Please type a whole number.\n");
                continue;
            }
        }

        tries = tries + 1;

        if (guess < secret) {
            printf("Too low!\n");
        } else if (guess > secret) {
            printf("Too high!\n");
        } else {
            printf("Correct! The secret number was %d\n", secret);
            printf("It took you %d tries.\n", tries);
            break;                 /* ...until we win */
        }
    }

    return 0;
}
```

- `srand` + `rand` — the classic random pair: seed once, then ask for
  numbers. `% 100 + 1` squeezes a result into 1..100.
- `scanf` returns how many values it managed to read. `1` means "one
  number read"; `0` means "that was not a number"; `EOF` means "no more
  input at all". All three are handled above.

**Lessons used:** 04, 05, 07. New: `rand`, `srand`, `time`.

### Project F — FizzBuzz (`projects/fizzbuzz.c`)

The famous beginner exercise. Count 1 to 100; replace multiples of 3
with "Fizz", multiples of 5 with "Buzz", multiples of both with
"FizzBuzz".

```c
#include <stdio.h>

int main(void)
{
    int i;

    for (i = 1; i <= 100; i++) {
        if (i % 15 == 0) {          /* 15 = 3 * 5: multiple of both */
            printf("%3d FizzBuzz\n", i);
        } else if (i % 3 == 0) {
            printf("%3d Fizz\n", i);
        } else if (i % 5 == 0) {
            printf("%3d Buzz\n", i);
        } else {
            printf("%3d\n", i);
        }
    }

    return 0;
}
```

**Lessons used:** 03, 05, 07.

### Project G — basic calculator (`projects/basic_calculator.c`)

Your first real interactive program. It reads lines like `12.5 + 3`,
checks the input, guards against division by zero, and loops until you
type `q`.

- `fgets` reads a whole **line** of text from the keyboard
- `sscanf` parses that line: "a number, an operator, a number" — the
  same `%d` / `%f` / `%c` codes as `scanf`, but reading FROM a string
- `switch` picks the operation
- `sscanf`'s return value (3 = all pieces matched) catches bad lines

```c
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
```

A sample session:

```text
=== C Basic Calculator ===
Type an expression like: 12.5 + 3
Type q to quit.
> 12.5 + 3
12.5000 + 3.0000 = 15.5000
> 10 / 0
Error: division by zero!
> q
Goodbye!
```

**Lessons used:** 04, 05, 06, 07, 10.

### Project H — shunting-yard calculator (`projects/shunting_calc.c`)

The boss fight of the noob level. It reads a full expression like
`(1 + 2) * 3 ^ 2` or `2 ^ 3 ^ 2` and evaluates it using the
*shunting-yard algorithm* — a clever way to handle operator precedence
and parentheses with two stacks.

This one is much longer than the lessons, but look closely and you will
recognize almost everything:

- functions with prototypes (Lesson 09)
- `switch` everywhere (Lesson 06)
- arrays used as *stacks* — push with `top = top + 1`, pop with
  `top = top - 1` (Lesson 08)
- `while` loops (Lesson 07)
- strings and characters, `sscanf`-style parsing (Lessons 04, 10)

```text
>> 3 + 4 * 2
= 11
>> (1 + 2) * 3 ^ 2
= 27
>> 2 ^ 3 ^ 2
= 512
>> quit
Goodbye!
```

Note that `^` is right-associative, like in real math: `2 ^ 3 ^ 2`
means `2 ^ (3 ^ 2)` = 512. The program also understands unary minus,
so `-5 + 3` and `2 * -3` work.

If you can explain to a friend how this program works, you have
officially finished the noob level.

---

## 3. Build Everything

`build.ps1` compiles every lesson and every project into the `bin/`
folder:

```text
powershell -ExecutionPolicy Bypass -File .\noob-level\build.ps1
```

Afterwards the programs live in `noob-level\bin\`:

```text
noob-level\bin\01_hello_world.exe
noob-level\bin\addition.exe
noob-level\bin\basic_calculator.exe
...
```

The compiled `.exe` files are not stored in git (see the repository
root `.gitignore`) — anyone can regenerate them from the source in one
command. Compiling from source is the normal C workflow.

---

## 4. Quick Reference

| You want to... | Write |
|----------------|-------|
| Print text / numbers | `printf("hi %d\n", x);` |
| Read a number | `scanf("%lf", &x);` |
| Declare an integer | `int n;` |
| Declare a decimal | `double x;` |
| Declare a character | `char c = 'A';` |
| Declare a constant | `#define PI 3.14` |
| Declare an array | `double a[10];` |
| Print a string | `printf("%s\n", s);` |
| Decide | `if (x > 0) { ... } else { ... }` |
| Compare | `==  !=  >  <  >=  <=` |
| Combine tests | `&&  ||  !` |
| Many choices | `switch (x) { case 1: ... break; }` |
| Repeat | `for (i = 1; i <= 10; i++) { ... }` |
| Loop while true | `while (cond) { ... }` |
| Run at least once | `do { ... } while (cond);` |
| Skip / stop a loop | `continue` / `break` |
| Remainder | `a % b` |
| Power / square root | `pow(a, b)` / `sqrt(x)` — from `math.h` |
| Own function | `double f(double x) { return ...; }` |
| Copy a string | `strcpy(dest, src)` |
| Join strings | `strcat(dest, src)` |
| Compare strings | `strcmp(a, b) == 0` (0 means equal!) |
| String length | `strlen(s)` (prints with `%zu`) |

---

## 5. Coming From the Fortran Repo (FFS)?

The CFS noob level mirrors FFS, but the two languages have some famous
differences — know them and you will not be caught off guard:

| Fortran (FFS) | C (CFS) | Note |
|---------------|---------|------|
| `implicit none` | (nothing) | C always requires declarations — no opt-out needed |
| `program x ... end` | `int main(void) { ... }` | the whole program lives in `main` |
| `print *, "hi", x` | `printf("hi %d\n", x);` | C needs a format string and matching codes |
| `read(*, *) x` | `scanf("%lf", &x);` | C needs `&` and the right code (`%lf`!) |
| arrays start at 1 | arrays start at **0** | `a(1)` in Fortran is `a[0]` in C |
| `select case (x)` | `switch (x)` | C: no ranges, needs `break`, works on ints/chars |
| `do i = 1, 10` | `for (i = 1; i <= 10; i++)` | three parts, semicolons |
| `mod(a, b)` | `a % b` | same idea |
| `a ** b` | `pow(a, b)` | C has no `**` operator |
| `a // b` (strings) | `strcat(dest, src)` | C strings are char arrays |
| `==` for strings | `strcmp(a, b) == 0` | Fortran compares strings with `==`; C cannot |

## 6. What Comes Next

You now know variables, math, input/output, decisions, loops, arrays,
functions and strings. Natural next steps:

- `for` loops over files, and reading from files with `fopen` / `fscanf`
- **pointers** (`&` and `*`) — the one big idea C keeps for later, and
  the reason `scanf` needs the `&`
- `struct` — your own data shapes
- dynamic memory with `malloc` / `free`
- bigger projects — like the screensaver experiments in `projects/`
  at the repository root

But first: go play with the guessing game. Add a difficulty setting.
Limit the guesses. Print the secret number at the end. Break something,
then fix it. That is the whole secret of learning to program.
# C Beginner Level

> From "I can write a calculator" to "I can build a tiny dungeon."
> You finished the noob level, so you know variables, loops, arrays,
> functions and strings. Now come the ideas that make C what it is:
> **pointers** (addresses of memory), **structs** (your own types),
> **dynamic memory** (size decided at run time), **files** (data that
> survives a restart) and **recursion** (a function that calls itself).
> Same deal as last time: read the lesson, run the program, change it,
> break it, fix it.

---

## 0. Setup

If you finished the noob level you already have everything: `gcc`, and
the habit of compiling with warnings on.

```text
gcc 01_pointers.c -o pointers -Wall -Wextra
./pointers
```

Two small differences from the noob level:

1. Some programs take **command-line arguments** — extra words after
   the program name. `main` receives them as `argc` (how many) and
   `argv` (the words themselves):

   ```text
   ./word_counter poem.txt
   ```

   `argv[0]` is always the program's own name, `argv[1]` is the first
   argument, and so on. See Project A for the full picture.

2. The files-lesson and several projects read and write **real files**
   on disk. Run them wherever you like — just remember where the file
   appears, and that it is created next to the program's *working
   directory*, not next to the program itself.

---

## 1. The Lessons

| # | File | You will learn |
|---|------|----------------|
| 01 | `lessons/01_pointers.c` | Addresses, `&` and `*` |
| 02 | `lessons/02_pointers_arrays.c` | Arrays are pointers (deep down) |
| 03 | `lessons/03_pointers_functions.c` | Passing variables by reference |
| 04 | `lessons/04_structs.c` | Bundling data: structs |
| 05 | `lessons/05_structs_pointers.c` | Pointers to structs, the `->` arrow |
| 06 | `lessons/06_typedef_enum.c` | Naming types and named constants |
| 07 | `lessons/07_memory.c` | Dynamic memory: `malloc` / `free` |
| 08 | `lessons/08_strings_deep.c` | Strings, now that you know pointers |
| 09 | `lessons/09_files.c` | Working with files |
| 10 | `lessons/10_recursion.c` | A function that calls itself |

### Lesson 01 — Pointers

**Goals:** understand addresses, and why `scanf` has needed `&` all along.

```c
#include <stdio.h>

int main(void)
{
    int number = 42;
    int *ptr;              /* ptr is a pointer to an int */

    ptr = &number;         /* &number = the ADDRESS of number */

    printf("number   = %d\n", number);                 /* 42      */
    printf("&number  = %p\n", (void *)&number);        /* 0x...   */
    printf("ptr      = %p\n", (void *)ptr);            /* same    */
    printf("*ptr     = %d\n", *ptr);                   /* 42      */

    *ptr = 99;             /* write through the pointer */
    printf("number is now %d\n", number);              /* 99      */

    return 0;
}
```

- Every variable lives somewhere in memory. `&variable` gives you its
  **address**; a pointer is a variable that *stores* an address.
- `*pointer` follows the pointer back to the variable — reading it or
  writing through it. This is called **dereferencing**.
- `%p` prints an address. The `(void *)` cast is just politeness for
  `printf`.
- **This is why `scanf` needs `&x`**: `scanf` is a function, and a
  function can only change a caller's variable through a pointer. You
  have been using pointers since the noob level without knowing it!

**Exercise:** declare a `double` and a `char`, point at them, print
their values through the pointers, then change them through the
pointers. What happens if you print `*ptr` before assigning `ptr`?

### Lesson 02 — Pointers and Arrays

**Goals:** discover that an array's name *is* a pointer to its first
element.

```c
#include <stdio.h>

int main(void)
{
    int numbers[5] = {10, 20, 30, 40, 50};
    int *p = numbers;        /* points at numbers[0] */
    int *walk;
    int i;

    printf("numbers[0] = %d\n", numbers[0]);   /* 10 */
    printf("*p         = %d\n", *p);           /* 10 */
    printf("*(p + 2)   = %d\n", *(p + 2));     /* 30 */
    printf("p[2]       = %d\n", p[2]);         /* 30 */

    printf("Pointer walk: ");
    for (walk = numbers; walk < numbers + 5; walk++) {
        printf("%d ", *walk);
    }
    printf("\n");

    printf("Index walk:   ");
    for (i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("&numbers[2] == numbers + 2 : %d (1 = true)\n",
           (&numbers[2] == numbers + 2));

    return 0;
}
```

- The name of an array **decays into a pointer to its first element**.
  Passing an array to a function passes that pointer — nothing is
  copied.
- **Pointer arithmetic** works in units of the pointed-to type:
  `p + 2` moves two *elements* forward, not two bytes.
- `numbers[i]` is sugar for `*(numbers + i)`. That is why `p[2]` works
  on a pointer, and why `&numbers[2] == numbers + 2`.
- The pointer-walk loop and the index loop print the same thing.

**Exercise:** print the addresses of all five elements and watch them
step by exactly `sizeof(int)` bytes. Walk the array *backwards* from
`numbers + 4` to `numbers`.

### Lesson 03 — Pointers and Functions

**Goals:** pass variables **by reference** so a function can really
change them.

```c
#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 5;
    int y = 10;

    printf("Before: x = %d, y = %d\n", x, y);
    swap(&x, &y);          /* pass ADDRESSES */
    printf("After:  x = %d, y = %d\n", x, y);

    int age = 0;
    printf("Enter your age: ");
    scanf("%d", &age);     /* scanf needs the ADDRESS of age */
    printf("You are %d years old.\n", age);

    return 0;
}

void swap(int *a, int *b)
{
    int temp = *a;         /* read what a points to */
    *a = *b;               /* write through the pointer */
    *b = temp;
}
```

- A function that takes `int` gets a **copy**; changing it changes
  nothing outside.
- A function that takes `int *` gets the **address**; writing through
  the pointer changes the caller's variable. This is *pass by
  reference*, and it is the whole secret behind `scanf`.
- `swap(&x, &y)` — the classic. Note that the parameters `a` and `b`
  are copies of the *addresses*, which is exactly what we want.

**Exercise:** write `void add_to(int *target, int amount)` that adds
`amount` to whatever `target` points at. Why does `scanf` *not* need
`&` when the argument is already a pointer (e.g. `scanf("%s", buf)`)?

### Lesson 04 — Structs

**Goals:** bundle several variables into one new type.

```c
#include <stdio.h>
#include <string.h>

struct Student {
    char name[30];
    int  age;
    double score;
};

int main(void)
{
    struct Student ada;          /* one student */
    struct Student class[3];     /* an ARRAY of students */
    struct Student copy;
    int i;
    double sum = 0.0;

    strcpy(ada.name, "Ada");
    ada.age = 36;
    ada.score = 98.5;
    printf("%s is %d years old, score %.1f\n",
           ada.name, ada.age, ada.score);

    strcpy(class[0].name, "Alan");
    class[0].age = 41;
    class[0].score = 91.0;

    strcpy(class[1].name, "Grace");
    class[1].age = 45;
    class[1].score = 97.0;

    strcpy(class[2].name, "Linus");
    class[2].age = 52;
    class[2].score = 88.5;

    for (i = 0; i < 3; i++) {
        sum += class[i].score;
    }
    printf("Average score of the class: %.2f\n", sum / 3.0);

    copy = ada;
    printf("Copy of ada: %s\n", copy.name);

    return 0;
}
```

- `struct Student { ... };` defines a new type that groups fields.
- Fields are accessed with a **dot**: `ada.age`.
- Structs work everywhere variables work: arrays of structs, structs
  inside structs, and (next lesson) pointers to structs.
- **Structs copy with a plain `=`** — all fields at once. (This is one
  of the few things C does for you automatically.)
- Strings inside structs are still char arrays: `strcpy` them, never
  assign with `=`.

**Exercise:** add a `grade` (char) field to `struct Student`. Write a
loop that finds the *youngest* student. Can a struct contain a field
that is itself a struct? Try it.

### Lesson 05 — Structs and Pointers

**Goals:** point at structs, and meet the `->` arrow.

```c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

void print_point(struct Point p)     /* by VALUE: a copy */
{
    printf("(%d, %d)\n", p.x, p.y);
}

void move_point(struct Point *p, int dx, int dy)   /* by POINTER */
{
    p->x += dx;      /* p->x is the same as (*p).x */
    p->y += dy;
}

int main(void)
{
    struct Point home = {3, 4};
    struct Point *ptr = &home;

    printf("home: ");
    print_point(home);            /* (3, 4) */

    printf("ptr->x = %d, ptr->y = %d\n", ptr->x, ptr->y);

    move_point(&home, 10, 20);    /* pass the ADDRESS */
    printf("after move: ");
    print_point(home);            /* (13, 24) */

    printf("(*ptr).x = %d\n", (*ptr).x);

    return 0;
}
```

- `struct Point *p` — a pointer to a struct; `&home` gives you one.
- `p->x` is shorthand for `(*p).x`: dereference first, then take the
  field. You will type `->` constantly from here on.
- Passing a struct **by value** copies the whole struct into the
  function; passing **by pointer** passes just the address — cheaper,
  and it lets the function change the original (Lesson 03 applied to
  structs).

**Exercise:** add a `void reset_point(struct Point *p)` that sets both
fields to 0. Make a function that *returns* a struct: `struct Point
make_point(int x, int y)`.

### Lesson 06 — typedef and enum

**Goals:** name your constants and shorten your type names.

```c
#include <stdio.h>

enum Day { MON, TUE, WED, THU, FRI, SAT, SUN };

typedef struct {
    int hours;
    int minutes;
} Time;

int main(void)
{
    enum Day today = WED;
    enum Day d;

    printf("WED = %d (enums are just numbers)\n", WED);

    switch (today) {
        case MON:
            printf("Mondays...\n");
            break;
        case FRI:
            printf("Finally Friday!\n");
            break;
        case SAT:
        case SUN:
            printf("Weekend!\n");
            break;
        default:
            printf("A working day.\n");
    }

    printf("All days:");
    for (d = MON; d <= SUN; d++) {
        printf(" %d", d);
    }
    printf("\n");

    Time now;
    now.hours = 14;
    now.minutes = 30;
    printf("Time: %02d:%02d\n", now.hours, now.minutes);

    return 0;
}
```

- `enum Day { MON, ... }` creates named constants; `MON` is 0, `TUE`
  is 1, and so on. Under the hood they are plain ints — that is why
  you can loop over them and `switch` on them.
- enums turn magic numbers into words: `today = WED` reads better than
  `today = 2`.
- `typedef struct { ... } Time;` gives the struct a short name, so you
  write `Time now;` instead of `struct Time now;`.

**Exercise:** define an enum for the months. Give `enum Day` a
`typedef` too and rewrite the program to use the short name. What
happens if you add a new day in the *middle* of the enum? (Answer:
every following value shifts — that is why you should not rely on the
numbers.)

### Lesson 07 — Dynamic Memory

**Goals:** decide the size of things *while the program runs*.

```c
#include <stdio.h>
#include <stdlib.h>      /* malloc, free */

int main(void)
{
    int fixed[10];
    printf("A fixed array of 10 ints uses %zu bytes (size known at compile time).\n",
           sizeof(fixed));

    int n;
    int i;

    printf("How many numbers? ");
    scanf("%d", &n);

    int *numbers = malloc((size_t)n * sizeof(int));
    if (numbers == NULL) {
        printf("Out of memory!\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        numbers[i] = i * i;
    }
    for (i = 0; i < n; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    free(numbers);

    return 0;
}
```

- `malloc(n * sizeof(int))` asks the OS for enough bytes to hold `n`
  ints and returns a pointer to the first one. `n` can be anything the
  user typed — that is the whole point.
- **Always check for `NULL`.** `malloc` returns `NULL` when it fails.
- From the pointer on, it behaves exactly like an array: `numbers[i]`.
- **Every `malloc` needs exactly one `free`.** Forget it and your
  program *leaks* memory — it quietly eats more and more RAM.
- So far your arrays lived on the *stack* (fixed, automatic).
  `malloc`'d memory lives on the *heap* (dynamic, yours to manage).
  The heap is where big and long-lived data lives.

**Exercise:** read a list of numbers into a `malloc`'d array and print
them in reverse. What happens if the user types a negative `n`? (The
`(size_t)` cast turns it into a huge number — `malloc` fails, and your
`NULL` check catches it. That is the check earning its keep.)

### Lesson 08 — Strings, Deep

**Goals:** strings through the eyes of a pointer-person.

```c
#include <stdio.h>
#include <string.h>      /* strlen */

int main(void)
{
    char *greeting = "Hello";            /* read-only text */
    char buffer[32] = "Hello";           /* writable copy */
    char names[3][20] = {"Ada", "Grace", "Linus"};
    char *p;
    int i;

    buffer[0] = 'J';
    printf("%s (writable)\n", buffer);

    printf("%zu letters in \"%s\"\n", strlen(greeting), greeting);

    for (i = 0; i < 3; i++) {
        printf("name %d: %s (%zu letters)\n",
               i, names[i], strlen(names[i]));
    }

    printf("Letter walk: ");
    for (p = buffer; *p != '\0'; p++) {
        printf("[%c] ", *p);
    }
    printf("\n");

    return 0;
}
```

- Two ways to make a string:
  - `char *greeting = "Hello";` — points into **read-only** memory.
    Reading is fine; writing (`greeting[0] = 'J'`) is a crash waiting
    to happen.
  - `char buffer[32] = "Hello";` — copies the text into **your own
    writable** array.
- `strlen` takes a `char *` — any string, either kind.
- `char names[3][20]` is an array of strings: three rows, each up to
  19 letters plus `'\0'`.
- Walking a string with a pointer is the same walk you did over ints in
  Lesson 02 — stop at `'\0'`.

**Exercise:** write a `void to_upper(char *s)` that uppercases a string
in place by walking it with a pointer. What happens if you pass
`greeting` (the read-only one) to it?

### Lesson 09 — Files

**Goals:** save data to disk and read it back.

```c
#include <stdio.h>

int main(void)
{
    char line[100];

    FILE *out = fopen("output.txt", "w");
    if (out == NULL) {
        printf("Could not open output.txt for writing.\n");
        return 1;
    }
    fprintf(out, "Hello, file!\n");
    fprintf(out, "2 + 2 = %d\n", 2 + 2);
    fclose(out);
    printf("Wrote output.txt\n");

    FILE *in = fopen("output.txt", "r");
    if (in == NULL) {
        printf("Could not open output.txt for reading.\n");
        return 1;
    }

    while (fgets(line, sizeof line, in) != NULL) {
        printf("read: %s", line);   /* fgets keeps the newline */
    }
    fclose(in);

    return 0;
}
```

- `fopen(name, mode)` opens a file and returns a `FILE *` — or `NULL`
  on failure. **Always check.**
- Modes: `"r"` read (file must exist), `"w"` write (creates, or
  **truncates**), `"a"` append (adds to the end).
- `fprintf` is `printf` into a file — same format codes.
- `fgets(line, size, in)` reads one line at a time and returns `NULL`
  at end of file. It keeps the `'\n'`.
- `fclose` flushes and closes. Always close what you open.

**Exercise:** copy this program and make it *append* three more lines
to the file instead of truncating. Write the multiplication table
(noob-level Project D) into a file instead of the screen.

### Lesson 10 — Recursion

**Goals:** a function that calls itself.

```c
#include <stdio.h>

void countdown(int n)
{
    if (n == 0) {                  /* base case: stop */
        printf("Liftoff!\n");
        return;
    }
    printf("%d ", n);
    countdown(n - 1);              /* recursive case */
}

long long factorial(int n)
{
    if (n <= 1) {
        return 1;                  /* base case */
    }
    return n * factorial(n - 1);   /* recursive case */
}

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
```

- **Base case** — a situation so small the answer is known, no
  recursive call. Without it, the function calls itself forever and
  the program crashes with a *stack overflow*.
- **Recursive case** — the problem, shrunk. `countdown(5)` prints 5
  and then does `countdown(4)`, which prints 4 and does `countdown(3)`
  ...
- `factorial(n) = n * factorial(n - 1)` — the mathematical definition
  *is* the program.
- Every call gets its own copy of the parameters on the **call stack**.
  That is what makes recursion work, and what overflows when the base
  case is missing.

**Exercise:** write `int sum_to(int n)` (sum 1..n) recursively. Print
`fibonacci(30)` — notice how it slows down? Count how many calls it
makes. (That slowness is a hint that recursion is not always the best
tool — a loop would be instant.)

---

## 2. The Projects

Now put the pieces together. Same rule as always: try to write each
one yourself before reading the solution.

### Project A — word counter (`projects/word_counter.c`)

A mini `wc`: counts lines, words and characters in a text file. Also
your first program with **command-line arguments**.

```c
#include <stdio.h>
#include <ctype.h>       /* isspace */

int main(int argc, char *argv[])
{
    FILE *file;
    int ch;
    int lines = 0;
    int words = 0;
    int chars = 0;
    int in_word = 0;

    if (argc != 2) {
        printf("Usage: word_counter <filename>\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        chars++;

        if (ch == '\n') {
            lines++;
        }

        if (isspace(ch)) {
            in_word = 0;              /* a space ends the word */
        } else if (!in_word) {
            in_word = 1;              /* first letter of a new word */
            words++;
        }
    }

    fclose(file);

    printf("%d lines, %d words, %d characters\n", lines, words, chars);
    return 0;
}
```

- `argc` = number of words on the command line; `argv[i]` = the words.
  `argv[0]` is the program's own name, so `argc` is always at least 1.
- `fgetc` reads one character; `EOF` signals the end of the file.
- The `in_word` trick: a word starts when a non-space follows a space
  (or the start of the file). Try it on a file with lots of punctuation
  — the count is surprisingly close to what you expect.

**Lessons used:** 07, 08, 09. New: `argc`/`argv`, `fgetc`.

### Project B — bank account (`projects/bank_account.c`)

A menu-driven savings account: deposit, withdraw, check balance. One
struct holds the data, `switch` picks the action, and a loop keeps the
menu alive. Note the `ask_int`/`ask_double` helpers — they check
scanf's return value so typing garbage cannot hang the menu (a lesson
we learned the hard way in the noob-level guessing game).

```c
#include <stdio.h>

struct Account {
    double balance;
    int    transactions;
};

int ask_int(int *value)
{
    if (scanf("%d", value) != 1) {
        scanf("%*s");            /* discard the bad word */
        return 0;
    }
    return 1;
}

int ask_double(double *value)
{
    if (scanf("%lf", value) != 1) {
        scanf("%*s");
        return 0;
    }
    return 1;
}

void show_menu(void)
{
    printf("\n=== Bank Account ===\n");
    printf("1. Deposit\n");
    printf("2. Withdraw\n");
    printf("3. Check balance\n");
    printf("4. Quit\n");
    printf("Your choice: ");
}

int main(void)
{
    struct Account account = {0.0, 0};
    int choice;
    double amount;

    do {
        show_menu();
        if (!ask_int(&choice)) {
            printf("Please type a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Amount to deposit: ");
                if (!ask_double(&amount)) {
                    printf("Please type a number.\n");
                    break;
                }
                account.balance += amount;
                account.transactions++;
                printf("Deposited %.2f\n", amount);
                break;

            case 2:
                printf("Amount to withdraw: ");
                if (!ask_double(&amount)) {
                    printf("Please type a number.\n");
                    break;
                }
                if (amount > account.balance) {
                    printf("Not enough money!\n");
                } else {
                    account.balance -= amount;
                    account.transactions++;
                    printf("Withdrew %.2f\n", amount);
                }
                break;

            case 3:
                printf("Balance: %.2f (%d transactions)\n",
                       account.balance, account.transactions);
                break;

            case 4:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Try 1-4.\n");
        }
    } while (choice != 4);

    return 0;
}
```

**Lessons used:** 04, 05, 06, 07. New: `ask_int`/`ask_double`.

### Project C — student records (`projects/student_records.c`)

Reads students (name + score) into an **array of structs**, prints
them as a table, plus the average and the best score.

```c
#include <stdio.h>

#define MAX_STUDENTS 100
#define NAME_LEN 30

struct Student {
    char name[NAME_LEN];
    double score;
};

int main(void)
{
    struct Student students[MAX_STUDENTS];
    int count;
    int i;
    double sum = 0.0;
    int best = 0;

    printf("How many students? ");
    scanf("%d", &count);
    if (count < 1 || count > MAX_STUDENTS) {
        printf("Please use a number from 1 to %d.\n", MAX_STUDENTS);
        return 1;
    }

    for (i = 0; i < count; i++) {
        printf("Student %d name: ", i + 1);
        scanf("%29s", students[i].name);
        printf("Student %d score: ", i + 1);
        scanf("%lf", &students[i].score);
    }

    for (i = 0; i < count; i++) {
        sum += students[i].score;
        if (students[i].score > students[best].score) {
            best = i;
        }
    }

    printf("\n%-20s %6s\n", "Name", "Score");
    for (i = 0; i < count; i++) {
        printf("%-20s %6.2f\n", students[i].name, students[i].score);
    }
    printf("Average: %.2f\n", sum / count);
    printf("Best:    %s with %.2f\n", students[best].name,
           students[best].score);

    return 0;
}
```

- `%-20s` left-aligns a name in a 20-wide field; `%6.2f` right-aligns
  a score in 6 columns. Tables without `printf` field widths look
  terrible — with them, they look like this.
- `%29s` caps the name at 29 characters: `scanf` will never overflow
  the 30-byte array. This is your first taste of buffer-safety.
- "Best" is stored as an *index* into the array, not as a copy.

**Lessons used:** 04, 07, 08. New: `%-20s`, `%29s`.

### Project D — Caesar cipher (`projects/caesar_cipher.c`)

The classic Caesar cipher: shift every letter by N positions, then
decrypt it again to prove the round trip.

```c
#include <stdio.h>
#include <ctype.h>       /* isalpha, isupper */
#include <string.h>      /* strcspn */

char shift_char(char c, int shift)
{
    if (isalpha((unsigned char)c)) {
        char base = isupper((unsigned char)c) ? 'A' : 'a';
        int pos = (c - base + shift) % 26;
        if (pos < 0) {
            pos += 26;
        }
        return (char)(pos + base);
    }
    return c;
}

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
    fgets(message, sizeof message, stdin);
    printf("Shift (e.g. 3): ");
    scanf("%d", &shift);

    message[strcspn(message, "\n")] = '\0';

    shift_string(message, shift);
    printf("Encrypted: %s\n", message);

    shift_string(message, -shift);
    printf("Decrypted: %s\n", message);

    return 0;
}
```

- `(c - base + shift) % 26` maps each letter to 0..25, shifts it, and
  wraps around the alphabet with modulo.
- Decryption needs *negative* shifts; the `if (pos < 0) pos += 26`
  handles the wrap in the other direction.
- `fgets` keeps the whole line, spaces included — but it also keeps
  the trailing newline. `strcspn(message, "\n")` finds that newline so
  you can chop it off. (Yes, it is a weird name. It means "string
  complement span".)

**Lessons used:** 08, 10. New: `isalpha`, `isupper`, `fgets`,
`strcspn`.

### Project E — file copier (`projects/file_copier.c`)

Copies a file byte by byte. Uses binary mode (`"rb"`/`"wb"`) so it
works for *any* file — on Windows, text mode would quietly corrupt
newlines in images or archives.

```c
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

    while ((ch = fgetc(in)) != EOF) {
        fputc(ch, out);
    }

    fclose(in);
    fclose(out);
    printf("Copied %s -> %s\n", argv[1], argv[2]);

    return 0;
}
```

**Lessons used:** 09. New: `fgetc`/`fputc`, binary mode.

### Project F — todo list (`projects/todo_list.c`)

A dynamic task list: the list **grows** with `realloc` as you add
tasks — the size is no longer fixed at compile time. This is dynamic
memory doing real work.

```c
#include <stdio.h>
#include <stdlib.h>      /* realloc, free */

#define TASK_LEN 80

struct Task {
    char text[TASK_LEN];
    int  done;
};

int ask_int(int *value)
{
    if (scanf("%d", value) != 1) {
        scanf("%*s");
        return 0;
    }
    return 1;
}

int main(void)
{
    struct Task *tasks = NULL;
    int count = 0;
    int choice;
    int i;

    while (1) {
        printf("\n=== Todo List (%d tasks) ===\n", count);
        printf("1. Add task\n");
        printf("2. Mark task done\n");
        printf("3. Print tasks\n");
        printf("4. Quit\n");
        printf("Your choice: ");
        if (!ask_int(&choice)) {
            printf("Please type a number.\n");
            continue;
        }

        switch (choice) {
            case 1: {
                struct Task *bigger = realloc(
                    tasks, (size_t)(count + 1) * sizeof(struct Task));
                if (bigger == NULL) {
                    printf("Out of memory!\n");
                    break;
                }
                tasks = bigger;
                count++;

                printf("Task text: ");
                scanf(" %79[^\n]", tasks[count - 1].text);
                tasks[count - 1].done = 0;
                break;
            }
            case 2:
                printf("Which task (1-%d)? ", count);
                if (!ask_int(&i)) {
                    printf("Please type a number.\n");
                    break;
                }
                if (i >= 1 && i <= count) {
                    tasks[i - 1].done = 1;
                    printf("Task %d marked done.\n", i);
                } else {
                    printf("No such task.\n");
                }
                break;
            case 3:
                for (i = 0; i < count; i++) {
                    printf("%d. [%c] %s\n", i + 1,
                           tasks[i].done ? 'X' : ' ',
                           tasks[i].text);
                }
                if (count == 0) {
                    printf("(no tasks yet)\n");
                }
                break;
            case 4:
                free(tasks);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try 1-4.\n");
        }
    }
}
```

- `realloc(old_ptr, new_size)` grows the memory *and moves it if it
  has to*. Assign the result to a *temporary* (`bigger`) first: if it
  returns `NULL`, your old data is still alive.
- `scanf(" %79[^\n]", ...)` reads a whole line of text, spaces
  included (`%s` would stop at the first space). The leading space
  skips the leftover newline.
- Every task is a struct; the whole pile lives on the heap; `free`
  gives it all back when you quit.

**Lessons used:** 04, 05, 06, 07. New: `realloc`, `%[^\n]`, `ask_int`.

### Project G — phone book (`projects/phone_book.c`)

A contact book that **survives a restart**: structs for the contacts,
`FILE` I/O for saving and loading.

```c
#include <stdio.h>
#include <string.h>      /* strcmp */

#define MAX_CONTACTS 100
#define NAME_LEN 30
#define PHONE_LEN 20

struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
};

int ask_int(int *value)
{
    if (scanf("%d", value) != 1) {
        scanf("%*s");
        return 0;
    }
    return 1;
}

void save_contacts(const struct Contact *book, int count)
{
    FILE *f = fopen("contacts.txt", "w");
    int i;

    if (f == NULL) {
        printf("Could not save contacts!\n");
        return;
    }
    for (i = 0; i < count; i++) {
        fprintf(f, "%s %s\n", book[i].name, book[i].phone);
    }
    fclose(f);
}

int load_contacts(struct Contact *book)
{
    FILE *f = fopen("contacts.txt", "r");
    int count = 0;

    if (f == NULL) {
        return 0;      /* no file yet: start with an empty book */
    }
    while (count < MAX_CONTACTS &&
           fscanf(f, "%29s %19s",
                  book[count].name, book[count].phone) == 2) {
        count++;
    }
    fclose(f);
    return count;
}

int main(void)
{
    struct Contact book[MAX_CONTACTS];
    int count = load_contacts(book);
    int choice;
    int i;

    printf("Contact book loaded: %d contacts\n", count);

    while (1) {
        printf("\n=== Phone Book ===\n");
        printf("1. Add contact\n");
        printf("2. List contacts\n");
        printf("3. Find by name\n");
        printf("4. Quit (saves)\n");
        printf("Your choice: ");
        if (!ask_int(&choice)) {
            printf("Please type a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                if (count >= MAX_CONTACTS) {
                    printf("Book is full!\n");
                    break;
                }
                printf("Name: ");
                scanf(" %29s", book[count].name);
                printf("Phone: ");
                scanf(" %19s", book[count].phone);
                count++;
                printf("Added.\n");
                break;

            case 2:
                for (i = 0; i < count; i++) {
                    printf("%2d. %-20s %s\n", i + 1,
                           book[i].name, book[i].phone);
                }
                if (count == 0) {
                    printf("(empty)\n");
                }
                break;

            case 3: {
                char search[NAME_LEN];
                int found = 0;
                printf("Name to find: ");
                scanf(" %29s", search);
                for (i = 0; i < count; i++) {
                    if (strcmp(book[i].name, search) == 0) {
                        printf("%s -> %s\n", book[i].name, book[i].phone);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No contact named %s\n", search);
                }
                break;
            }

            case 4:
                save_contacts(book, count);
                printf("Saved %d contacts. Goodbye!\n", count);
                return 0;

            default:
                printf("Invalid choice. Try 1-4.\n");
        }
    }
}
```

- The file format is one contact per line: `Ada 555-1234`. `fprintf`
  writes it, `fscanf` reads it back — the same `%s` codes as `scanf`,
  but from a file.
- `fscanf(...) == 2` — it returns how many fields it read; 2 means a
  full contact. The loop stops at the end of the file.
- `const struct Contact *book` — the `const` promises the function
  will only *read* the contacts, never modify them. It is free
  documentation for anyone reading your code.

**Lessons used:** 04, 05, 06, 09. New: file persistence, `fscanf`
into struct fields, `const` parameters.

### Project H — text adventure (`projects/text_adventure.c`)

The boss fight of the beginner level: a tiny dungeon crawler. The
world is a set of rooms; each room is a **struct that knows its exits,
and every exit is a pointer to another room**. Moving is just
following a pointer: `current = current->to[i];` — your first graph.

```c
#include <stdio.h>
#include <string.h>      /* strcmp */

#define MAX_DESC 100
#define MAX_EXITS 4

struct Room {
    char description[MAX_DESC];
    char *exits[MAX_EXITS];        /* names of the exits, e.g. "east" */
    struct Room *to[MAX_EXITS];    /* where each exit leads */
    int exit_count;
    int has_key;
};

void connect(struct Room *a, struct Room *b, const char *direction)
{
    a->exits[a->exit_count] = (char *)direction;
    a->to[a->exit_count] = b;
    a->exit_count++;
}

int main(void)
{
    struct Room hall   = {"You are in a dark hall.",       {0}, {0}, 0, 0};
    struct Room kitchen = {"You are in a kitchen. It smells old.", {0}, {0}, 0, 0};
    struct Room garden = {"You are in a garden full of flowers.", {0}, {0}, 0, 1};
    struct Room cellar = {"You are in a damp cellar.",     {0}, {0}, 0, 0};
    struct Room door   = {"A bright door! You escaped!",   {0}, {0}, 0, 0};

    connect(&hall, &kitchen, "east");
    connect(&kitchen, &hall, "west");
    connect(&kitchen, &garden, "north");
    connect(&garden, &kitchen, "south");
    connect(&kitchen, &cellar, "south");
    connect(&cellar, &kitchen, "north");
    connect(&garden, &door, "east");     /* the exit is behind the key */

    struct Room *current = &hall;
    int has_key = 0;
    char command[50];
    int i;

    printf("=== Tiny Dungeon ===\n");
    printf("Commands: look, take, north, south, east, west, quit\n");
    printf("Find the key, then reach the bright door.\n");

    while (1) {
        printf("\n%s\n", current->description);
        printf("Exits:");
        for (i = 0; i < current->exit_count; i++) {
            printf(" %s", current->exits[i]);
        }
        printf("\n> ");

        if (scanf("%49s", command) != 1) {
            break;                /* end of input */
        }

        if (strcmp(command, "quit") == 0) {
            printf("Goodbye!\n");
            break;
        } else if (strcmp(command, "look") == 0) {
            if (current->has_key) {
                printf("A shiny KEY lies here. (Type: take)\n");
            } else {
                printf("Nothing special here.\n");
            }
        } else if (strcmp(command, "take") == 0) {
            if (current->has_key) {
                has_key = 1;
                current->has_key = 0;
                printf("You took the key.\n");
            } else {
                printf("Nothing to take here.\n");
            }
        } else {
            int found = 0;
            for (i = 0; i < current->exit_count; i++) {
                if (strcmp(command, current->exits[i]) == 0) {
                    if (current->to[i] == &door && !has_key) {
                        printf("The door is locked. You need a key.\n");
                        found = 1;
                    } else {
                        current = current->to[i];   /* follow the pointer */
                        found = 1;
                    }
                    break;
                }
            }
            if (!found) {
                printf("You cannot go that way.\n");
            }
        }

        if (current == &door) {
            printf("\n%s\n", current->description);
            printf("YOU WIN! You escaped the dungeon.\n");
            break;
        }
    }

    return 0;
}
```

A sample session:

```text
=== Tiny Dungeon ===
Commands: look, take, north, south, east, west, quit
Find the key, then reach the bright door.

You are in a dark hall.
Exits: east
> east

You are in a kitchen. It smells old.
Exits: west north south
> north

You are in a garden full of flowers.
Exits: south east
> take
You took the key.

You are in a garden full of flowers.
Exits: south east
> east

A bright door! You escaped!
YOU WIN! You escaped the dungeon.
```

If you can explain to a friend how the rooms are connected, you have
officially finished the beginner level.

**Lessons used:** 04, 05, 06, 08, 09. New: a tiny graph made of
pointers.

---

## 3. Build Everything

`build.ps1` compiles every lesson and every project into the `bin/`
folder — same script as the noob level:

```text
powershell -ExecutionPolicy Bypass -File .\beginner-level\build.ps1
```

The compiled `.exe` files are not stored in git (see the repository
root `.gitignore`) — anyone can regenerate them from the source in one
command.

---

## 4. Quick Reference

| You want to... | Write |
|----------------|-------|
| Take the address of a variable | `int *p = &x;` |
| Read/write what a pointer points to | `*p` |
| Print an address | `printf("%p\n", (void *)p);` |
| Pointer to an array's first element | `int *p = arr;` |
| Move a pointer to the next element | `p++` (or `p + i`) |
| Pass a variable so a function can change it | `f(&x);` with `void f(int *p)` |
| Define a struct | `struct Point { int x; int y; };` |
| Field of a struct | `p.x` (by value) / `p->x` (by pointer) |
| Named constants | `enum Color { RED, GREEN, BLUE };` |
| Shorten a type name | `typedef struct { ... } Time;` |
| Ask the OS for memory | `int *a = malloc(n * sizeof(int));` |
| Give it back | `free(a);` |
| Open a file | `FILE *f = fopen("f.txt", "r");` |
| Write to / read from a file | `fprintf(f, ...)` / `fscanf(f, ...)` / `fgets(line, size, f)` |
| Close a file | `fclose(f);` |
| Recursion | base case first, then `return f(n - 1);` |
| Command-line arguments | `int main(int argc, char *argv[])` |

## 5. What Comes Next

You now know the three big C ideas — pointers, structs and dynamic
memory — plus files and recursion. The natural next steps:

- **Linked lists** — structs that point to each other, the foundation
  of every data structure (your dungeon rooms were already a graph in
  disguise)
- **Multi-file programs** — splitting code into `.h` headers and
  several `.c` files, and a proper build setup
- **Function pointers** — storing a function's address in a variable
  (yes, functions have addresses too)
- **`const` everywhere** — the discipline that keeps big programs sane
- Reading the screensaver projects in `projects/` at the repository
  root — with pointers and structs under your belt, they are no longer
  mysterious

But first: go play with the dungeon. Add more rooms, add an inventory,
make the key spawn in a random room, or add a monster that chases you.
Break something, then fix it. That is the whole secret of learning to
program.

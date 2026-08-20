/* 05_structs_pointers.c
 * Pointers to structs, and the -> arrow.
 *
 * A struct can be big (many fields). Copying it into a function
 * BY VALUE copies everything. Passing a POINTER passes just the
 * address -- faster, and it lets the function change the original.
 *
 *     p->x   is the same as   (*p).x
 *
 * Compile:
 *     gcc 05_structs_pointers.c -o structs_pointers
 * Run:
 *     ./structs_pointers
 *
 * Lesson 05 - README.md:
 *     struct Point *p = &home;   -> pointer to a struct
 *     p->x                       -> the arrow: dereference + field
 *     (*p).x                     -> the long way, same thing
 *     print_point(home)          -> by VALUE: gets a copy
 *     move_point(&home, 10, 20)  -> by POINTER: changes the original
 */

#include <stdio.h>

struct Point {
    int x;
    int y;
};

/* by VALUE: gets a copy, cannot change the caller's point */
void print_point(struct Point p)
{
    printf("(%d, %d)\n", p.x, p.y);
}

/* by POINTER: can change the original */
void move_point(struct Point *p, int dx, int dy)
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

    /* the arrow: pointer to struct, then field */
    printf("ptr->x = %d, ptr->y = %d\n", ptr->x, ptr->y);

    move_point(&home, 10, 20);    /* pass the ADDRESS */
    printf("after move: ");
    print_point(home);            /* (13, 24) */

    /* arrow is sugar for (*ptr). */
    printf("(*ptr).x = %d\n", (*ptr).x);

    return 0;
}

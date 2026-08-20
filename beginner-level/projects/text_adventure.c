/* text_adventure.c
 * The boss fight of the beginner level: a tiny dungeon crawler.
 *
 * The world is a set of rooms. Each room is a STRUCT that knows its
 * exits, and every exit is a POINTER to another room. Moving is
 * just following a pointer:  current = current->to[i];
 *
 * Goal: find the key (in the garden), then reach the bright door.
 *
 * Compile:
 *     gcc text_adventure.c -o text_adventure
 * Run:
 *     ./text_adventure
 *
 * Lessons used: 04, 05, 06, 08, 09. New: structs connected by
 * pointers -- your first tiny "graph".
 */

#include <stdio.h>
#include <string.h>      /* strcmp */

#define MAX_DESC 100
#define MAX_EXITS 4

struct Room {
    char description[MAX_DESC];
    char *exits[MAX_EXITS];        /* names of the exits, e.g. "east" */
    struct Room *to[MAX_EXITS];    /* where each exit leads */
    int exit_count;
    int has_key;                   /* 1 = the key lies here */
};

/* connect room a to room b through "direction" */
void connect(struct Room *a, struct Room *b, const char *direction)
{
    a->exits[a->exit_count] = (char *)direction;
    a->to[a->exit_count] = b;
    a->exit_count++;
}

int main(void)
{
    /* --- build the world ------------------------------------------- */
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
            /* try to walk in that direction */
            int found = 0;
            for (i = 0; i < current->exit_count; i++) {
                if (strcmp(command, current->exits[i]) == 0) {
                    if (current->to[i] == &door && !has_key) {
                        printf("The door is locked. You need a key.\n");
                        found = 1;   /* we DID find the exit; it is locked */
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

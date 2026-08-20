/* todo_list.c
 * A dynamic task list: add, mark done, print tasks.
 * The list GROWS with realloc as you add tasks -- the size is no
 * longer fixed at compile time. This is dynamic memory in action.
 *
 * Compile:
 *     gcc todo_list.c -o todo_list
 * Run:
 *     ./todo_list
 *
 * Lessons used: 04, 05, 06, 07. New: realloc, scanf %[^\n], ask_int.
 */

#include <stdio.h>
#include <stdlib.h>      /* realloc, free */

#define TASK_LEN 80

struct Task {
    char text[TASK_LEN];
    int  done;
};

/* read a whole number; returns 1 on success, 0 on garbage.
 * Garbage input would otherwise leave the variable unchanged and
 * the menu would loop forever -- check scanf's return value! */
int ask_int(int *value)
{
    if (scanf("%d", value) != 1) {
        scanf("%*s");            /* discard the bad word */
        return 0;
    }
    return 1;
}

int main(void)
{
    struct Task *tasks = NULL;   /* no tasks yet */
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
                /* make room: grow the array by one task.
                 * realloc moves the data if it must. */
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
                /* %[^\n] reads a whole line (up to 79 chars),
                 * spaces included -- %s would stop at the first space */
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
                free(tasks);     /* give the dynamic memory back */
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try 1-4.\n");
        }
    }
}

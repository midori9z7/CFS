/* phone_book.c
 * A contact book saved to a file: add, list, find.
 * Structs hold the contacts; FILE I/O makes them survive a restart.
 *
 * The file format is one contact per line:
 *     Ada 555-1234
 *     Grace 555-5678
 *
 * Compile:
 *     gcc phone_book.c -o phone_book
 * Run:
 *     ./phone_book
 *
 * Lessons used: 04, 05, 06, 09. New: fscanf into struct fields,
 * saving and loading, ask_int.
 */

#include <stdio.h>
#include <string.h>      /* strcmp */

#define MAX_CONTACTS 100
#define NAME_LEN 30
#define PHONE_LEN 20

struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
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

/* write every contact into contacts.txt */
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

/* read contacts back; returns how many were loaded */
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

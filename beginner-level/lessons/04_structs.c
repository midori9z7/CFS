/* 04_structs.c
 * Structs: bundling several variables into ONE new type.
 *
 * A struct groups related data. You can then declare variables,
 * arrays and (later) pointers of that type. Think of it as
 * designing your own variable type.
 *
 * Compile:
 *     gcc 04_structs.c -o structs
 * Run:
 *     ./structs
 *
 * Lesson 04 - README.md:
 *     struct Student { ... };       -> define a new type
 *     struct Student ada;           -> declare a variable of it
 *     ada.name / ada.age            -> access fields with a dot
 *     struct Student class[3];      -> an array of structs
 *     copy = ada;                   -> structs copy with plain =
 *     strcpy(ada.name, "Ada")       -> strings inside structs
 */

#include <stdio.h>
#include <string.h>

/* a struct bundles several variables into one new type */
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

    /* fill the first student, field by field */
    strcpy(ada.name, "Ada");
    ada.age = 36;
    ada.score = 98.5;
    printf("%s is %d years old, score %.1f\n",
           ada.name, ada.age, ada.score);

    /* fill an array of structs */
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

    /* structs can be copied with a simple = */
    copy = ada;
    printf("Copy of ada: %s\n", copy.name);

    return 0;
}

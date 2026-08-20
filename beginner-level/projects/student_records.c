/* student_records.c
 * Reads students (name + score) into an ARRAY OF STRUCTS,
 * then prints them in a table, plus the average and the best score.
 *
 * Compile:
 *     gcc student_records.c -o student_records
 * Run:
 *     ./student_records
 *
 * Lessons used: 04, 07, 08. New: %-20s (left-aligned field), %29s.
 */

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
        scanf("%29s", students[i].name);      /* %29s: never overflow */
        printf("Student %d score: ", i + 1);
        scanf("%lf", &students[i].score);
    }

    for (i = 0; i < count; i++) {
        sum += students[i].score;
        if (students[i].score > students[best].score) {
            best = i;                         /* remember the index */
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

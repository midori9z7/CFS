/* bank_account.c
 * A menu-driven savings account: deposit, withdraw, check balance.
 * One struct holds the account's data; a do-while loop keeps the
 * menu alive until the user quits; switch picks the action.
 *
 * Compile:
 *     gcc bank_account.c -o bank_account
 * Run:
 *     ./bank_account
 *
 * Lessons used: 04, 05, 06, 07. New: ask_int/ask_double -- checking
 * scanf's return value so garbage input cannot hang the menu.
 */

#include <stdio.h>

struct Account {
    double balance;
    int    transactions;
};

/* read a whole number; returns 1 on success, 0 on garbage.
 * Garbage input would otherwise leave the variable unchanged and
 * the menu would loop forever -- checking scanf's return value
 * (first seen in the Level 1 guessing game) fixes that. */
int ask_int(int *value)
{
    if (scanf("%d", value) != 1) {
        scanf("%*s");            /* discard the bad word */
        return 0;
    }
    return 1;
}

/* read a decimal number; 1 on success, 0 on garbage */
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

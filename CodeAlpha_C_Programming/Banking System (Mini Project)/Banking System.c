#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BankAccount {
    int accountNumber;
    char name[100];   // buffer for full names
    float balance;
};

void deposit(struct BankAccount *acc, float amount) {
    acc->balance += amount;
    printf("Deposited: %.2f\nNew Balance: %.2f\n", amount, acc->balance);
}

void withdraw(struct BankAccount *acc, float amount) {
    if (amount <= acc->balance) {
        acc->balance -= amount;
        printf("Withdrawn: %.2f\nNew Balance: %.2f\n", amount, acc->balance);
    } else {
        printf("Insufficient balance!\n");
    }
}

void balanceEnquiry(struct BankAccount *acc) {
    printf("Account Balance: %.2f\n", acc->balance);
}

// Save or update account in file
void saveAccount(struct BankAccount acc) {
    FILE *fp = fopen("C:\\Users\\Jyoti\\Desktop\\accounts.txt", "r");
    FILE *temp = fopen("C:\\Users\\Jyoti\\Desktop\\temp.txt", "w");

    if (temp == NULL) {
        return; // silent fail
    }

    int found = 0;
    char line[200];

    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            int accountNumber;
            char name[100];
            float balance;

            // Read accountNumber, full name, and balance
            if (sscanf(line, "%d %[^\n] %f", &accountNumber, name, &balance) == 3) {
                if (accountNumber == acc.accountNumber) {
                    fprintf(temp, "%d %s %.2f\n", acc.accountNumber, acc.name, acc.balance);
                    found = 1;
                } else {
                    fprintf(temp, "%d %s %.2f\n", accountNumber, name, balance);
                }
            }
        }
        fclose(fp);
    }

    if (!found) {
        fprintf(temp, "%d %s %.2f\n", acc.accountNumber, acc.name, acc.balance);
    }

    fclose(temp);

    remove("C:\\Users\\Jyoti\\Desktop\\accounts.txt");
    rename("C:\\Users\\Jyoti\\Desktop\\temp.txt",
           "C:\\Users\\Jyoti\\Desktop\\accounts.txt");
}

// Load account by number
int loadAccount(struct BankAccount *acc, int accNo) {
    FILE *fp = fopen("C:\\Users\\Jyoti\\Desktop\\accounts.txt", "r");
    if (fp == NULL) return 0;

    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        int accountNumber;
        char name[100];
        float balance;

        if (sscanf(line, "%d %[^0-9] %f", &accountNumber, name, &balance) == 3) {
            // trim trailing spaces from name
            name[strcspn(name, "\n")] = '\0';
            while (strlen(name) > 0 && name[strlen(name)-1] == ' ')
                name[strlen(name)-1] = '\0';

            if (accountNumber == accNo) {
                acc->accountNumber = accountNumber;
                strcpy(acc->name, name);
                acc->balance = balance;
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}


int main() {
    struct BankAccount account;
    int choice, accNo;
    float amount;

    printf("Enter your account number: ");
    scanf("%d", &accNo);

    if (!loadAccount(&account, accNo)) {
        printf("Account not found. Creating new account.\n");
        account.accountNumber = accNo;

        printf("Enter your name: ");
        getchar(); // clear leftover newline
        fgets(account.name, sizeof(account.name), stdin);
        account.name[strcspn(account.name, "\n")] = '\0'; // remove newline

        account.balance = 0.0;
        saveAccount(account);
    }

    printf("\nWelcome %s (Acc No: %d)\n", account.name, account.accountNumber);

    while (1) {
        printf("\n1. Deposit\n2. Withdraw\n3. Balance Enquiry\n4. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter amount: ");
                scanf("%f", &amount);
                deposit(&account, amount);
                saveAccount(account);
                break;
            case 2:
                printf("Enter amount: ");
                scanf("%f", &amount);
                withdraw(&account, amount);
                saveAccount(account);
                break;
            case 3:
                balanceEnquiry(&account);
                break;
            case 4:
                saveAccount(account);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}

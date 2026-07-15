#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "accounts.txt"

struct BankAccount
{
    int accountNumber;
    int pin;
    char name[100];
    float balance;
};



void removeNewline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

void clearBuffer()
{
    while(getchar()!='\n');
}



int generateAccountNumber()
{
    FILE *fp=fopen(FILE_NAME,"r");

    if(fp==NULL)
        return 1001;

    struct BankAccount acc;
    int lastAcc=1000;

    while(fscanf(fp,"%d|%d|%99[^|]|%f\n",
                 &acc.accountNumber,
                 &acc.pin,
                 acc.name,
                 &acc.balance)==4)
    {
        lastAcc=acc.accountNumber;
    }

    fclose(fp);

    return lastAcc+1;
}



void saveAccount(struct BankAccount acc)
{
    FILE *fp=fopen(FILE_NAME,"a");

    if(fp==NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(fp,"%d|%d|%s|%.2f\n",
            acc.accountNumber,
            acc.pin,
            acc.name,
            acc.balance);

    fclose(fp);
}



void createAccount()
{
    struct BankAccount acc;

    printf("\n========== CREATE ACCOUNT ==========\n");

    acc.accountNumber=generateAccountNumber();

    printf("Account Number : %d\n",acc.accountNumber);

    printf("Enter Full Name : ");
    clearBuffer();
    fgets(acc.name,sizeof(acc.name),stdin);
    removeNewline(acc.name);

    while(1)
    {
        printf("Create 4-digit PIN : ");
        scanf("%d",&acc.pin);

        if(acc.pin>=1000 && acc.pin<=9999)
            break;

        printf("PIN must be exactly 4 digits.\n");
    }

    while(1)
    {
        printf("Initial Deposit : ");

        scanf("%f",&acc.balance);

        if(acc.balance>=0)
            break;

        printf("Invalid amount.\n");
    }

    saveAccount(acc);

    printf("\n====================================\n");
    printf("Account Created Successfully!\n");
    printf("Account Number : %d\n",acc.accountNumber);
    printf("====================================\n");
}



int login(struct BankAccount *acc)
{
    FILE *fp=fopen(FILE_NAME,"r");

    if(fp==NULL)
    {
        printf("\nNo Accounts Found.\n");
        return 0;
    }

    int accNo,pin;

    printf("\n========== LOGIN ==========\n");

    printf("Account Number : ");
    scanf("%d",&accNo);

    printf("PIN : ");
    scanf("%d",&pin);

    while(fscanf(fp,"%d|%d|%99[^|]|%f\n",
                 &acc->accountNumber,
                 &acc->pin,
                 acc->name,
                 &acc->balance)==4)
    {
        if(acc->accountNumber==accNo &&
           acc->pin==pin)
        {
            fclose(fp);

            printf("\n====================================\n");
            printf("Login Successful!\n");
            printf("Welcome %s\n",acc->name);
            printf("====================================\n");

            return 1;
        }
    }

    fclose(fp);

    printf("\nInvalid Account Number or PIN.\n");

    return 0;
}



void accountDetails(struct BankAccount acc)
{
    printf("\n====================================\n");
    printf("        ACCOUNT DETAILS\n");
    printf("====================================\n");

    printf("Account Number : %d\n",acc.accountNumber);
    printf("Name           : %s\n",acc.name);
    printf("Balance        : %.2f\n",acc.balance);

    printf("====================================\n");
}


void updateAccount(struct BankAccount acc)
{
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("File Error!\n");

        if (fp != NULL)
            fclose(fp);

        if (temp != NULL)
            fclose(temp);

        return;
    }

    struct BankAccount data;

    while (fscanf(fp, "%d|%d|%99[^|]|%f\n",
                  &data.accountNumber,
                  &data.pin,
                  data.name,
                  &data.balance) == 4)
    {
        if (data.accountNumber == acc.accountNumber)
        {
            fprintf(temp, "%d|%d|%s|%.2f\n",
                    acc.accountNumber,
                    acc.pin,
                    acc.name,
                    acc.balance);
        }
        else
        {
            fprintf(temp, "%d|%d|%s|%.2f\n",
                    data.accountNumber,
                    data.pin,
                    data.name,
                    data.balance);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
}




void deposit(struct BankAccount *acc)
{
    float amount;

    printf("\nEnter Deposit Amount : ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("Invalid Amount!\n");
        return;
    }

    acc->balance += amount;

    updateAccount(*acc);

    printf("\n====================================\n");
    printf("Deposit Successful!\n");
    printf("Amount Deposited : %.2f\n", amount);
    printf("Current Balance  : %.2f\n", acc->balance);
    printf("====================================\n");
}




void withdraw(struct BankAccount *acc)
{
    float amount;

    printf("\nEnter Withdrawal Amount : ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("Invalid Amount!\n");
        return;
    }

    if (amount > acc->balance)
    {
        printf("\nInsufficient Balance!\n");
        return;
    }

    acc->balance -= amount;

    updateAccount(*acc);

    printf("\n====================================\n");
    printf("Withdrawal Successful!\n");
    printf("Amount Withdrawn : %.2f\n", amount);
    printf("Current Balance  : %.2f\n", acc->balance);
    printf("====================================\n");
}




void balanceEnquiry(struct BankAccount acc)
{
    printf("\n====================================\n");
    printf("        BALANCE ENQUIRY\n");
    printf("====================================\n");

    printf("Account Number : %d\n", acc.accountNumber);
    printf("Account Holder : %s\n", acc.name);
    printf("Available Balance : %.2f\n", acc.balance);

    printf("====================================\n");
}
#define TRANSACTION_FILE "transactions.txt"



void saveTransaction(int accountNumber, char type[], float amount)
{
    FILE *fp = fopen(TRANSACTION_FILE, "a");

    if(fp == NULL)
        return;

    fprintf(fp, "%d|%s|%.2f\n",
            accountNumber,
            type,
            amount);

    fclose(fp);
}



void transferMoney(struct BankAccount *sender)
{
    FILE *fp = fopen(FILE_NAME, "r");

    if(fp == NULL)
    {
        printf("No Accounts Found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");

    if(temp == NULL)
    {
        fclose(fp);
        return;
    }

    int receiverAcc;
    float amount;

    printf("\n========== MONEY TRANSFER ==========\n");

    printf("Receiver Account Number : ");
    scanf("%d",&receiverAcc);

    if(receiverAcc == sender->accountNumber)
    {
        printf("Cannot transfer to your own account.\n");

        fclose(fp);
        fclose(temp);
        remove("temp.txt");

        return;
    }

    printf("Enter Amount : ");
    scanf("%f",&amount);

    if(amount <= 0)
    {
        printf("Invalid Amount.\n");

        fclose(fp);
        fclose(temp);
        remove("temp.txt");

        return;
    }

    if(amount > sender->balance)
    {
        printf("Insufficient Balance.\n");

        fclose(fp);
        fclose(temp);
        remove("temp.txt");

        return;
    }

    struct BankAccount acc;

    int receiverFound = 0;

    sender->balance -= amount;

    while(fscanf(fp,"%d|%d|%99[^|]|%f\n",
                 &acc.accountNumber,
                 &acc.pin,
                 acc.name,
                 &acc.balance)==4)
    {

        if(acc.accountNumber == sender->accountNumber)
        {
            fprintf(temp,"%d|%d|%s|%.2f\n",
                    sender->accountNumber,
                    sender->pin,
                    sender->name,
                    sender->balance);
        }

        else if(acc.accountNumber == receiverAcc)
        {
            acc.balance += amount;

            receiverFound = 1;

            fprintf(temp,"%d|%d|%s|%.2f\n",
                    acc.accountNumber,
                    acc.pin,
                    acc.name,
                    acc.balance);
        }

        else
        {
            fprintf(temp,"%d|%d|%s|%.2f\n",
                    acc.accountNumber,
                    acc.pin,
                    acc.name,
                    acc.balance);
        }
    }

    fclose(fp);
    fclose(temp);

    if(receiverFound)
    {
        remove(FILE_NAME);
        rename("temp.txt",FILE_NAME);

        saveTransaction(sender->accountNumber,"Transfer Sent",amount);
        saveTransaction(receiverAcc,"Transfer Received",amount);

        printf("\nTransfer Successful!\n");
        printf("Transferred : %.2f\n",amount);
        printf("Remaining Balance : %.2f\n",sender->balance);
    }

    else
    {
        sender->balance += amount;

        remove("temp.txt");

        printf("\nReceiver Account Not Found.\n");
    }
}



void transactionHistory(int accountNumber)
{
    FILE *fp=fopen(TRANSACTION_FILE,"r");

    if(fp==NULL)
    {
        printf("\nNo Transaction History Found.\n");
        return;
    }

    int accNo;
    char type[50];
    float amount;

    int found=0;

    printf("\n=========================================\n");
    printf("        TRANSACTION HISTORY\n");
    printf("=========================================\n");

    printf("%-20s %-15s\n","TYPE","AMOUNT");

    printf("-----------------------------------------\n");

    while(fscanf(fp,"%d|%49[^|]|%f\n",
                 &accNo,
                 type,
                 &amount)==3)
    {
        if(accNo==accountNumber)
        {
            printf("%-20s %.2f\n",
                   type,
                   amount);

            found=1;
        }
    }

    if(!found)
        printf("No Transactions Found.\n");

    printf("=========================================\n");

    fclose(fp);
}

void changePIN(struct BankAccount *acc)
{
    int oldPin,newPin;

    printf("\n========== CHANGE PIN ==========\n");

    printf("Enter Current PIN : ");
    scanf("%d",&oldPin);

    if(oldPin!=acc->pin)
    {
        printf("Incorrect Current PIN!\n");
        return;
    }

    while(1)
    {
        printf("Enter New 4-digit PIN : ");
        scanf("%d",&newPin);

        if(newPin>=1000 && newPin<=9999)
            break;

        printf("PIN must be 4 digits.\n");
    }

    acc->pin=newPin;

    updateAccount(*acc);

    printf("\nPIN Changed Successfully!\n");
}


void deleteAccount(struct BankAccount acc)
{
    FILE *fp=fopen(FILE_NAME,"r");
    FILE *temp=fopen("temp.txt","w");

    if(fp==NULL || temp==NULL)
    {
        printf("File Error!\n");
        return;
    }

    struct BankAccount data;

    while(fscanf(fp,"%d|%d|%99[^|]|%f\n",
                 &data.accountNumber,
                 &data.pin,
                 data.name,
                 &data.balance)==4)
    {
        if(data.accountNumber!=acc.accountNumber)
        {
            fprintf(temp,"%d|%d|%s|%.2f\n",
                    data.accountNumber,
                    data.pin,
                    data.name,
                    data.balance);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt",FILE_NAME);

    printf("\n====================================\n");
    printf("Account Deleted Successfully.\n");
    printf("====================================\n");
}


void userMenu(struct BankAccount *acc)
{
    int choice;

    do
    {
        printf("\n====================================\n");
        printf("         BANK DASHBOARD\n");
        printf("====================================\n");

        printf("1. Account Details\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Transfer Money\n");
        printf("6. Transaction History\n");
        printf("7. Change PIN\n");
        printf("8. Delete Account\n");
        printf("9. Logout\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                accountDetails(*acc);
                break;

            case 2:
                deposit(acc);
                saveTransaction(acc->accountNumber,"Deposit",0);
                break;

            case 3:
                withdraw(acc);
                saveTransaction(acc->accountNumber,"Withdraw",0);
                break;

            case 4:
                balanceEnquiry(*acc);
                break;

            case 5:
                transferMoney(acc);
                break;

            case 6:
                transactionHistory(acc->accountNumber);
                break;

            case 7:
                changePIN(acc);
                break;

            case 8:
                deleteAccount(*acc);
                return;

            case 9:
                printf("\nLogged Out Successfully.\n");
                break;

            default:
                printf("\nInvalid Choice.\n");
        }

    }while(choice!=9);
}


int main()
{
    int choice;

    struct BankAccount currentUser;

    do
    {
        printf("\n====================================\n");
        printf("       BANK MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                createAccount();
                break;

            case 2:

                if(login(&currentUser))
                {
                    userMenu(&currentUser);
                }

                break;

            case 3:
                printf("\nThank You For Using Our Banking System!\n");
                break;

            default:
                printf("\nInvalid Choice.\n");
        }

    }while(choice!=3);

    return 0;
}
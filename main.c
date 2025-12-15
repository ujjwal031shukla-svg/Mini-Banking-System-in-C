#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 5
#define FILE_NAME "accounts.dat"

struct Account {
    int account_number;
    char name[50];
    float balance;
};

struct Account accounts[MAX_ACCOUNTS];
int account_count = 0;

void showMenu();
void createAccount();
int findAccount(int acc_no);
void deposit();
void withdraw();
void checkBalance();
void deleteAccount();
void listAccounts();
void loadAccountsFromFile();
void saveAccountToFile(struct Account *acc);
void updateAccountInFile(struct Account *acc);

int main() {
    int choice;

    loadAccountsFromFile(); 

    do {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: deleteAccount(); break;
            case 6: listAccounts(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 7);

    return 0;
}

void showMenu() {
    printf("\n--- Mini Banking System ---\n");
    printf("1. Create Account\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Check Balance\n");
    printf("5. Delete Account\n");
    printf("6. List All Accounts\n");
    printf("7. Exit\n");
}

void loadAccountsFromFile() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if(fp == NULL) return; 

    account_count = 0;
    while(fread(&accounts[account_count], sizeof(struct Account), 1, fp)) {
        account_count++;
        if(account_count >= MAX_ACCOUNTS) break;
    }

    fclose(fp);
}

void saveAccountToFile(struct Account *acc) {
    FILE *fp = fopen(FILE_NAME, "ab"); 
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(acc, sizeof(struct Account), 1, fp);
    fclose(fp);
}

void updateAccountInFile(struct Account *acc) {
    FILE *fp = fopen(FILE_NAME, "rb+"); 
    if(fp == NULL) return;

    struct Account temp;
    while(fread(&temp, sizeof(struct Account), 1, fp)) {
        if(temp.account_number == acc->account_number) {
            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(acc, sizeof(struct Account), 1, fp);
            break;
        }
    }

    fclose(fp);
}

int findAccount(int acc_no) {
    for(int i = 0; i < account_count; i++) {
        if(accounts[i].account_number == acc_no)
            return i;
    }
    return -1;
}

void createAccount() {
    if(account_count >= MAX_ACCOUNTS) {
        printf("Account limit reached.\n");
        return;
    }

    struct Account acc;

    printf("Enter account number: ");
    scanf("%d", &acc.account_number);

    if(findAccount(acc.account_number) != -1) {
        printf("Account already exists!\n");
        return;
    }

    printf("Enter name: ");
    scanf("%49s", acc.name); 

    acc.balance = 0.0;

    accounts[account_count++] = acc;
    saveAccountToFile(&acc);

    printf("Account created successfully!\n");
}

void deposit() {
    int acc_no;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &acc_no);

    int idx = findAccount(acc_no);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if(amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    accounts[idx].balance += amount;
    updateAccountInFile(&accounts[idx]);

    printf("Deposit successful!\n");
}

void withdraw() {
    int acc_no;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &acc_no);

    int idx = findAccount(acc_no);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if(amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    if(amount > accounts[idx].balance) {
        printf("Insufficient balance!\n");
        return;
    }

    accounts[idx].balance -= amount;
    updateAccountInFile(&accounts[idx]);

    printf("Withdrawal successful!\n");
}

void checkBalance() {
    int acc_no;

    printf("Enter account number: ");
    scanf("%d", &acc_no);

    int idx = findAccount(acc_no);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Account Holder: %s\n", accounts[idx].name);
    printf("Current Balance: %.2f\n", accounts[idx].balance);
}

void deleteAccount() {
    int acc_no;
    printf("Enter account number to delete: ");
    scanf("%d", &acc_no);

    int idx = findAccount(acc_no);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }

   
    for(int i = idx; i < account_count - 1; i++) {
        accounts[i] = accounts[i + 1];
    }
    account_count--;

   
    FILE *fp = fopen(FILE_NAME, "wb");
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for(int i = 0; i < account_count; i++) {
        fwrite(&accounts[i], sizeof(struct Account), 1, fp);
    }
    fclose(fp);

    printf("Account deleted successfully!\n");
}


void listAccounts() {
    if(account_count == 0) {
        printf("No accounts available.\n");
        return;
    }

    printf("\n--- All Accounts ---\n");
    for(int i = 0; i < account_count; i++) {
        printf("Account Number: %d, Name: %s, Balance: %.2f\n",
               accounts[i].account_number, accounts[i].name, accounts[i].balance);
    }
}

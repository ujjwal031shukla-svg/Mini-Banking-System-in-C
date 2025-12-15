# Mini-Banking-System-in-C
A console-based banking application in C that allows users to create accounts, deposit, withdraw, transfer funds, and view account details. All data is stored in a binary file with basic authentication.

Mini Banking System in C
**Overview**

This is a console-based Mini Banking System written in C. It allows users to:

Create new bank accounts

Deposit money

Withdraw money

Check account balance

Delete accounts

List all accounts

All account data is stored persistently in a binary file (accounts.dat), so information is retained between program runs.
**
**Features****

Create Account – Add a new account with a unique account number and account holder name.

Deposit – Add money to an existing account.

Withdraw – Withdraw money from an existing account (with balance check).

Check Balance – View the current balance of any account.

Delete Account – Remove an account permanently.

List All Accounts – Display all existing accounts with their balance.

Persistent Storage – Accounts are saved in accounts.dat file.

**How to Run**

Clone the repository:

git clone <your-repo-link>
cd mini-banking-system


Compile the C program:

gcc main.c -o mini_bank


Run the executable:

./mini_bank


Follow the on-screen menu to perform banking operations.

**Example Output**
--- Mini Banking System ---
1. Create Account
2. Deposit
3. Withdraw
4. Check Balance
5. Delete Account
6. List All Accounts
7. Exit

Enter your choice: 1
Enter account number: 1001
Enter name: John
Account created successfully!

Enter your choice: 2
Enter account number: 1001
Enter amount to deposit: 500
Deposit successful!

Enter your choice: 4
Enter account number: 1001
Account Holder: John
Current Balance: 500.00

****Code Structure**
**
main.c – Contains all program logic including functions for account operations.

accounts.dat – Binary file storing all account information.

**Notes**

Maximum 5 accounts supported (configurable via MAX_ACCOUNTS macro).

Account names are limited to 49 characters.

All operations are validated for safety (e.g., no negative deposits/withdrawals).

Future Enhancements

Dynamic memory allocation to support unlimited accounts

Support for account names with spaces

Transaction history per account

Refactor into multiple files (account.h, account.c, main.c) for modularity

**License**

This project is open-source. Feel free to use and modify it.

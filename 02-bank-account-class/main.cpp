// Practical 02 - Classes, Access Specifiers and Member Functions
//
// BankAccount combines data (balance, account number) with behaviour
// (deposit, withdraw). Its data is PRIVATE so no outside code can set the
// balance directly; it can only change through validated public methods.

#include <iostream>
#include <string>

class BankAccount {
private:
    // PRIVATE: hidden from main() and other classes. Protecting these keeps
    // the balance consistent - it can only change through validated methods.
    std::string accountNumber;
    double      balance;

public:
    // PUBLIC: the interface that the rest of the program is allowed to use.

    // Constructor initialises the object and validates the opening balance.
    BankAccount(const std::string& number, double openingBalance)
        : accountNumber(number), balance(0.0) {
        if (openingBalance < 0) {
            std::cout << "  [warning] Negative opening balance rejected, starting at 0.\n";
        } else {
            balance = openingBalance;
        }
    }

    // Deposit only accepts positive amounts.
    void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "  [error] Deposit amount must be positive.\n";
            return;
        }
        balance += amount;
    }

    // Withdraw returns true on success, false if the request is invalid.
    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "  [error] Withdrawal amount must be positive.\n";
            return false;
        }
        if (amount > balance) {
            std::cout << "  [error] Insufficient balance for withdrawal of " << amount << ".\n";
            return false;
        }
        balance -= amount;
        return true;
    }

    // Read-only accessors (const means they do not modify the object).
    double getBalance() const { return balance; }
    const std::string& getAccountNumber() const { return accountNumber; }

    void display() const {
        std::cout << "Account " << accountNumber << " | Balance: " << balance << "\n";
    }
};

int main() {
    // Two objects of the same class, each with its own private data.
    BankAccount savings("SAV-1001", 5000.00);
    BankAccount current("CUR-2002", 1200.50);

    std::cout << "=== Initial state ===\n";
    savings.display();
    current.display();

    std::cout << "\n=== Savings operations ===\n";
    savings.deposit(1500.00);
    savings.withdraw(2000.00);
    savings.deposit(-50);            // invalid, rejected
    savings.display();

    std::cout << "\n=== Current operations ===\n";
    current.withdraw(5000.00);       // invalid, rejected
    current.withdraw(200.25);
    current.display();

    // Private members cannot be accessed from here. Uncommenting the next
    // line causes a compile error, which demonstrates the access specifier:
    // savings.balance = 1000000;

    return 0;
}

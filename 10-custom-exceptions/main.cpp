// Practical 10 - Custom Exceptions: Banking Transactions
//
// Exception hierarchy:
//   std::runtime_error
//     └── BankError            (base for all banking errors)
//           ├── InvalidAmount      (amount is zero or negative)
//           └── InsufficientFunds  (withdrawal exceeds the balance)
//
// Each failed transaction is checked BEFORE the balance changes, so a failed
// transaction never leaves the balance incorrect.

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

class BankError : public std::runtime_error {
public:
    explicit BankError(const std::string& message) : std::runtime_error(message) {}
};

class InvalidAmount : public BankError {
public:
    explicit InvalidAmount(double amount)
        : BankError("Invalid amount " + std::to_string(amount) + ": must be greater than zero") {}
};

class InsufficientFunds : public BankError {
public:
    InsufficientFunds(double requested, double available)
        : BankError("Insufficient funds: requested " + std::to_string(requested) +
                    ", available " + std::to_string(available)) {}
};

class BankAccount {
public:
    BankAccount(std::string owner, double balance)
        : owner_(std::move(owner)), balance_(balance) {}

    void deposit(double amount) {
        if (amount <= 0) throw InvalidAmount(amount);   // validate first
        balance_ += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) throw InvalidAmount(amount);            // validate first
        if (amount > balance_) throw InsufficientFunds(amount, balance_);
        balance_ -= amount;                                       // only changes on success
    }

    // Transfers money only if BOTH steps are valid.
    void transferTo(BankAccount& target, double amount) {
        withdraw(amount);            // throws before any change if invalid
        target.deposit(amount);
    }

    double balance() const { return balance_; }
    const std::string& owner() const { return owner_; }

private:
    std::string owner_;
    double      balance_;
};

// Runs one transaction and reports the result. Each exception type is caught separately.
void attempt(const std::string& description, void (*operation)()) {
    std::cout << "- " << description << "\n";
    try {
        operation();
        std::cout << "  SUCCESS\n";
    } catch (const InvalidAmount& ex) {
        std::cout << "  FAILED (invalid amount): " << ex.what() << "\n";
    } catch (const InsufficientFunds& ex) {
        std::cout << "  FAILED (insufficient funds): " << ex.what() << "\n";
    } catch (const BankError& ex) {
        std::cout << "  FAILED (other bank error): " << ex.what() << "\n";
    }
}

BankAccount alice("Alice", 1000.00);
BankAccount bob("Bob", 250.00);

void printBalances() {
    std::cout << std::fixed << std::setprecision(2)
              << "  Balances -> " << alice.owner() << ": " << alice.balance()
              << " | " << bob.owner() << ": " << bob.balance() << "\n";
}

void aliceDeposit200()      { alice.deposit(200.00); }
void aliceWithdraw300()     { alice.withdraw(300.00); }
void aliceWithdraw5000()    { alice.withdraw(5000.00); }
void aliceWithdrawNeg()     { alice.withdraw(-50.00); }
void aliceToBob400()        { alice.transferTo(bob, 400.00); }
void aliceToBob9000()       { alice.transferTo(bob, 9000.00); }
void bobDepositZero()       { bob.deposit(0.0); }

int main() {
    std::cout << "=== Starting balances ===\n";
    printBalances();

    std::cout << "\n=== Successful transactions ===\n";
    attempt("Alice deposits 200", aliceDeposit200);
    attempt("Alice withdraws 300", aliceWithdraw300);
    attempt("Alice transfers 400 to Bob", aliceToBob400);
    printBalances();

    std::cout << "\n=== Failed transactions ===\n";
    attempt("Alice withdraws 5000 (too much)", aliceWithdraw5000);
    attempt("Alice withdraws -50 (negative)", aliceWithdrawNeg);
    attempt("Alice transfers 9000 to Bob", aliceToBob9000);
    attempt("Bob deposits 0", bobDepositZero);
    printBalances();

    std::cout << "\nBalances are unchanged by the failed transactions above.\n";
    std::cout << "\nWhat each exception means:\n"
                 "  InvalidAmount     - the request itself is malformed (amount <= 0).\n"
                 "  InsufficientFunds - the request is valid but the account cannot cover it.\n";
    return 0;
}

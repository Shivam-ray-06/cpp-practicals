// Practical 01 - C++ Fundamentals
// Demonstrates: data types, constants, variables, arithmetic / relational /
// logical operators, and input/output with cin and cout.

#include <iostream>
#include <string>

int main() {
    // Constants: values that must not change after initialisation
    const int    MAX_MARKS  = 100;
    const int    PASS_MARK  = 40;
    const double BONUS_RATE = 0.05;   // 5 % bonus

    // Variables of suitable types
    std::string name;
    int         age;
    int         marks1;
    int         marks2;

    std::cout << "=== Student Marks Calculator ===\n";
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::cout << "Enter your age: ";
    std::cin >> age;

    std::cout << "Enter marks in subject 1 (out of " << MAX_MARKS << "): ";
    std::cin >> marks1;

    std::cout << "Enter marks in subject 2 (out of " << MAX_MARKS << "): ";
    std::cin >> marks2;

    // Arithmetic operators
    int    total      = marks1 + marks2;
    int    difference = marks1 - marks2;
    int    product    = marks1 * marks2;
    int    remainder  = total % 2;                  // modulus: 0 = total is even
    double average    = total / 2.0;                // floating-point division
    double percentage = (total * 100.0) / (2 * MAX_MARKS);
    double bonus      = average * BONUS_RATE;

    // Relational operators
    bool hasHigherFirstSubject = marks1 > marks2;
    bool isPassingAverage      = average >= PASS_MARK;
    bool isEqualMarks          = marks1 == marks2;

    // Logical operators
    bool isAdult      = age >= 18;
    bool passedBoth   = marks1 >= PASS_MARK && marks2 >= PASS_MARK;
    bool eligible     = isAdult && (passedBoth || isPassingAverage);
    bool needsReview  = !passedBoth;

    // Output
    std::cout << "\n--- Results for " << name << " ---\n";
    std::cout << "Total marks       : " << total << "\n";
    std::cout << "Difference        : " << difference << "\n";
    std::cout << "Product           : " << product << "\n";
    std::cout << "Remainder of total: " << remainder << (remainder == 0 ? " (even)" : " (odd)") << "\n";
    std::cout << "Average           : " << average << "\n";
    std::cout << "Percentage        : " << percentage << " %\n";
    std::cout << "Bonus (5% of avg) : " << bonus << "\n";
    std::cout << std::boolalpha;
    std::cout << "Subject 1 higher  : " << hasHigherFirstSubject << "\n";
    std::cout << "Average passing   : " << isPassingAverage << "\n";
    std::cout << "Equal marks       : " << isEqualMarks << "\n";
    std::cout << "Eligible          : " << eligible << "\n";
    std::cout << "Needs review      : " << needsReview << "\n";

    return 0;
}

// Practical 07 - Compile-Time Polymorphism: Function and Operator Overloading
//
// Overloading is resolved at COMPILE time from the parameter types.
//   - Function overloading: same name, different parameter lists.
//   - Operator overloading: giving an operator (+, <<) a meaning for a class.
// Runtime polymorphism (virtual functions) is different - see Practical 06.

#include <iostream>
#include <string>

// ---- Function overloading ----
int add(int a, int b) {
    std::cout << "  [add(int,int)] ";
    return a + b;
}

double add(double a, double b) {
    std::cout << "  [add(double,double)] ";
    return a + b;
}

// Three arguments: a different parameter list again.
int add(int a, int b, int c) {
    std::cout << "  [add(int,int,int)] ";
    return a + b + c;
}

// ---- Operator overloading: ComplexNumber ----
class ComplexNumber {
    double real_;
    double imag_;

public:
    ComplexNumber(double real = 0.0, double imag = 0.0) : real_(real), imag_(imag) {}

    // Overloaded '+' as a member function: combines two complex numbers.
    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real_ + other.real_, imag_ + other.imag_);
    }

    // Overloaded '==' so tests can compare results.
    bool operator==(const ComplexNumber& other) const {
        return real_ == other.real_ && imag_ == other.imag_;
    }

    // Overloaded '<<' as a non-member so it can take std::cout on the left.
    friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& c) {
        os << c.real_;
        if (c.imag_ >= 0) os << " + " << c.imag_ << "i";
        else              os << " - " << -c.imag_ << "i";
        return os;
    }
};

int main() {
    std::cout << "=== Function overloading (same name, different parameters) ===\n";
    std::cout << add(2, 3) << "\n";
    std::cout << add(2.5, 3.75) << "\n";
    std::cout << add(1, 2, 3) << "\n";

    std::cout << "\n=== Operator overloading with ComplexNumber ===\n";
    ComplexNumber z1(3.0, 4.0);     // 3 + 4i
    ComplexNumber z2(1.5, -2.0);    // 1.5 - 2i
    ComplexNumber sum = z1 + z2;    // uses our overloaded '+'

    std::cout << "z1       = " << z1 << "\n";
    std::cout << "z2       = " << z2 << "\n";
    std::cout << "z1 + z2  = " << sum << "\n";

    std::cout << "\n=== Test cases ===\n" << std::boolalpha;
    std::cout << "(3+4i) + (1.5-2i) == 4.5+2i ? "
              << (sum == ComplexNumber(4.5, 2.0)) << "\n";
    std::cout << "Zero identity: z1 + 0 == z1 ? "
              << ((z1 + ComplexNumber()) == z1) << "\n";

    std::cout << "\n=== Why operator overloading is useful ===\n"
                 "Expressions like 'z1 + z2' read like the maths they represent, so\n"
                 "code that uses ComplexNumber stays as clear as code that uses int or double.\n";
    return 0;
}

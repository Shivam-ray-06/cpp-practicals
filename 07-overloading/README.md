# Practical 07 - Compile-Time Polymorphism: Overloading

## Question
Demonstrate function overloading and operator overloading using a Complex Number class.

## Aim
Understand how C++ chooses functions at compile time from parameter lists and operator definitions.

## Parts
1. **Function overloading** - `add(int, int)`, `add(double, double)` and `add(int, int, int)`.
   The compiler picks the version from the argument types and count.
2. **Operator overloading** - `ComplexNumber` has `real` and `imag` parts, and `operator+`
   adds two numbers component-wise.
3. **Test cases** - `(3+4i) + (1.5-2i) == 4.5+2i`, and adding zero leaves a number unchanged.

## Three related ideas
| Idea | Decided at | Example |
|---|---|---|
| Function overloading | compile time | `add(int,int)` vs `add(double,double)` |
| Operator overloading | compile time | `z1 + z2` calls `ComplexNumber::operator+` |
| Runtime polymorphism | run time | `Shape&` calling `area()` (practical 06) |

## Why the operator overload is useful
`z1 + z2` reads like the mathematics it represents, so code using `ComplexNumber`
is as clear as code using `int` or `double`.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o overload
./overload
```
Output: `sample_output.txt`.

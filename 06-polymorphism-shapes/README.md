# Practical 06 - Runtime Polymorphism and Abstract Classes

## Question
Create an abstract `Shape` class and implement `Circle`, `Rectangle` and `Triangle`
with an `area()` function.

## Aim
Show how a base-class interface calls the correct derived-class function at runtime.

## Design
```
Shape  (abstract: virtual double area() const = 0;  virtual ~Shape())
  |-- Circle     (area = pi * r * r)
  |-- Rectangle  (area = width * height)
  |-- Triangle   (area = base * height / 2)
```

- `= 0` makes `area()` pure virtual, so `Shape` is abstract and `Shape s;` does not compile.
- `virtual` makes the call resolve at runtime through a `Shape&` or `Shape*`.
- The virtual destructor makes `std::unique_ptr<Shape>` delete derived objects safely.
- Invalid dimensions (for example a negative radius) throw `std::invalid_argument`,
  and the program catches it and reports it.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o shapes
./shapes
```
Output: `sample_output.txt`.

# cpp-practicals

C++ Programming Practical Manual (RSSOFTTECS) - completed practicals 01 to 11.

Each practical is in its own folder and is self-contained: it has one `main.cpp`,
a `README.md` (purpose, compile and run steps, notes), and `sample_output.txt`
(the real output captured from the program).

| Folder | Practical | Key ideas |
|---|---|---|
| `01-fundamentals/` | GitHub Setup and C++ Fundamentals | data types, `const`, operators, `cin`/`cout` |
| `02-bank-account-class/` | Classes, Access Specifiers and Member Functions | `private` vs `public`, constructors, validation |
| `03-rule-of-five/` | Constructors and Rule of Five | deep copy, move semantics, destructor, Valgrind |
| `04-smart-pointers/` | RAII and Smart Pointers | `unique_ptr`, `shared_ptr`, Valgrind |
| `05-inheritance/` | Single and Multilevel Inheritance | Person -> Student -> GraduateStudent |
| `06-polymorphism-shapes/` | Runtime Polymorphism and Abstract Classes | pure virtual `area()`, virtual destructor |
| `07-overloading/` | Compile-Time Polymorphism | function overloading, `operator+` on `ComplexNumber` |
| `08-singleton-config/` | Singleton Design Pattern | one `AppConfig` instance, trade-offs |
| `09-generic-stack/` | Generic Stack Using Templates | `template<typename T>`, `int`/`float`/`std::string` |
| `10-custom-exceptions/` | Custom Exceptions: Banking | exception hierarchy derived from `std::runtime_error` |
| `11-csv-file-io/` | CSV Student Records Using File I/O | `fstream`, CSV format, `seekg/tellg/seekp/tellp` |

The mini project (practical 12) is not part of this repository yet.

## Build any practical

```bash
cd <folder>
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app
./app
```

Requires a C++17 compiler (g++ 9+ or clang++ 10+). Valgrind is optional and only
used for practicals 03 and 04 (Linux): `valgrind --leak-check=full ./app`.

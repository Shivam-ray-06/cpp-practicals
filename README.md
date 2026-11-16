# Object Oriented Programming (OOP) Practical Repository

**Student Name:** Shivam Ray  
**Branch:** B.Tech (Artificial Intelligence & Data Science) — 2nd Year  
**Course:** Object Oriented Programming with C++  
**Curriculum Manual:** RSSOFTTECS Practical Manual (12 Practicals)

---

## 📚 Practical Index

| No. | Directory | Practical Title | Key Concepts & Technologies |
|---|---|---|---|
| **01** | [`01-fundamentals/`](./01-fundamentals/) & [`practical01.cpp`](./practical01.cpp) | GitHub Setup and C++ Fundamentals | Data types, `const`, operators, I/O streams |
| **02** | [`02-bank-account-class/`](./02-bank-account-class/) | Classes, Access Specifiers & Methods | `private` vs `public`, constructors, validation |
| **03** | [`03-rule-of-five/`](./03-rule-of-five/) | Constructors and Rule of Five | Deep copy, move semantics, destructors |
| **04** | [`04-smart-pointers/`](./04-smart-pointers/) | RAII and Smart Pointers | `std::unique_ptr`, `std::shared_ptr`, memory safety |
| **05** | [`05-inheritance/`](./05-inheritance/) | Single and Multilevel Inheritance | Person → Student → GraduateStudent hierarchy |
| **06** | [`06-polymorphism-shapes/`](./06-polymorphism-shapes/) | Runtime Polymorphism & Abstract Classes | Pure virtual functions, dynamic dispatch, vtables |
| **07** | [`07-overloading/`](./07-overloading/) | Compile-Time Polymorphism | Function overloading, `operator+` on `ComplexNumber` |
| **08** | [`08-singleton-config/`](./08-singleton-config/) | Singleton Design Pattern | Meyer's singleton, shared system configuration |
| **09** | [`09-generic-stack/`](./09-generic-stack/) | Generic Stack Using Templates | `template <typename T>`, stack operations |
| **10** | [`10-custom-exceptions/`](./10-custom-exceptions/) | Custom Exceptions: Banking | Exception hierarchy derived from `std::runtime_error` |
| **11** | [`11-csv-file-io/`](./11-csv-file-io/) | CSV Student Records Using File I/O | `fstream`, structured CSV, `seekg/tellg/seekp/tellp` |
| **12** | [**`12-library-management-system/`**](./12-library-management-system/) | **Mini Project: Console Library System** | **Full application: OOP, STL, Exceptions, CSV, Polymorphism** |

---

## 🛠️ Build and Execution Instructions

### Prerequisites
- Modern C++ Compiler: Clang++ (macOS) or GCC / G++ (Linux/Windows) with C++17 support.
- Git.

### Compiling Any Practical
Each practical is self-contained. To compile and run any practical:
```bash
cd <practical-folder>
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o app
./app
```

### Running Practical 12 (Mini Project)
```bash
cd 12-library-management-system
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o library_app
./library_app            # Interactive menu
./library_app --demo     # Automated normal + error demonstration
```

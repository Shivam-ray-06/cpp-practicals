# Object Oriented Programming (OOP) Lab — Practical 01

**Course:** B.Tech (Artificial Intelligence & Data Science) - 2nd Year  
**Subject:** Object Oriented Programming (C++)  
**Practical 01:** GitHub Setup and C++ Fundamentals

---

## 🎯 Aim
To practise basic C++ syntax (data types, constants, variables, operators, and input/output) and learn how to track code changes using Git and GitHub.

---

## 📋 Problem Statement / Question
Create a GitHub repository and write a C++ program that demonstrates data types, constants, variables, operators, and input/output.

---

## 💡 Concepts Demonstrated
1. **Data Types & Variables:**
   - `int` (`rollNumber`)
   - `float` (`marks1`, `marks2`, `marks3`, `totalMarks`, `percentage`)
   - `char` (`grade`)
   - `bool` (`isPassed`)
   - `std::string` (`studentName`)
2. **Constants:**
   - `const int MAX_MARKS = 100;`
   - `const float PASS_PERCENTAGE = 40.0f;`
3. **Operators:**
   - **Arithmetic:** `+` (summation), `/` (division), `*` (multiplication)
   - **Relational:** `>=`, `<`, `==`
   - **Logical:** `&&` (Logical AND) for multi-condition evaluation
   - **Ternary Operator:** `?:` for conditional status display
4. **Input & Output:**
   - `std::cin` / `getline` for user input
   - `std::cout` with stream manipulators (`std::fixed`, `std::setprecision`) for formatted console output.

---

## ⚙️ How to Compile and Run

### Prerequisites
- GCC / G++ (`g++`) or Clang (`clang++`) installed.
- Git installed.

### Steps
1. **Clone the repository:**
   ```bash
   git clone https://github.com/Shivam-ray-06/cpp-practicals.git
   cd cpp-practicals
   ```

2. **Compile the program:**
   ```bash
   g++ -std=c++17 practical01.cpp -o practical01
   ```
   *(or on macOS using clang++: `clang++ -std=c++17 practical01.cpp -o practical01`)*

3. **Run the executable:**
   ```bash
   ./practical01
   ```

---

## 📝 Sample Input and Output

### Input
```text
Enter Student Name: Shivam Ray
Enter Roll Number: 101
Enter marks for Subject 1 (out of 100): 88.5
Enter marks for Subject 2 (out of 100): 92.0
Enter marks for Subject 3 (out of 100): 85.5
```

### Output
```text
========================================
  Student Performance Evaluation System  
========================================
Enter Student Name: Shivam Ray
Enter Roll Number: 101
Enter marks for Subject 1 (out of 100): 88.5
Enter marks for Subject 2 (out of 100): 92.0
Enter marks for Subject 3 (out of 100): 85.5

----------------------------------------
             REPORT CARD               
----------------------------------------
Student Name : Shivam Ray
Roll Number  : 101
Subject 1    : 88.50 / 100
Subject 2    : 92.00 / 100
Subject 3    : 85.50 / 100
Total Marks  : 266.00 / 300
Percentage   : 88.67%
Grade        : A
Result       : PASSED
----------------------------------------
```

---

## 🔬 Result / Observation
The basic fundamentals of C++ including standard I/O streams (`cin`, `cout`), primitive data types, constants, arithmetic, relational, and logical operators were implemented successfully. The source code was tracked, committed, and pushed to the remote GitHub repository using Git version control.

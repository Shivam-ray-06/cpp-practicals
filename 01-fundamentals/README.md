# Practical 01 - GitHub Setup and C++ Fundamentals

## Question
Write a C++ program that demonstrates data types, constants, variables, operators
and input/output.

## Aim
Practise basic C++ syntax and learn how to track code changes using Git and GitHub.

## What the program covers
| Topic | Where in `main.cpp` |
|---|---|
| Constants (`const int MAX_MARKS`, `PASS_MARK`, `BONUS_RATE`) | top of `main()` |
| Data types (`std::string`, `int`, `double`, `bool`) | variable declarations |
| Arithmetic (`+ - * / %`) | "Arithmetic operators" block |
| Relational (`> >= ==`) | "Relational operators" block |
| Logical (`&& \|\| !`) | "Logical operators" block |
| Input / output (`std::cin`, `std::getline`, `std::cout`) | prompts and results |

## Compile
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o fundamentals
```

## Run
```bash
./fundamentals
```

## Sample input and output
- Input is in `sample_input.txt` (name, age, marks in subject 1, marks in subject 2).
- The full transcript (with inputs shown after each prompt) is in `sample_output.txt`.

Test with the saved input:
```bash
./fundamentals < sample_input.txt
```

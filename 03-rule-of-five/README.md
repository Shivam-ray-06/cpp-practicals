# Practical 03 - Constructors and Rule of Five

## Question
Implement a class that demonstrates default, parameterized, copy and move constructors,
and the Rule of Five.

## Aim
Understand object creation, copying, moving and safe management of an owned resource.

## Class
`IntArray` owns a dynamically allocated `int` array (`new[]` / `delete[]`).

| Member | Role |
|---|---|
| default constructor | creates an empty array |
| parameterized constructor | creates an array of `n` elements |
| copy constructor | **deep copy** - allocates new memory and copies the values |
| copy assignment | deep copy, with a self-assignment check |
| move constructor | steals the pointer and leaves the source empty (`size 0`) |
| move assignment | releases the current memory, then steals the source's pointer |
| destructor | releases the owned memory |

Rule of Five = destructor, copy constructor, copy assignment, move constructor, move assignment.
The default and parameterized constructors are extra constructor forms.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -g main.cpp -o rule5
./rule5
```

## Memory check (Valgrind)
```bash
valgrind --leak-check=full ./rule5
```
Result: `All heap blocks were freed -- no leaks are possible` and
`ERROR SUMMARY: 0 errors`. Full log: `valgrind_output.txt`.
Program output: `sample_output.txt`.

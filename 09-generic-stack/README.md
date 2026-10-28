# Practical 09 - Generic Stack Using Templates

## Question
Write a generic Stack class using templates and test it with `int`, `float` and `std::string`.

## Aim
Understand generic programming: one class working with several data types.

## Design
- `template <typename T> class Stack` uses `std::vector<T>` internally.
- Operations: `push`, `pop`, `top`, `empty`, `size`.
- `pop()` and `top()` on an empty stack throw `std::underflow_error`, which the caller catches.

## Why a template?
Without templates, three separate classes (`IntStack`, `FloatStack`, `StringStack`)
would be needed. The template is written once, and the compiler generates each version
when it is used (`Stack<int>`, `Stack<float>`, `Stack<std::string>`).

## Test cases
| Case | Expected | Result |
|---|---|---|
| New stack is empty | `empty() == true` | pass |
| Push 3 values, then `top()` | last value pushed | pass |
| Pop until empty | values come out in LIFO order | pass |
| Pop from empty stack | error caught, message shown | pass |

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o stack
./stack
```
Output: `sample_output.txt`.

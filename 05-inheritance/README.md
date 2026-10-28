# Practical 05 - Single and Multilevel Inheritance

## Question
Implement a university-management example: `Person -> Student -> GraduateStudent`.

## Aim
Understand base and derived classes and how data and behaviour are reused.

## Class diagram

```
Person                      (base: name, age)
  |
  +-- Student               (single inheritance: adds studentId, course)
        |
        +-- GraduateStudent (multilevel inheritance: adds researchTopic, supervisor)
```

## Inherited members available to each class
| Class | Own members | Inherited members it can use |
|---|---|---|
| `Person` | `name`, `age`, `displayPerson()` | none |
| `Student` | `studentId`, `course`, `displayStudent()` | `name`, `age`, `displayPerson()` |
| `GraduateStudent` | `researchTopic`, `supervisor`, `displayGraduate()` | everything in `Student` and `Person` |

Constructors run base-first (`[Person ctor]`, then `[Student ctor]`, then
`[GraduateStudent ctor]`), as shown in the output. The base class has a virtual
destructor, so deleting through a `Person*` is safe.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o university
./university
```
Output: `sample_output.txt`.

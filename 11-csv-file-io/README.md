# Practical 11 - CSV Student Records Using File I/O

## Question
Implement a CSV reader/writer using `fstream` to store and retrieve student records.
Demonstrate `seekg()`, `seekp()`, `tellg()` and `tellp()`.

## Aim
Practise persistent storage, structured records, file modes and file-position operations.

## CSV format (decided and documented)
```
id,name,marks
101,Asha Nair,87.5
102,Dev Patel,72
103,Priya Menon,94.25
```
- First line is a header.
- One record per line, fields separated by commas.
- Fields are written as text. Raw struct bytes are **not** used, because padding,
  byte order and `std::string` layout are not portable.

## What the program does
| Part | Action | Output file |
|---|---|---|
| 1 | Write 3 records (checks that the file opened and the write succeeded) | `students.csv` |
| 2 | Read records back and display them in a table | - |
| 3 | Missing file handled with a clear error | - |
| 4 | Malformed lines (missing field, non-numeric ID, marks outside 0-100) skipped with warnings | `students_bad.csv` |
| 5 | Position functions on a separate demo file | `position_demo.txt` |

## File-position functions
| Function | Stream | Meaning |
|---|---|---|
| `tellg()` / `seekg()` | input (get) | where the next read starts / moves the read position |
| `tellp()` / `seekp()` | output (put) | where the next write goes / moves the write position |

Part 5 output: `seekp(3)` moves the write position to 3, and writing `BBB` there
overwrites the file, which becomes `AAABBBAAAA`. The read position is moved separately
with `seekg(3)`, and `seekg(0, std::ios::end)` finds the file length (10 bytes).

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o csv_records
./csv_records
```
The program creates the CSV files in the folder it is run from.
Output: `sample_output.txt`. Generated files are included as evidence.

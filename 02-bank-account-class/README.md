# Practical 02 - Classes, Access Specifiers and Member Functions

## Question
Design and implement a class for a real-world entity (here: `BankAccount`).

## Aim
Understand how classes combine data and behaviour, and how access specifiers protect data.

## Design
| Member | Access | Why |
|---|---|---|
| `accountNumber`, `balance` | `private` | Outside code must not change the balance directly; only validated methods may. |
| constructor, `deposit`, `withdraw`, `getBalance`, `display` | `public` | The interface the rest of the program uses. |
| `getBalance()`, `getAccountNumber()`, `display()` | `public const` | Read-only: they promise not to modify the object. |

Validation rules:
- Opening balance cannot be negative (rejected, starts at 0).
- Deposit and withdrawal amounts must be positive.
- Withdrawal cannot exceed the balance.

The class comments in `main.cpp` explain each private and public member.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o bank
./bank
```

## Sample output
See `sample_output.txt`. It shows two objects (`SAV-1001`, `CUR-2002`) with
successful and rejected operations.

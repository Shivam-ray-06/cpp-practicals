# Practical 10 - Custom Exceptions: Banking Transaction

## Question
Create a custom exception hierarchy and throw/catch specific exceptions in a banking transaction program.

## Aim
Report application-specific failures and handle each one in a controlled way.

## Exception hierarchy
```
std::runtime_error
  |
  +-- BankError            (base for all banking errors)
        |-- InvalidAmount      amount is zero or negative (the request is malformed)
        +-- InsufficientFunds  amount is valid but exceeds the balance
```

## Rules implemented
- `withdraw` and `transfer` throw `InvalidAmount` for a non-positive amount.
- They throw `InsufficientFunds` when the amount is larger than the balance.
- Each exception type is caught separately and gives its own message.
- Balance is checked before it is changed, so a failed transaction changes nothing.
  The output confirms the balances are unchanged after the failed transactions.

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o bank_exceptions
./bank_exceptions
```
Output (successful and failed transactions): `sample_output.txt`.

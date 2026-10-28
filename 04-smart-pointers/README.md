# Practical 04 - RAII and Smart Pointers

## Question
Replace suitable raw `new`/`delete` usage with `std::unique_ptr` and `std::shared_ptr`.
Compare behaviour and check for memory leaks.

## Aim
Learn how RAII ties resource lifetime to object lifetime.

## What the program shows
| Part | Smart pointer | Ownership |
|---|---|---|
| A | `std::unique_ptr<Resource>` | one owner; `std::move` transfers it, and the old owner becomes null |
| B | `std::shared_ptr<Logger>` | several services share one logger; freed when the last owner goes |
| C | `std::vector<std::unique_ptr<int>>` | 10,000 allocations freed automatically over many iterations |

## Comparison: raw pointer vs unique_ptr vs shared_ptr

| Aspect | Raw pointer (`new`/`delete`) | `unique_ptr` | `shared_ptr` |
|---|---|---|---|
| Who frees the memory | programmer, manually | automatically, when the one owner is destroyed | automatically, when the last owner is destroyed |
| Ownership | unclear | exactly one owner | shared (reference-counted) |
| Copyable | yes (causes double-delete bugs) | no, only movable | yes (increments the count) |
| Overhead | none | none (practically) | control block + atomic reference count |
| Exception-safe | only if you add try/catch | yes | yes |
| Use when | rarely (interfacing with old APIs) | default choice | genuinely shared lifetime only |

Rule used: prefer `unique_ptr`; use `shared_ptr` only when two parts of the
program really need shared ownership.

## Compile, run and memory check
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -g main.cpp -o smart
./smart
valgrind --leak-check=full ./smart
```
Valgrind result: `All heap blocks were freed -- no leaks are possible`,
`ERROR SUMMARY: 0 errors`. Logs: `sample_output.txt` and `valgrind_output.txt`.

Performance note: no timing benchmark is claimed here, because results depend
on the machine and workload.

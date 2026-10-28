# Practical 08 - Singleton Design Pattern

## Question
Implement the Singleton (chosen pattern) and discuss its use case and trade-offs.

## Aim
Apply a creational design pattern to control access to a single instance.

## Pattern choice
**Singleton** was chosen because application settings (logging level, database URL, app name)
must be the same for every module in the program.

## Implementation
- `AppConfig` has a private constructor, so outside code cannot create one.
- `static AppConfig& instance()` creates the object on first call and returns the same
  object every time after that.
- The copy constructor and copy assignment are deleted, so copies cannot be made.
- Settings are read with `get(key)`; a missing key throws `std::out_of_range` and is handled.

## Demonstration
- Modules (`logging`, `database`) read the same instance.
- Changing `log.level` once is visible everywhere.
- Two calls to `instance()` return the same address (`Same object? true`).

## Benefit and trade-off
- **Benefit:** one consistent source of settings, created once, accessible everywhere.
- **Trade-off:** global access hides dependencies between modules and makes unit testing
  harder (tests share state). Dependency injection is often preferred for large systems.

## Object diagram
```
main() / modules --> AppConfig::instance() --> [ single AppConfig object ]
                                                 app.name, db.url, log.level
```

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o config
./config
```
Output: `sample_output.txt` (the object address changes between runs; that is expected).

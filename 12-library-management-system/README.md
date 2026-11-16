# Practical 12 - Mini Project: Library Management System

**Course:** B.Tech (Artificial Intelligence & Data Science) - 2nd Year  
**Subject:** Object Oriented Programming (C++)  
**Topic Selected:** Option A — Library Management System (Recommended)  
**Student:** Shivam Ray

---

## 🎯 Aim
To apply the comprehensive concepts learned throughout the OOP course (Encapsulation, Inheritance, Polymorphism, STL Containers, Custom Exception Handling, and File I/O) in a complete console-based application solving a real-world problem.

---

## 👥 Users and Problem Definition
- **Target Users:** 
  - **Librarians:** Catalog administrators who add circulating books or non-circulating reference works, issue/return books to students, inspect catalog inventory, and review transaction logs.
  - **Students / Faculty Members:** Borrowers looking up books by title or ID, checking availability, and viewing reference materials.
- **Main Problem Solved:** 
  Prevents lost inventory, tracks borrower accountability, enforces borrowing rules (e.g. non-circulating reference material cannot be taken out), prevents double-borrowing errors, and maintains persistent storage between sessions using CSV records.

---

## 🏛️ Class Architecture and Responsibilities

| Class | Responsibility | Key OOP Principle |
|---|---|---|
| `LibraryItem` | Abstract Base Class defining common item attributes (`id`, `title`, `isAvailable`, `borrowerName`) and interface (`displayDetails()`, `canBeIssued()`, `toCSV()`). | **Abstraction & Encapsulation** |
| `Book` | Circulating textbook/novel. Implements `canBeIssued() -> true`, tracks `author` and `isbn`. | **Inheritance & Polymorphism** |
| `ReferenceBook` | Non-circulating reference volume (encyclopedias, journals). Overrides `canBeIssued() -> false`. Throws exception if issued. | **Inheritance & Polymorphic Restriction** |
| `LibraryException` | Base custom exception class derived from `std::runtime_error`. | **Exception Handling** |
| `ItemNotFoundException` | Thrown when an item with a given ID does not exist in catalog. | **Robust Error Handling** |
| `ItemAlreadyIssuedException` | Thrown when trying to borrow a book already checked out. | **Data Integrity** |
| `ItemNotIssuableException` | Thrown when attempting to issue a reference-only item. | **Business Rule Enforcement** |
| `Library` | Controller holding `std::map<int, std::shared_ptr<LibraryItem>>` catalog, audit log vector, and CSV serialization logic. | **STL Containers & File I/O** |

---

## 📊 UML Class Diagram

```mermaid
classDiagram
    class LibraryItem {
        <<abstract>>
        #int id
        #string title
        #bool isAvailable
        #string borrowerName
        +getId() int
        +getTitle() string
        +getAvailability() bool
        +getBorrowerName() string
        +getItemType()* string
        +canBeIssued()* bool
        +displayDetails()* void
        +toCSV()* string
        +issueTo(studentName) void
        +returnItem() void
    }

    class Book {
        -string author
        -string isbn
        +getItemType() string
        +canBeIssued() bool
        +displayDetails() void
        +toCSV() string
    }

    class ReferenceBook {
        -string subjectDomain
        -string shelfLocation
        +getItemType() string
        +canBeIssued() bool
        +displayDetails() void
        +toCSV() string
    }

    class Library {
        -map~int, shared_ptr~LibraryItem~~ catalog
        -vector~string~ auditLog
        -string dataFilePath
        +addItem(item) void
        +issueItem(id, student) void
        +returnItem(id) void
        +searchByTitle(query) vector
        +displayAll() void
        +loadCatalogFromCSV() void
        +saveCatalogToCSV() void
    }

    class LibraryException {
        +what() const char*
    }
    class ItemNotFoundException
    class ItemAlreadyIssuedException
    class ItemNotIssuableException

    LibraryItem <|-- Book : Inherits
    LibraryItem <|-- ReferenceBook : Inherits
    Library o-- LibraryItem : Manages (std::map)
    LibraryException <|-- ItemNotFoundException : Inherits
    LibraryException <|-- ItemAlreadyIssuedException : Inherits
    LibraryException <|-- ItemNotIssuableException : Inherits
```

---

## 🚀 Compilation and Execution Instructions

### 1. Compile with C++17 Standard
```bash
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o library_app
```
*(or with g++: `g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o library_app`)*

### 2. Run Interactive Mode
```bash
./library_app
```

### 3. Run Automated Demonstration (Generates Lab Record Evidence)
```bash
./library_app --demo
```

---

## 🧪 Demonstration of Normal and Error Cases

The program includes an automated test harness covering both standard operations and exceptional edge cases:

1. **Normal Case — Issue Book:**  
   Student borrows book ID 101. Availability changes from `Available` to `Issued` under student's name.
2. **Error Case 1 — ItemAlreadyIssuedException:**  
   Another student attempts to borrow book ID 101 while it is still checked out. Caught and reported gracefully.
3. **Error Case 2 — ItemNotIssuableException:**  
   Attempt to issue Reference Book ID 201 (e.g. *Encyclopedia of Machine Learning*). Polymorphic method `canBeIssued()` returns `false`, throwing `ItemNotIssuableException`.
4. **Error Case 3 — ItemNotFoundException:**  
   Attempt to access non-existent item ID 999. Handled without crashing.
5. **Normal Case — Return Book:**  
   Item ID 101 returned, resetting borrower name and setting availability to `Available`.
6. **Error Case 4 — Return Non-Issued Item:**  
   Attempt to return an already available book. Throws exception stating item is not issued.
7. **Persistence — CSV File I/O:**  
   All changes are saved to `books.csv` on disk and automatically reloaded on next startup.

---

## 🔬 Result / Observation
A modular, object-oriented console application was successfully designed and developed. Encapsulation, inheritance, runtime polymorphism, and custom exception handling were verified through both interactive execution and an automated test suite. Data persistence was validated using structured CSV storage, and the complete codebase was tracked using Git and published to GitHub.

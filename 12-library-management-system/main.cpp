/*
 * Practical 12: Mini Project - Console-Based Application
 * Project Topic: Option A - Library Management System (Recommended)
 *
 * Subject: Object Oriented Programming (OOP)
 * Student: Shivam Ray (B.Tech AI & DS, 2nd Year)
 *
 * Core Concepts Demonstrated:
 * 1. Object-Oriented Programming (Encapsulation, Abstract Base Class, Polymorphism)
 * 2. Standard Template Library (std::map, std::vector, std::shared_ptr, std::algorithm)
 * 3. Custom Exception Hierarchy (derived from std::runtime_error)
 * 4. Persistent File I/O with CSV reading and writing (std::fstream)
 * 5. Input Validation and Interactive Console Menu + Automated Demo
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

// ============================================================================
// 1. CUSTOM EXCEPTION HIERARCHY
// ============================================================================

class LibraryException : public std::runtime_error {
public:
    explicit LibraryException(const std::string& message)
        : std::runtime_error("[Library Error] " + message) {}
};

class ItemNotFoundException : public LibraryException {
public:
    explicit ItemNotFoundException(int id)
        : LibraryException("Item with ID " + std::to_string(id) + " was not found in the catalog.") {}
};

class ItemAlreadyIssuedException : public LibraryException {
public:
    explicit ItemAlreadyIssuedException(int id, const std::string& borrower)
        : LibraryException("Item ID " + std::to_string(id) + " is already issued to: " + borrower) {}
};

class ItemNotIssuableException : public LibraryException {
public:
    explicit ItemNotIssuableException(int id, const std::string& title)
        : LibraryException("Item ID " + std::to_string(id) + " (\"" + title +
                           "\") is a Reference item and cannot be issued out of the library.") {}
};

class InvalidDataException : public LibraryException {
public:
    explicit InvalidDataException(const std::string& msg)
        : LibraryException("Validation failure: " + msg) {}
};

class FileIOException : public LibraryException {
public:
    explicit FileIOException(const std::string& filename, const std::string& detail)
        : LibraryException("File I/O error on '" + filename + "': " + detail) {}
};

// ============================================================================
// 2. ABSTRACT BASE CLASS: LibraryItem (Encapsulation & Polymorphism)
// ============================================================================

class LibraryItem {
protected:
    int id;
    std::string title;
    bool isAvailable;
    std::string borrowerName;

public:
    LibraryItem(int itemId, std::string itemTitle, bool available = true, std::string borrower = "")
        : id(itemId), title(std::move(itemTitle)), isAvailable(available), borrowerName(std::move(borrower)) {
        if (id <= 0) {
            throw InvalidDataException("Item ID must be a positive integer.");
        }
        if (title.empty()) {
            throw InvalidDataException("Item title cannot be empty.");
        }
    }

    virtual ~LibraryItem() = default;

    // Getters (Encapsulation)
    int getId() const { return id; }
    const std::string& getTitle() const { return title; }
    bool getAvailability() const { return isAvailable; }
    const std::string& getBorrowerName() const { return borrowerName; }

    // Pure Virtual Functions (Polymorphism)
    virtual std::string getItemType() const = 0;
    virtual bool canBeIssued() const = 0;
    virtual void displayDetails() const = 0;
    virtual std::string toCSV() const = 0;

    // Circulation logic
    virtual void issueTo(const std::string& studentName) {
        if (!canBeIssued()) {
            throw ItemNotIssuableException(id, title);
        }
        if (!isAvailable) {
            throw ItemAlreadyIssuedException(id, borrowerName);
        }
        if (studentName.empty()) {
            throw InvalidDataException("Borrower name cannot be empty.");
        }
        isAvailable = false;
        borrowerName = studentName;
    }

    virtual void returnItem() {
        if (isAvailable) {
            throw LibraryException("Item ID " + std::to_string(id) + " is not currently issued.");
        }
        isAvailable = true;
        borrowerName = "";
    }
};

// ============================================================================
// 3. DERIVED CLASS 1: Book (General Circulating Book)
// ============================================================================

class Book : public LibraryItem {
private:
    std::string author;
    std::string isbn;

public:
    Book(int id, const std::string& title, std::string bookAuthor, std::string bookIsbn,
         bool available = true, const std::string& borrower = "")
        : LibraryItem(id, title, available, borrower),
          author(std::move(bookAuthor)), isbn(std::move(bookIsbn)) {
        if (author.empty()) {
            throw InvalidDataException("Book author cannot be empty.");
        }
    }

    const std::string& getAuthor() const { return author; }
    const std::string& getISBN() const { return isbn; }

    std::string getItemType() const override { return "Standard Book"; }
    bool canBeIssued() const override { return true; }

    void displayDetails() const override {
        std::cout << " [" << std::setw(3) << id << "] "
                  << std::left << std::setw(15) << getItemType()
                  << std::setw(32) << (title.length() > 30 ? title.substr(0, 27) + "..." : title)
                  << std::setw(22) << (author.length() > 20 ? author.substr(0, 18) + "..." : author)
                  << std::setw(12) << (isAvailable ? "Available" : "Issued")
                  << (isAvailable ? "-" : borrowerName) << "\n";
    }

    std::string toCSV() const override {
        // Format: ID,Type,Title,AuthorOrSubject,ExtraInfo,IsAvailable,BorrowerName
        return std::to_string(id) + ",BOOK," + title + "," + author + "," + isbn + "," +
               (isAvailable ? "1" : "0") + "," + borrowerName;
    }
};

// ============================================================================
// 4. DERIVED CLASS 2: ReferenceBook (Non-Circulating Reference Material)
// ============================================================================

class ReferenceBook : public LibraryItem {
private:
    std::string subjectDomain;
    std::string shelfLocation;

public:
    ReferenceBook(int id, const std::string& title, std::string domain, std::string shelf,
                  bool available = true, const std::string& borrower = "")
        : LibraryItem(id, title, available, borrower),
          subjectDomain(std::move(domain)), shelfLocation(std::move(shelf)) {
        if (subjectDomain.empty()) {
            throw InvalidDataException("Reference book subject domain cannot be empty.");
        }
    }

    const std::string& getDomain() const { return subjectDomain; }
    const std::string& getShelf() const { return shelfLocation; }

    std::string getItemType() const override { return "Reference Book"; }
    bool canBeIssued() const override { return false; } // Polymorphic restriction

    void displayDetails() const override {
        std::cout << " [" << std::setw(3) << id << "] "
                  << std::left << std::setw(15) << getItemType()
                  << std::setw(32) << (title.length() > 30 ? title.substr(0, 27) + "..." : title)
                  << std::setw(22) << ("[" + subjectDomain + "]")
                  << std::setw(12) << "Ref Only"
                  << "Shelf: " << shelfLocation << "\n";
    }

    std::string toCSV() const override {
        return std::to_string(id) + ",REF," + title + "," + subjectDomain + "," + shelfLocation + "," +
               (isAvailable ? "1" : "0") + "," + borrowerName;
    }
};

// ============================================================================
// 5. CONTROLLER CLASS: Library (STL Containers & File I/O)
// ============================================================================

class Library {
private:
    // STL Map for O(log N) lookup by ID and automatic sorted order
    std::map<int, std::shared_ptr<LibraryItem>> catalog;
    // STL Vector for maintaining audit trail
    std::vector<std::string> auditLog;
    std::string dataFilePath;

public:
    explicit Library(std::string filePath = "books.csv")
        : dataFilePath(std::move(filePath)) {
        loadCatalogFromCSV();
    }

    ~Library() {
        // Auto-save upon exit
        try {
            saveCatalogToCSV();
        } catch (...) {
            // Suppress exceptions in destructor
        }
    }

    void logAction(const std::string& action) {
        auditLog.push_back(action);
    }

    void addItem(std::shared_ptr<LibraryItem> item) {
        if (!item) {
            throw InvalidDataException("Null item pointer provided.");
        }
        if (catalog.find(item->getId()) != catalog.end()) {
            throw InvalidDataException("Item ID " + std::to_string(item->getId()) + " already exists in library.");
        }
        catalog[item->getId()] = item;
        logAction("Added new " + item->getItemType() + " [ID: " + std::to_string(item->getId()) + "]: " + item->getTitle());
    }

    void issueItem(int id, const std::string& studentName) {
        auto it = catalog.find(id);
        if (it == catalog.end()) {
            throw ItemNotFoundException(id);
        }
        it->second->issueTo(studentName);
        logAction("Issued [ID: " + std::to_string(id) + "] to " + studentName);
    }

    void returnItem(int id) {
        auto it = catalog.find(id);
        if (it == catalog.end()) {
            throw ItemNotFoundException(id);
        }
        std::string previousBorrower = it->second->getBorrowerName();
        it->second->returnItem();
        logAction("Returned [ID: " + std::to_string(id) + "] from " + previousBorrower);
    }

    std::shared_ptr<LibraryItem> findById(int id) const {
        auto it = catalog.find(id);
        if (it == catalog.end()) {
            throw ItemNotFoundException(id);
        }
        return it->second;
    }

    std::vector<std::shared_ptr<LibraryItem>> searchByTitle(const std::string& query) const {
        std::vector<std::shared_ptr<LibraryItem>> results;
        std::string lowerQuery = query;
        std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

        for (const auto& pair : catalog) {
            std::string lowerTitle = pair.second->getTitle();
            std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
            if (lowerTitle.find(lowerQuery) != std::string::npos) {
                results.push_back(pair.second);
            }
        }
        return results;
    }

    void displayAll() const {
        std::cout << "\n========================================================================================================\n";
        std::cout << " ID   Type            Title                           Author / Subject      Status      Borrower / Shelf\n";
        std::cout << "--------------------------------------------------------------------------------------------------------\n";
        if (catalog.empty()) {
            std::cout << " (Library catalog is currently empty)\n";
        } else {
            for (const auto& pair : catalog) {
                pair.second->displayDetails();
            }
        }
        std::cout << "========================================================================================================\n";
        std::cout << " Total Catalog Items: " << catalog.size() << "\n\n";
    }

    void displayAuditLog() const {
        std::cout << "\n--- Library Audit Log (" << auditLog.size() << " events) ---\n";
        for (size_t i = 0; i < auditLog.size(); ++i) {
            std::cout << " [" << (i + 1) << "] " << auditLog[i] << "\n";
        }
        std::cout << "-----------------------------------------\n";
    }

    // ---------------- File I/O & CSV Handling ----------------
    void loadCatalogFromCSV() {
        std::ifstream file(dataFilePath);
        if (!file.is_open()) {
            // Seed initial sample books for 2nd year AI/DS curriculum if file doesn't exist yet
            seedStarterCatalogue();
            return;
        }

        catalog.clear();
        std::string line;
        bool isHeader = true;
        int lineNum = 0;

        while (std::getline(file, line)) {
            lineNum++;
            if (line.empty()) continue;
            if (isHeader) {
                isHeader = false;
                continue; // Skip header
            }

            std::stringstream ss(line);
            std::string idStr, type, title, field4, field5, availStr, borrower;

            if (std::getline(ss, idStr, ',') &&
                std::getline(ss, type, ',') &&
                std::getline(ss, title, ',') &&
                std::getline(ss, field4, ',') &&
                std::getline(ss, field5, ',') &&
                std::getline(ss, availStr, ',')) {

                std::getline(ss, borrower); // borrower may be empty

                try {
                    int id = std::stoi(idStr);
                    bool isAvail = (availStr == "1");

                    if (type == "BOOK") {
                        catalog[id] = std::make_shared<Book>(id, title, field4, field5, isAvail, borrower);
                    } else if (type == "REF") {
                        catalog[id] = std::make_shared<ReferenceBook>(id, title, field4, field5, isAvail, borrower);
                    }
                } catch (const std::exception& e) {
                    std::cerr << "[Warning] Skipping malformed record on line " << lineNum << ": " << e.what() << "\n";
                }
            }
        }
        file.close();
        logAction("Loaded " + std::to_string(catalog.size()) + " items from " + dataFilePath);
    }

    void saveCatalogToCSV() const {
        std::ofstream file(dataFilePath);
        if (!file.is_open()) {
            throw FileIOException(dataFilePath, "Unable to open file for writing.");
        }

        // CSV Header
        file << "id,type,title,author_or_domain,isbn_or_shelf,is_available,borrower_name\n";
        for (const auto& pair : catalog) {
            file << pair.second->toCSV() << "\n";
        }
        file.close();
    }

    void seedStarterCatalogue() {
        addItem(std::make_shared<Book>(101, "Object-Oriented Programming with C++", "E. Balagurusamy", "978-0070669079"));
        addItem(std::make_shared<Book>(102, "Introduction to Algorithms (CLRS)", "Thomas H. Cormen", "978-0262033848"));
        addItem(std::make_shared<Book>(103, "Artificial Intelligence: A Modern Approach", "Stuart Russell", "978-0136042594"));
        addItem(std::make_shared<ReferenceBook>(201, "Encyclopedia of Machine Learning", "AI/DS Research", "Rack-R1-Shelf3"));
        addItem(std::make_shared<ReferenceBook>(202, "ACM Computing Surveys (Vol. 55)", "Computer Science", "Rack-R2-Shelf1"));
        saveCatalogToCSV();
        logAction("Initialized starter library catalogue with 5 items.");
    }
};

// ============================================================================
// 6. DEMONSTRATION SUITE (Normal & Error Cases for Lab Record)
// ============================================================================

void runAutomatedDemonstration(Library& lib) {
    std::cout << "\n========================================================\n";
    std::cout << "   RUNNING AUTOMATED DEMONSTRATION (NORMAL & ERROR CASES) \n";
    std::cout << "========================================================\n\n";

    // 1. Initial State
    std::cout << ">>> 1. INITIAL CATALOG STATUS <<<\n";
    lib.displayAll();

    // 2. Normal Case: Issue a standard book
    std::cout << ">>> 2. NORMAL CASE: Issue Book ID 101 to student 'Shivam Ray' <<<\n";
    try {
        lib.issueItem(101, "Shivam Ray");
        std::cout << "[SUCCESS] Book ID 101 successfully issued to Shivam Ray.\n";
    } catch (const std::exception& e) {
        std::cout << "[FAILED] " << e.what() << "\n";
    }

    // 3. Error Case: Try to issue the same book again (ItemAlreadyIssuedException)
    std::cout << "\n>>> 3. ERROR CASE 1: Attempt to re-issue already borrowed Book ID 101 <<<\n";
    try {
        lib.issueItem(101, "Rahul Sharma");
        std::cout << "[UNEXPECTED SUCCESS] Should have thrown exception!\n";
    } catch (const LibraryException& e) {
        std::cout << "[CAUGHT EXPECTED EXCEPTION] " << e.what() << "\n";
    }

    // 4. Error Case: Try to issue a Reference Book (ItemNotIssuableException)
    std::cout << "\n>>> 4. ERROR CASE 2: Attempt to issue Reference Book ID 201 (Non-circulating) <<<\n";
    try {
        lib.issueItem(201, "Sneha Kulkarni");
        std::cout << "[UNEXPECTED SUCCESS] Should have thrown exception!\n";
    } catch (const LibraryException& e) {
        std::cout << "[CAUGHT EXPECTED EXCEPTION] " << e.what() << "\n";
    }

    // 5. Error Case: Non-existent item ID (ItemNotFoundException)
    std::cout << "\n>>> 5. ERROR CASE 3: Attempt to issue non-existent Book ID 999 <<<\n";
    try {
        lib.issueItem(999, "Aman Gupta");
        std::cout << "[UNEXPECTED SUCCESS] Should have thrown exception!\n";
    } catch (const LibraryException& e) {
        std::cout << "[CAUGHT EXPECTED EXCEPTION] " << e.what() << "\n";
    }

    // 6. Normal Case: Return the issued book
    std::cout << "\n>>> 6. NORMAL CASE: Return Book ID 101 <<<\n";
    try {
        lib.returnItem(101);
        std::cout << "[SUCCESS] Book ID 101 returned and marked Available.\n";
    } catch (const std::exception& e) {
        std::cout << "[FAILED] " << e.what() << "\n";
    }

    // 7. Error Case: Return an item that is already available
    std::cout << "\n>>> 7. ERROR CASE 4: Attempt to return already available Book ID 101 <<<\n";
    try {
        lib.returnItem(101);
        std::cout << "[UNEXPECTED SUCCESS] Should have thrown exception!\n";
    } catch (const LibraryException& e) {
        std::cout << "[CAUGHT EXPECTED EXCEPTION] " << e.what() << "\n";
    }

    // 8. Normal Case: Search by keyword
    std::cout << "\n>>> 8. NORMAL CASE: Search by keyword 'Intelligence' <<<\n";
    auto searchResults = lib.searchByTitle("Intelligence");
    std::cout << "Found " << searchResults.size() << " match(es):\n";
    for (const auto& item : searchResults) {
        item->displayDetails();
    }

    // 9. Display updated catalog
    std::cout << "\n>>> 9. FINAL CATALOG AND AUDIT LOG <<<\n";
    lib.displayAll();
    lib.displayAuditLog();

    std::cout << "\n>>> 10. PERSISTENCE VERIFICATION: Saving catalog to 'books.csv' <<<\n";
    lib.saveCatalogToCSV();
    std::cout << "[SUCCESS] Catalog persisted to disk.\n";
    std::cout << "========================================================\n";
}

// ============================================================================
// 7. MAIN FUNCTION & INTERACTIVE MENU
// ============================================================================

void printMenu() {
    std::cout << "\n============================================\n";
    std::cout << "       LIBRARY MANAGEMENT SYSTEM (OOP)      \n";
    std::cout << "============================================\n";
    std::cout << " 1. Display All Items in Catalog\n";
    std::cout << " 2. Add New Standard Book\n";
    std::cout << " 3. Add New Reference Book\n";
    std::cout << " 4. Search Item by Title\n";
    std::cout << " 5. Issue Book to Member\n";
    std::cout << " 6. Return Book\n";
    std::cout << " 7. Run Automated Demonstration (Lab Record)\n";
    std::cout << " 8. Save and Exit\n";
    std::cout << "============================================\n";
    std::cout << "Enter your choice (1-8): ";
}

int main(int argc, char* argv[]) {
    std::cout << "Starting Library Management System...\n";
    Library library("books.csv");

    // If --demo argument passed, run demonstration directly
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runAutomatedDemonstration(library);
        return 0;
    }

    int choice = 0;
    while (choice != 8) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\n[Error] Invalid input. Please enter a number between 1 and 8.\n";
            continue;
        }
        std::cin.ignore(10000, '\n'); // flush newline

        try {
            switch (choice) {
                case 1: {
                    library.displayAll();
                    break;
                }
                case 2: {
                    int id;
                    std::string title, author, isbn;
                    std::cout << "Enter Book ID (Integer): ";
                    std::cin >> id;
                    std::cin.ignore(10000, '\n');
                    std::cout << "Enter Title: ";
                    std::getline(std::cin, title);
                    std::cout << "Enter Author: ";
                    std::getline(std::cin, author);
                    std::cout << "Enter ISBN: ";
                    std::getline(std::cin, isbn);

                    library.addItem(std::make_shared<Book>(id, title, author, isbn));
                    library.saveCatalogToCSV();
                    std::cout << "\n[SUCCESS] Book added successfully and saved to CSV.\n";
                    break;
                }
                case 3: {
                    int id;
                    std::string title, domain, shelf;
                    std::cout << "Enter Reference Book ID (Integer): ";
                    std::cin >> id;
                    std::cin.ignore(10000, '\n');
                    std::cout << "Enter Title: ";
                    std::getline(std::cin, title);
                    std::cout << "Enter Subject Domain: ";
                    std::getline(std::cin, domain);
                    std::cout << "Enter Shelf Location: ";
                    std::getline(std::cin, shelf);

                    library.addItem(std::make_shared<ReferenceBook>(id, title, domain, shelf));
                    library.saveCatalogToCSV();
                    std::cout << "\n[SUCCESS] Reference Book added successfully and saved to CSV.\n";
                    break;
                }
                case 4: {
                    std::string query;
                    std::cout << "Enter title keyword to search: ";
                    std::getline(std::cin, query);
                    auto results = library.searchByTitle(query);
                    std::cout << "\nFound " << results.size() << " result(s):\n";
                    for (const auto& item : results) {
                        item->displayDetails();
                    }
                    break;
                }
                case 5: {
                    int id;
                    std::string student;
                    std::cout << "Enter Item ID to Issue: ";
                    std::cin >> id;
                    std::cin.ignore(10000, '\n');
                    std::cout << "Enter Student/Borrower Name: ";
                    std::getline(std::cin, student);

                    library.issueItem(id, student);
                    library.saveCatalogToCSV();
                    std::cout << "\n[SUCCESS] Item ID " << id << " issued to " << student << ".\n";
                    break;
                }
                case 6: {
                    int id;
                    std::cout << "Enter Item ID to Return: ";
                    std::cin >> id;
                    std::cin.ignore(10000, '\n');

                    library.returnItem(id);
                    library.saveCatalogToCSV();
                    std::cout << "\n[SUCCESS] Item ID " << id << " returned successfully.\n";
                    break;
                }
                case 7: {
                    runAutomatedDemonstration(library);
                    break;
                }
                case 8: {
                    library.saveCatalogToCSV();
                    std::cout << "\nCatalog saved to books.csv. Thank you for using Library Management System!\n";
                    break;
                }
                default:
                    std::cout << "\n[Error] Invalid option. Please choose 1-8.\n";
                    break;
            }
        } catch (const LibraryException& e) {
            std::cout << "\n" << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "\n[Unexpected Error] " << e.what() << "\n";
        }
    }

    return 0;
}

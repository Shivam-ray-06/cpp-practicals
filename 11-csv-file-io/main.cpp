// Practical 11 - CSV Student Records Using File I/O
//
// Part 1: save and load Student records as a documented CSV format:
//         id,name,marks  (first line is a header)
// Part 2: demonstrate tellg() / seekg() (input position) and
//         tellp() / seekp() (output position) on a separate demo file.
//
// Note: we write fields as CSV text rather than raw struct bytes, because raw
// bytes are not portable (padding, byte order and string layout differ).

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Student {
    int         id;
    std::string name;
    double      marks;
};

const std::string CSV_FILE = "students.csv";
const std::string CSV_HEADER = "id,name,marks";

// ---- Writing ----
bool saveStudents(const std::string& path, const std::vector<Student>& students) {
    std::ofstream out(path);                 // truncates the file each time
    if (!out) {
        std::cerr << "[error] cannot open '" << path << "' for writing\n";
        return false;
    }
    out << CSV_HEADER << "\n";
    for (const Student& s : students) {
        out << s.id << "," << s.name << "," << s.marks << "\n";
    }
    if (!out) {                              // checks that the writes succeeded
        std::cerr << "[error] writing to '" << path << "' failed\n";
        return false;
    }
    return true;
}

// ---- Reading ----
// Malformed lines are reported and skipped rather than stopping the whole load.
std::vector<Student> loadStudents(const std::string& path) {
    std::vector<Student> students;
    std::ifstream in(path);
    if (!in) {
        std::cerr << "[error] cannot open '" << path << "' for reading\n";
        return students;
    }

    std::string line;
    std::getline(in, line);                  // skip header

    int lineNumber = 1;
    while (std::getline(in, line)) {
        ++lineNumber;
        if (line.empty()) continue;

        std::stringstream fields(line);
        std::string idText, name, marksText;
        if (!std::getline(fields, idText, ',') ||
            !std::getline(fields, name, ',') ||
            !std::getline(fields, marksText)) {
            std::cerr << "[warning] line " << lineNumber << " is malformed, skipped\n";
            continue;
        }

        try {
            Student s;
            s.id    = std::stoi(idText);
            s.name  = name;
            s.marks = std::stod(marksText);
            if (s.marks < 0 || s.marks > 100) {
                std::cerr << "[warning] line " << lineNumber << " has invalid marks, skipped\n";
                continue;
            }
            students.push_back(s);
        } catch (const std::exception&) {
            std::cerr << "[warning] line " << lineNumber << " has non-numeric fields, skipped\n";
        }
    }
    return students;
}

void printStudents(const std::vector<Student>& students) {
    std::cout << "ID    Name                 Marks\n";
    std::cout << "----  -------------------  -----\n";
    for (const Student& s : students) {
        std::cout.width(4);
        std::cout << s.id << "  ";
        std::cout.width(19);
        std::cout << std::left << s.name << std::right << "  " << s.marks << "\n";
    }
}

// ---- File-position demonstration ----
void demoFilePositions() {
    const std::string demoPath = "position_demo.txt";

    // ---- Output position: tellp() and seekp() ----
    // Open for reading AND writing so seekp can overwrite in the middle.
    {
        std::ofstream create(demoPath);          // create the file with known content
        create << "AAAAAAAAAA";                  // 10 characters
    }
    std::fstream file(demoPath, std::ios::in | std::ios::out);
    if (!file) {
        std::cerr << "[error] cannot open demo file\n";
        return;
    }

    std::cout << "Initial output position (tellp): " << file.tellp() << "\n";
    file.seekp(3);                               // move the write position to index 3
    std::cout << "After seekp(3), tellp() = " << file.tellp() << "\n";
    file << "BBB";                               // overwrites characters 3..5
    std::cout << "After writing 3 chars, tellp() = " << file.tellp() << "\n";

    // ---- Input position: tellg() and seekg() ----
    file.clear();                                // clear state flags before reading
    file.seekg(0);
    std::cout << "Initial input position (tellg): " << file.tellg() << "\n";
    file.seekg(3);
    std::cout << "After seekg(3), tellg() = " << file.tellg() << "\n";

    char ch = '?';
    file.get(ch);
    std::cout << "Character at position 3 is '" << ch << "'; tellg() now = "
              << file.tellg() << "\n";

    file.seekg(0, std::ios::end);
    std::cout << "Total length found with seekg(0, end): " << file.tellg() << "\n";

    std::cout << "\nFile contents now: ";
    file.seekg(0);
    std::string contents;
    std::getline(file, contents);
    std::cout << contents << "\n";
}

int main() {
    std::cout << "=== Part 1: Writing student records ===\n";
    std::vector<Student> records = {
        {101, "Asha Nair",     87.5},
        {102, "Dev Patel",     72.0},
        {103, "Priya Menon",   94.25},
    };
    if (saveStudents(CSV_FILE, records)) {
        std::cout << "Saved " << records.size() << " records to " << CSV_FILE << "\n";
    }

    std::cout << "\n=== Part 2: Reading records back ===\n";
    std::vector<Student> loaded = loadStudents(CSV_FILE);
    printStudents(loaded);
    std::cout << "Loaded " << loaded.size() << " records\n";

    std::cout << "\n=== Part 3: Handling a missing file ===\n";
    loadStudents("does_not_exist.csv");

    std::cout << "\n=== Part 4: Malformed input in the CSV ===\n";
    {
        std::ofstream bad("students_bad.csv");
        bad << CSV_HEADER << "\n"
            << "201,Good Student,80\n"
            << "202,Missing Marks\n"                // malformed: only two fields
            << "abc,Non Number,50\n"                // malformed: id is not a number
            << "203,Too High,150\n";                // invalid: marks out of range
    }
    std::vector<Student> partial = loadStudents("students_bad.csv");
    printStudents(partial);
    std::cout << "Valid records loaded: " << partial.size() << "\n";

    std::cout << "\n=== Part 5: File-position functions ===\n";
    demoFilePositions();

    std::cout << "\nInput position (get) and output position (put) are tracked separately,\n"
                 "so seekg/tellg and seekp/tellp can move through the same file independently.\n";
    return 0;
}

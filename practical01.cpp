/*
 * Practical 01: GitHub Setup and C++ Fundamentals
 * Aim: To practise basic C++ syntax (data types, constants, variables,
 *      operators, and I/O) and learn tracking code changes using Git & GitHub.
 * Student Branch: B.Tech (AI & DS)
 * Subject: Object Oriented Programming (OOP)
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    // 1. Constants
    const int MAX_MARKS = 100;
    const float PASS_PERCENTAGE = 40.0f;

    // 2. Variables of primitive & string data types
    string studentName;
    int rollNumber;
    float marks1, marks2, marks3;
    float totalMarks, percentage;
    char grade;
    bool isPassed;

    // 3. User Input (cin)
    cout << "========================================" << endl;
    cout << "  Student Performance Evaluation System  " << endl;
    cout << "========================================" << endl;

    cout << "Enter Student Name: ";
    getline(cin, studentName);

    cout << "Enter Roll Number: ";
    cin >> rollNumber;

    cout << "Enter marks for Subject 1 (out of " << MAX_MARKS << "): ";
    cin >> marks1;

    cout << "Enter marks for Subject 2 (out of " << MAX_MARKS << "): ";
    cin >> marks2;

    cout << "Enter marks for Subject 3 (out of " << MAX_MARKS << "): ";
    cin >> marks3;

    // 4. Arithmetic Operators (+, /, *)
    totalMarks = marks1 + marks2 + marks3;
    percentage = (totalMarks / (3.0f * MAX_MARKS)) * 100.0f;

    // 5. Relational and Logical Operators (>=, <, &&)
    // Student passes only if marks in all subjects are >= 40 AND percentage >= 40
    isPassed = (marks1 >= 40.0f) && (marks2 >= 40.0f) && (marks3 >= 40.0f) && (percentage >= PASS_PERCENTAGE);

    if (percentage >= 90.0f) {
        grade = 'O'; // Outstanding
    } else if (percentage >= 75.0f) {
        grade = 'A';
    } else if (percentage >= 60.0f) {
        grade = 'B';
    } else if (percentage >= 40.0f) {
        grade = 'C';
    } else {
        grade = 'F';
    }

    // 6. Formatted Output (cout)
    cout << "\n----------------------------------------" << endl;
    cout << "             REPORT CARD               " << endl;
    cout << "----------------------------------------" << endl;
    cout << "Student Name : " << studentName << endl;
    cout << "Roll Number  : " << rollNumber << endl;
    cout << fixed << setprecision(2);
    cout << "Subject 1    : " << marks1 << " / " << MAX_MARKS << endl;
    cout << "Subject 2    : " << marks2 << " / " << MAX_MARKS << endl;
    cout << "Subject 3    : " << marks3 << " / " << MAX_MARKS << endl;
    cout << "Total Marks  : " << totalMarks << " / " << (3 * MAX_MARKS) << endl;
    cout << "Percentage   : " << percentage << "%" << endl;
    cout << "Grade        : " << grade << endl;
    cout << "Result       : " << (isPassed ? "PASSED" : "FAILED") << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}


// Practical 05 - Single and Multilevel Inheritance
//
// University example:  Person -> Student -> GraduateStudent
//   Person          : base class (single inheritance is Person -> Student)
//   Student         : derived from Person
//   GraduateStudent : derived from Student (multilevel inheritance)

#include <iostream>
#include <string>

// ---- Base class ----
class Person {
protected:                  // protected: visible to derived classes, hidden from main()
    std::string name_;
    int         age_;

public:
    Person(std::string name, int age) : name_(std::move(name)), age_(age) {
        std::cout << "  [Person ctor] " << name_ << "\n";
    }
    virtual ~Person() = default;   // virtual destructor: safe deletion through base pointers

    void displayPerson() const {
        std::cout << "Name: " << name_ << " | Age: " << age_ << "\n";
    }
};

// ---- Single inheritance: Student is-a Person ----
class Student : public Person {
protected:
    std::string studentId_;
    std::string course_;

public:
    Student(std::string name, int age, std::string id, std::string course)
        : Person(std::move(name), age),          // base constructor runs first
          studentId_(std::move(id)), course_(std::move(course)) {
        std::cout << "  [Student ctor] " << studentId_ << "\n";
    }

    void displayStudent() const {
        displayPerson();                         // reuses the inherited method
        std::cout << "  Student ID: " << studentId_ << " | Course: " << course_ << "\n";
    }
};

// ---- Multilevel inheritance: GraduateStudent is-a Student is-a Person ----
class GraduateStudent : public Student {
private:
    std::string researchTopic_;
    std::string supervisor_;

public:
    GraduateStudent(std::string name, int age, std::string id, std::string course,
                    std::string topic, std::string supervisor)
        : Student(std::move(name), age, std::move(id), std::move(course)),
          researchTopic_(std::move(topic)), supervisor_(std::move(supervisor)) {
        std::cout << "  [GraduateStudent ctor] " << researchTopic_ << "\n";
    }

    void displayGraduate() const {
        displayStudent();                        // inherited from Student, which uses Person
        std::cout << "  Research topic: " << researchTopic_
                  << " | Supervisor: " << supervisor_ << "\n";
    }
};

int main() {
    std::cout << "=== Single inheritance: Person -> Student ===\n";
    Student s1("Anita Sharma", 20, "CS2026-014", "B.Sc. Computer Science");
    s1.displayStudent();

    std::cout << "\n=== Multilevel inheritance: Person -> Student -> GraduateStudent ===\n";
    GraduateStudent g1("Rahul Verma", 25, "PG2026-003", "M.Sc. Computer Science",
                       "Deep learning for code generation", "Dr. Meera Iyer");
    g1.displayGraduate();

    std::cout << "\n=== Inherited members available to each class ===\n";
    std::cout << "Student object can use : displayPerson(), displayStudent()\n";
    std::cout << "GraduateStudent object can use : displayPerson(), displayStudent(), displayGraduate()\n";

    // Derived objects can be used wherever a base reference is expected.
    const Person& asPerson = g1;
    std::cout << "\nViewed as a Person reference: ";
    asPerson.displayPerson();

    return 0;
}

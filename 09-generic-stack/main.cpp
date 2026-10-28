// Practical 09 - Generic Stack Using Templates
//
// A class template lets one implementation work with any element type.
// Without templates we would need three separate classes: IntStack, FloatStack
// and StringStack. The compiler generates the right version for each type used.

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class Stack {
public:
    void push(const T& value) {
        items_.push_back(value);
    }

    // Removes the top item. Popping an empty stack throws a clear error.
    void pop() {
        if (empty()) {
            throw std::underflow_error("pop() called on an empty stack");
        }
        items_.pop_back();
    }

    // Safe access to the top item without removing it.
    const T& top() const {
        if (empty()) {
            throw std::underflow_error("top() called on an empty stack");
        }
        return items_.back();
    }

    bool empty() const { return items_.empty(); }
    std::size_t size() const { return items_.size(); }

private:
    std::vector<T> items_;   // STL container used internally
};

// Helper template to test any stack type with the same code.
template <typename T>
void runStackTest(const std::string& typeName, const std::vector<T>& values) {
    std::cout << "\n--- Stack<" << typeName << "> ---\n";
    Stack<T> stack;

    std::cout << "Initially empty? " << std::boolalpha << stack.empty() << "\n";
    for (const T& v : values) {
        stack.push(v);
        std::cout << "pushed " << v << " | size = " << stack.size() << "\n";
    }

    std::cout << "top = " << stack.top() << "\n";
    while (!stack.empty()) {
        std::cout << "popping " << stack.top() << "\n";
        stack.pop();
    }
    std::cout << "Empty after popping all? " << stack.empty() << "\n";

    // Edge case: popping from an empty stack.
    try {
        stack.pop();
    } catch (const std::underflow_error& ex) {
        std::cout << "Error handled: " << ex.what() << "\n";
    }
}

int main() {
    std::cout << "=== Generic Stack tested with three data types ===\n";
    runStackTest<int>("int", {10, 20, 30});
    runStackTest<float>("float", {1.5f, 2.25f, 3.75f});
    runStackTest<std::string>("std::string", {"alpha", "beta", "gamma"});

    std::cout << "\nWhy templates help: one class definition serves int, float and\n"
                 "std::string. The compiler generates each version when it is used.\n";
    return 0;
}

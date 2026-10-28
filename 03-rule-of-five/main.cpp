// Practical 03 - Constructors and the Rule of Five
//
// IntArray owns a dynamically allocated int array. Because it owns a raw
// resource, it must define (or deliberately delete) all five special members:
//   1. destructor
//   2. copy constructor
//   3. copy assignment operator
//   4. move constructor
//   5. move assignment operator
// It also has a default constructor and a parameterised constructor.

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

class IntArray {
private:
    int*        data_;
    std::size_t size_;

    void swap(IntArray& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

public:
    // ---- Additional constructors (not part of the Rule of Five) ----

    // Default constructor: empty array, owns no memory.
    IntArray() : data_(nullptr), size_(0) {
        std::cout << "  [default ctor]\n";
    }

    // Parameterised constructor: allocates n ints, all set to 'value'.
    explicit IntArray(std::size_t n, int value = 0)
        : data_(n > 0 ? new int[n] : nullptr), size_(n) {
        std::fill(data_, data_ + size_, value);
        std::cout << "  [parameterised ctor] size " << size_ << "\n";
    }

    // ---- Rule of Five ----

    // 1. Destructor: releases the owned memory.
    ~IntArray() {
        std::cout << "  [destructor] releasing " << size_ << " ints\n";
        delete[] data_;
    }

    // 2. Copy constructor: DEEP copy - allocates new memory and copies values.
    IntArray(const IntArray& other)
        : data_(other.size_ > 0 ? new int[other.size_] : nullptr), size_(other.size_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
        std::cout << "  [copy ctor] deep-copied " << size_ << " ints\n";
    }

    // 3. Copy assignment: copy-and-swap idiom gives a strong exception guarantee
    //    and correctly handles self-assignment.
    IntArray& operator=(const IntArray& other) {
        std::cout << "  [copy assignment]\n";
        if (this != &other) {
            IntArray temp(other);   // reuses the copy constructor
            swap(temp);             // temp now holds our old data and frees it
        }
        return *this;
    }

    // 4. Move constructor: TAKES OWNERSHIP of other's memory - no copying.
    //    noexcept lets containers such as std::vector move instead of copy.
    IntArray(IntArray&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;      // leave 'other' in a valid, empty state
        other.size_ = 0;
        std::cout << "  [move ctor] transferred ownership\n";
    }

    // 5. Move assignment: frees our memory, then takes over other's memory.
    IntArray& operator=(IntArray&& other) noexcept {
        std::cout << "  [move assignment]\n";
        if (this != &other) {
            delete[] data_;
            data_       = other.data_;
            size_       = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // ---- Helper functions ----

    std::size_t size() const { return size_; }

    // Bounds-checked element access.
    int& at(std::size_t index) {
        if (index >= size_) throw std::out_of_range("IntArray index out of range");
        return data_[index];
    }
    int at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range("IntArray index out of range");
        return data_[index];
    }

    void print(const char* label) const {
        std::cout << label << ": [";
        for (std::size_t i = 0; i < size_; ++i) {
            std::cout << data_[i] << (i + 1 < size_ ? ", " : "");
        }
        std::cout << "] (size " << size_ << ")\n";
    }
};

// Helper that returns an object by value - demonstrates move semantics.
IntArray makeSquares(std::size_t n) {
    IntArray result(n);
    for (std::size_t i = 0; i < n; ++i) {
        result.at(i) = static_cast<int>(i * i);
    }
    return result;   // moved (or copy elided), not deep-copied
}

int main() {
    std::cout << "1) Default constructor\n";
    IntArray empty;
    empty.print("empty");

    std::cout << "\n2) Parameterised constructor\n";
    IntArray a(5, 7);
    a.print("a");

    std::cout << "\n3) Copy constructor (deep copy)\n";
    IntArray b(a);
    b.at(0) = 100;                       // changing b must NOT affect a
    a.print("a");
    b.print("b");

    std::cout << "\n4) Copy assignment\n";
    IntArray c(2, 1);
    c = a;
    c.print("c");

    std::cout << "\n5) Move constructor\n";
    IntArray d(std::move(b));            // b is left empty
    d.print("d");
    b.print("b (moved-from)");

    std::cout << "\n6) Move assignment\n";
    IntArray e;
    e = std::move(c);
    e.print("e");

    std::cout << "\n7) Returning a new object from a function\n";
    IntArray squares = makeSquares(6);
    squares.print("squares");

    std::cout << "\n8) Self-assignment safety\n";
    a = a;
    a.print("a after self-assignment");

    std::cout << "\n9) Bounds checking\n";
    try {
        std::cout << squares.at(10) << "\n";
    } catch (const std::out_of_range& ex) {
        std::cout << "  caught: " << ex.what() << "\n";
    }

    std::cout << "\nEnd of main - destructors run in reverse order:\n";
    return 0;
}

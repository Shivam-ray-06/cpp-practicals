// Practical 04 - RAII and Smart Pointers
//
// RAII (Resource Acquisition Is Initialization): a resource is acquired in a
// constructor and released in a destructor, so its lifetime follows an object's
// lifetime. Smart pointers apply this idea to heap memory.
//
//   std::unique_ptr - exactly ONE owner; cannot be copied, only moved.
//   std::shared_ptr - SHARED ownership; memory is freed when the last owner goes.

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// A resource that prints when it is created and destroyed, so ownership is visible.
class Resource {
public:
    explicit Resource(std::string name) : name_(std::move(name)) {
        std::cout << "    [acquire] " << name_ << "\n";
    }
    ~Resource() {
        std::cout << "    [release] " << name_ << "\n";
    }
    void use() const { std::cout << "    using " << name_ << "\n"; }

private:
    std::string name_;
};

// ---- Part A: unique_ptr - single ownership ----
void demoUniquePtr() {
    std::cout << "\n[A] std::unique_ptr - single owner\n";

    auto owner = std::make_unique<Resource>("database-connection");
    owner->use();

    // std::unique_ptr<Resource> copy = owner;   // compile error: not copyable

    // Ownership can be transferred with std::move.
    std::unique_ptr<Resource> newOwner = std::move(owner);
    std::cout << "    old owner is null after move: " << std::boolalpha
              << (owner == nullptr) << "\n";
    newOwner->use();

    std::cout << "    leaving scope...\n";
}   // newOwner destroyed here and the resource released automatically

// ---- Part B: shared_ptr - shared ownership ----
class Logger {
public:
    explicit Logger(std::string file) : file_(std::move(file)) {
        std::cout << "    [open log] " << file_ << "\n";
    }
    ~Logger() { std::cout << "    [close log] " << file_ << "\n"; }
    void write(const std::string& message) const {
        std::cout << "    [" << file_ << "] " << message << "\n";
    }

private:
    std::string file_;
};

class Service {
public:
    Service(std::string name, std::shared_ptr<Logger> logger)
        : name_(std::move(name)), logger_(std::move(logger)) {}
    void work() const { logger_->write(name_ + " is working"); }

private:
    std::string name_;
    std::shared_ptr<Logger> logger_;   // shares the same logger
};

void demoSharedPtr() {
    std::cout << "\n[B] std::shared_ptr - shared ownership\n";

    auto logger = std::make_shared<Logger>("app.log");
    std::cout << "    owners after creation: " << logger.use_count() << "\n";

    {
        Service orders("OrderService", logger);
        Service payments("PaymentService", logger);
        std::cout << "    owners with two services: " << logger.use_count() << "\n";
        orders.work();
        payments.work();
    }   // both services destroyed here, releasing their references

    std::cout << "    owners after services end: " << logger.use_count() << "\n";
    std::cout << "    leaving demo...\n";
}   // the last reference is dropped here, so the logger is freed

// ---- Part C: many iterations - no leaks with smart pointers ----
void demoManyIterations() {
    std::cout << "\n[C] Many iterations with unique_ptr in a vector\n";
    const int ITERATIONS = 1000;
    std::size_t totalCreated = 0;

    for (int i = 0; i < ITERATIONS; ++i) {
        std::vector<std::unique_ptr<int>> values;
        for (int j = 0; j < 10; ++j) {
            values.push_back(std::make_unique<int>(i * j));
            ++totalCreated;
        }
        // 'values' goes out of scope each loop and frees all 10 integers.
    }
    std::cout << "    allocated and freed " << totalCreated
              << " integers with no manual delete\n";
}

int main() {
    demoUniquePtr();
    demoSharedPtr();
    demoManyIterations();

    std::cout << "\nNote: raw 'new' would require a matching 'delete' on every\n"
                 "path, including when exceptions are thrown. Smart pointers\n"
                 "release memory automatically, even on those paths.\n";
    return 0;
}

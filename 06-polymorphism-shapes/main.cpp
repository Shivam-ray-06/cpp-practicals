// Practical 06 - Runtime Polymorphism and Abstract Classes
//
// Shape declares a PURE VIRTUAL area() function, which makes it abstract:
// it has no implementation and cannot be instantiated. Each derived class
// supplies its own area(). Calling area() through a Shape pointer or reference
// runs the correct derived version chosen at RUNTIME (dynamic dispatch).

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;               // virtual destructor for safe deletion via base pointer

    virtual double area() const = 0;          // PURE virtual: makes Shape abstract
    virtual std::string name() const = 0;
};

class Circle : public Shape {
    double radius_;
public:
    explicit Circle(double radius) : radius_(radius) {
        if (radius <= 0) throw std::invalid_argument("Circle radius must be positive");
    }
    double area() const override { return M_PI * radius_ * radius_; }
    std::string name() const override { return "Circle"; }
};

class Rectangle : public Shape {
    double width_;
    double height_;
public:
    Rectangle(double width, double height) : width_(width), height_(height) {
        if (width <= 0 || height <= 0) throw std::invalid_argument("Rectangle sides must be positive");
    }
    double area() const override { return width_ * height_; }
    std::string name() const override { return "Rectangle"; }
};

class Triangle : public Shape {
    double base_;
    double height_;
public:
    Triangle(double base, double height) : base_(base), height_(height) {
        if (base <= 0 || height <= 0) throw std::invalid_argument("Triangle base and height must be positive");
    }
    double area() const override { return 0.5 * base_ * height_; }
    std::string name() const override { return "Triangle"; }
};

// Works with ANY Shape - it does not need to know the concrete type.
void printArea(const Shape& shape) {
    std::cout << std::left << std::setw(10) << shape.name()
              << " area = " << std::fixed << std::setprecision(2) << shape.area() << "\n";
}

int main() {
    // Store derived objects through base-class pointers.
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 8.0));

    std::cout << "Areas calculated through the Shape interface:\n";
    double total = 0.0;
    for (const auto& shape : shapes) {
        // Same call, different behaviour - resolved at runtime.
        printArea(*shape);
        total += shape->area();
    }
    std::cout << "Total area: " << total << "\n";

    // Reference form of polymorphism.
    std::cout << "\nUsing a Shape reference:\n";
    Rectangle square(7.0, 7.0);
    const Shape& ref = square;
    printArea(ref);

    // Invalid dimensions are rejected.
    std::cout << "\nInvalid input test:\n";
    try {
        Circle bad(-2.0);
    } catch (const std::invalid_argument& ex) {
        std::cout << "  caught: " << ex.what() << "\n";
    }

    // Shape s;   // compile error: cannot instantiate abstract class 'Shape'

    std::cout << "\nExplanation:\n"
                 "  - 'virtual' lets a call through a base pointer/reference reach the derived function.\n"
                 "  - '= 0' makes area() pure virtual, so Shape is abstract and cannot be created.\n"
                 "  - The virtual destructor makes deleting through unique_ptr<Shape> safe.\n";
    return 0;
}

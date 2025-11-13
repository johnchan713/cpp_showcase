#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <format>

namespace cpp26_oop {

// ============================================================================
// BASIC CLASS - Demonstrates encapsulation with private/public members
// Usage: Basic class with constructor, methods, and member variables
// ============================================================================
class BasicClass {
private:
    int value;
    std::string name;

public:
    BasicClass(int v, std::string n) : value(v), name(std::move(n)) {}

    void display() const {
        // C++20 std::format - Modern string formatting
        std::cout << std::format("BasicClass: name='{}', value={}\n", name, value);
    }

    int getValue() const { return value; }
    const std::string& getName() const { return name; }
};

// Demonstrates basic class instantiation and usage
void demonstrate_basic_class() {
    std::cout << "\n=== BASIC CLASS ===\n";

    BasicClass obj(42, "MyObject");
    obj.display();

    // Auto type deduction
    auto value = obj.getValue();
    auto name = obj.getName();

    std::cout << std::format("Retrieved: value={}, name='{}'\n", value, name);
}

// ============================================================================
// INHERITANCE - Demonstrates single and multiple inheritance
// Usage: Shows base class, derived class, and polymorphism
// ============================================================================
class Animal {
protected:
    std::string species;

public:
    Animal(std::string s) : species(std::move(s)) {}

    virtual void speak() const {
        std::cout << "Animal speaks\n";
    }

    virtual ~Animal() = default;  // Virtual destructor for polymorphism
};

class Mammal : public Animal {
protected:
    bool hasFur;

public:
    Mammal(std::string s, bool fur) : Animal(std::move(s)), hasFur(fur) {}

    void speak() const override {
        std::cout << std::format("{} (Mammal) says: *mammal sounds*\n", species);
    }
};

class Dog : public Mammal {
private:
    std::string breed;

public:
    Dog(std::string b) : Mammal("Canine", true), breed(std::move(b)) {}

    void speak() const override {
        std::cout << std::format("Dog ({}) says: Woof!\n", breed);
    }

    void fetch() const {
        std::cout << "Dog is fetching...\n";
    }
};

// Demonstrates inheritance hierarchy and polymorphism
void demonstrate_inheritance() {
    std::cout << "\n=== INHERITANCE & POLYMORPHISM ===\n";

    Dog dog("Golden Retriever");
    dog.speak();
    dog.fetch();

    // Polymorphism
    Animal* animal_ptr = &dog;
    animal_ptr->speak();  // Calls Dog's speak() due to virtual function
}

// ============================================================================
// MULTIPLE INHERITANCE - Demonstrates inheriting from multiple base classes
// Usage: Shows diamond problem and virtual inheritance
// ============================================================================
class Flyable {
public:
    virtual void fly() const {
        std::cout << "Flying...\n";
    }
    virtual ~Flyable() = default;
};

class Swimmable {
public:
    virtual void swim() const {
        std::cout << "Swimming...\n";
    }
    virtual ~Swimmable() = default;
};

class Duck : public Animal, public Flyable, public Swimmable {
public:
    Duck() : Animal("Duck") {}

    void speak() const override {
        std::cout << "Duck says: Quack!\n";
    }

    void fly() const override {
        std::cout << "Duck is flying!\n";
    }

    void swim() const override {
        std::cout << "Duck is swimming!\n";
    }
};

// Demonstrates multiple inheritance from different base classes
void demonstrate_multiple_inheritance() {
    std::cout << "\n=== MULTIPLE INHERITANCE ===\n";

    Duck duck;
    duck.speak();
    duck.fly();
    duck.swim();
}

// ============================================================================
// ABSTRACT CLASS - Demonstrates pure virtual functions and interfaces
// Usage: Cannot instantiate abstract class, must inherit and implement
// ============================================================================
class Shape {
public:
    virtual double area() const = 0;  // Pure virtual function
    virtual double perimeter() const = 0;
    virtual void describe() const = 0;

    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }

    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }

    void describe() const override {
        std::cout << std::format("Circle: radius={:.2f}, area={:.2f}, perimeter={:.2f}\n",
                                 radius, area(), perimeter());
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }

    void describe() const override {
        std::cout << std::format("Rectangle: {}x{}, area={:.2f}, perimeter={:.2f}\n",
                                 width, height, area(), perimeter());
    }
};

// Demonstrates abstract classes and polymorphic containers
void demonstrate_abstract_class() {
    std::cout << "\n=== ABSTRACT CLASS & INTERFACE ===\n";

    // Container of polymorphic shapes
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Circle>(3.0));

    // Range-based for loop with auto
    for (const auto& shape : shapes) {
        shape->describe();
    }
}

// ============================================================================
// ENCAPSULATION - Demonstrates access modifiers and getters/setters
// Usage: Shows private, protected, public access control
// ============================================================================
class BankAccount {
private:
    std::string owner;
    double balance;
    int accountNumber;

protected:
    void logTransaction(const std::string& msg) const {
        std::cout << std::format("[LOG] {}: {}\n", accountNumber, msg);
    }

public:
    BankAccount(std::string own, int accNum)
        : owner(std::move(own)), balance(0.0), accountNumber(accNum) {}

    // Getters
    const std::string& getOwner() const { return owner; }
    double getBalance() const { return balance; }
    int getAccountNumber() const { return accountNumber; }

    // Setters with validation
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            logTransaction(std::format("Deposited ${:.2f}", amount));
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            logTransaction(std::format("Withdrew ${:.2f}", amount));
            return true;
        }
        return false;
    }

    void displayInfo() const {
        std::cout << std::format("Account #{}: Owner='{}', Balance=${:.2f}\n",
                                 accountNumber, owner, balance);
    }
};

// Demonstrates encapsulation principles and data hiding
void demonstrate_encapsulation() {
    std::cout << "\n=== ENCAPSULATION ===\n";

    BankAccount account("John Doe", 12345);
    account.deposit(1000.0);
    account.withdraw(250.0);
    account.displayInfo();
}

// ============================================================================
// OPERATOR OVERLOADING - Demonstrates custom operator behavior
// Usage: Define operators for custom types (+, -, ==, <<, etc.)
// ============================================================================
class Complex {
private:
    double real, imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Arithmetic operators
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }

    // Comparison operator
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    // Stream insertion operator (friend function)
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << std::format("{:.2f} + {:.2f}i", c.real, c.imag);
        return os;
    }

    // Unary operators
    Complex operator-() const {
        return Complex(-real, -imag);
    }

    // Compound assignment
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
};

// Demonstrates operator overloading for custom types
void demonstrate_operator_overloading() {
    std::cout << "\n=== OPERATOR OVERLOADING ===\n";

    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);

    auto c3 = c1 + c2;
    auto c4 = c1 - c2;
    auto c5 = c1 * c2;

    std::cout << "c1 = " << c1 << "\n";
    std::cout << "c2 = " << c2 << "\n";
    std::cout << "c1 + c2 = " << c3 << "\n";
    std::cout << "c1 - c2 = " << c4 << "\n";
    std::cout << "c1 * c2 = " << c5 << "\n";
    std::cout << "-c1 = " << -c1 << "\n";
}

// ============================================================================
// FRIEND FUNCTIONS - Demonstrates friend functions and classes
// Usage: Friend functions can access private members
// ============================================================================
class Box {
private:
    double width, height, depth;

public:
    Box(double w, double h, double d) : width(w), height(h), depth(d) {}

    // Friend function declaration
    friend double calculateVolume(const Box& box);
    friend class BoxPrinter;

    double getWidth() const { return width; }
};

// Friend function can access private members
double calculateVolume(const Box& box) {
    return box.width * box.height * box.depth;
}

// Friend class can access private members
class BoxPrinter {
public:
    static void print(const Box& box) {
        std::cout << std::format("Box dimensions: {}x{}x{}, Volume: {:.2f}\n",
                                 box.width, box.height, box.depth,
                                 calculateVolume(box));
    }
};

// Demonstrates friend functions and friend classes
void demonstrate_friend() {
    std::cout << "\n=== FRIEND FUNCTIONS & CLASSES ===\n";

    Box box(3.0, 4.0, 5.0);
    std::cout << "Volume via friend function: " << calculateVolume(box) << "\n";
    BoxPrinter::print(box);
}

// ============================================================================
// MOVE SEMANTICS - Demonstrates move constructors and move assignment (C++11)
// Usage: Efficiently transfer resources without copying
// ============================================================================
class BigData {
private:
    int* data;
    size_t size;

public:
    // Constructor
    BigData(size_t s) : size(s) {
        data = new int[size];
        std::cout << std::format("BigData: Allocated {} elements\n", size);
    }

    // Copy constructor
    BigData(const BigData& other) : size(other.size) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
        std::cout << std::format("BigData: Copied {} elements\n", size);
    }

    // Move constructor (C++11)
    BigData(BigData&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << std::format("BigData: Moved {} elements\n", size);
    }

    // Copy assignment
    BigData& operator=(const BigData& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "BigData: Copy assigned\n";
        }
        return *this;
    }

    // Move assignment (C++11)
    BigData& operator=(BigData&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "BigData: Move assigned\n";
        }
        return *this;
    }

    ~BigData() {
        if (data) {
            std::cout << std::format("BigData: Deallocated {} elements\n", size);
        }
        delete[] data;
    }

    size_t getSize() const { return size; }
};

// Demonstrates move semantics and perfect forwarding
void demonstrate_move_semantics() {
    std::cout << "\n=== MOVE SEMANTICS (C++11) ===\n";

    BigData bd1(1000);

    // Copy
    BigData bd2 = bd1;

    // Move
    BigData bd3 = std::move(bd1);

    std::cout << "bd1 size after move: " << bd1.getSize() << "\n";
    std::cout << "bd3 size after move: " << bd3.getSize() << "\n";
}

// ============================================================================
// RULE OF FIVE - Demonstrates the rule of five special member functions
// Usage: When you define one, you should define all five
// ============================================================================
class RuleOfFiveExample {
private:
    int* resource;

public:
    // 1. Constructor
    RuleOfFiveExample(int value = 0) : resource(new int(value)) {
        std::cout << "Constructor called\n";
    }

    // 2. Destructor
    ~RuleOfFiveExample() {
        delete resource;
        std::cout << "Destructor called\n";
    }

    // 3. Copy constructor
    RuleOfFiveExample(const RuleOfFiveExample& other)
        : resource(new int(*other.resource)) {
        std::cout << "Copy constructor called\n";
    }

    // 4. Copy assignment operator
    RuleOfFiveExample& operator=(const RuleOfFiveExample& other) {
        if (this != &other) {
            delete resource;
            resource = new int(*other.resource);
            std::cout << "Copy assignment called\n";
        }
        return *this;
    }

    // 5. Move constructor
    RuleOfFiveExample(RuleOfFiveExample&& other) noexcept
        : resource(other.resource) {
        other.resource = nullptr;
        std::cout << "Move constructor called\n";
    }

    // Move assignment operator
    RuleOfFiveExample& operator=(RuleOfFiveExample&& other) noexcept {
        if (this != &other) {
            delete resource;
            resource = other.resource;
            other.resource = nullptr;
            std::cout << "Move assignment called\n";
        }
        return *this;
    }

    int getValue() const { return resource ? *resource : 0; }
};

// Demonstrates all five special member functions
void demonstrate_rule_of_five() {
    std::cout << "\n=== RULE OF FIVE ===\n";

    RuleOfFiveExample obj1(42);
    RuleOfFiveExample obj2 = obj1;  // Copy constructor
    RuleOfFiveExample obj3(std::move(obj1));  // Move constructor

    RuleOfFiveExample obj4(100);
    obj4 = obj2;  // Copy assignment
    obj4 = std::move(obj3);  // Move assignment

    std::cout << "obj4 value: " << obj4.getValue() << "\n";
}

// ============================================================================
// CONSTRUCTORS - Default, Deleted, and Delegating
// ============================================================================
class ConstructorDemo {
private:
    int value;
    std::string name;

public:
    // Default constructor (compiler-generated)
    ConstructorDemo() = default;

    // Parameterized constructor
    ConstructorDemo(int v) : value(v), name("unnamed") {
        std::cout << "ConstructorDemo(int): value=" << value << "\n";
    }

    // Delegating constructor - delegates to another constructor
    ConstructorDemo(int v, std::string n) : ConstructorDemo(v) {
        name = std::move(n);
        std::cout << "Delegating constructor: name=" << name << "\n";
    }

    // Another delegating constructor
    ConstructorDemo(std::string n) : ConstructorDemo(0, std::move(n)) {
        std::cout << "Delegating to two-param constructor\n";
    }

    void display() const {
        std::cout << std::format("  value={}, name='{}'\n", value, name);
    }
};

// Class with deleted constructors
class NonCopyable {
private:
    int data;

public:
    NonCopyable(int d) : data(d) {
        std::cout << "NonCopyable constructor\n";
    }

    // Delete copy constructor - prevents copying
    NonCopyable(const NonCopyable&) = delete;

    // Delete copy assignment - prevents copy assignment
    NonCopyable& operator=(const NonCopyable&) = delete;

    // Default move constructor (still allows moving)
    NonCopyable(NonCopyable&&) = default;

    // Default move assignment
    NonCopyable& operator=(NonCopyable&&) = default;

    int getData() const { return data; }
};

class OnlyStackAllocated {
public:
    OnlyStackAllocated() {
        std::cout << "OnlyStackAllocated created\n";
    }

    // Delete operator new - prevents heap allocation
    void* operator new(size_t) = delete;
    void* operator new[](size_t) = delete;
};

void demonstrate_constructors() {
    std::cout << "\n=== CONSTRUCTORS (Default, Deleted, Delegating) ===\n";

    // Default constructor
    std::cout << "Using default constructor:\n";
    ConstructorDemo obj1;
    // obj1.display();  // Would show uninitialized values

    // Parameterized constructor
    std::cout << "\nUsing parameterized constructor:\n";
    ConstructorDemo obj2(42);
    obj2.display();

    // Delegating constructor
    std::cout << "\nUsing delegating constructor:\n";
    ConstructorDemo obj3(100, "MyObject");
    obj3.display();

    std::cout << "\nAnother delegating constructor:\n";
    ConstructorDemo obj4("AnotherObject");
    obj4.display();

    // Deleted constructors
    std::cout << "\nNonCopyable class:\n";
    NonCopyable nc1(42);
    // NonCopyable nc2 = nc1;  // Error: copy constructor deleted
    // NonCopyable nc3(nc1);   // Error: copy constructor deleted

    // But move is allowed
    NonCopyable nc4 = std::move(nc1);
    std::cout << "Moved value: " << nc4.getData() << "\n";

    // Deleted operator new
    std::cout << "\nOnlyStackAllocated:\n";
    OnlyStackAllocated stack_obj;
    // OnlyStackAllocated* heap_obj = new OnlyStackAllocated();  // Error: new is deleted
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_basic_class();
    demonstrate_inheritance();
    demonstrate_multiple_inheritance();
    demonstrate_abstract_class();
    demonstrate_encapsulation();
    demonstrate_operator_overloading();
    demonstrate_friend();
    demonstrate_move_semantics();
    demonstrate_rule_of_five();
    demonstrate_constructors();
}

} // namespace cpp26_oop

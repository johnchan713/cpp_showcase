#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <concepts>
#include <vector>
#include <utility>

namespace cpp26_templates {

// ============================================================================
// FUNCTION TEMPLATES
// ============================================================================
template<typename T>
T add(T a, T b) {
    return a + b;
}

// Template with multiple type parameters
template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

// Template with non-type parameter
template<typename T, size_t N>
size_t array_size(T (&)[N]) {
    return N;
}

void demonstrate_function_templates() {
    std::cout << "\n=== FUNCTION TEMPLATES ===\n";
    std::cout << "add<int>(5, 3): " << add<int>(5, 3) << "\n";
    std::cout << "add<double>(2.5, 3.7): " << add<double>(2.5, 3.7) << "\n";
    std::cout << "add with deduction: " << add(10, 20) << "\n";

    std::cout << "multiply(3, 2.5): " << multiply(3, 2.5) << "\n";

    int arr[] = {1, 2, 3, 4, 5};
    std::cout << "Array size: " << array_size(arr) << "\n";
}

// ============================================================================
// CLASS TEMPLATES
// ============================================================================
template<typename T>
class Box {
private:
    T value;
public:
    Box(T val) : value(val) {}
    T get() const { return value; }
    void set(T val) { value = val; }
};

// Template specialization
template<>
class Box<std::string> {
private:
    std::string value;
public:
    Box(std::string val) : value(std::move(val)) {}
    std::string get() const { return "[String: " + value + "]"; }
    void set(std::string val) { value = std::move(val); }
};

// Partial specialization
template<typename T>
class Box<T*> {
private:
    T* ptr;
public:
    Box(T* p) : ptr(p) {}
    T* get() const { return ptr; }
    T getValue() const { return *ptr; }
};

void demonstrate_class_templates() {
    std::cout << "\n=== CLASS TEMPLATES ===\n";

    Box<int> int_box(42);
    std::cout << "Box<int>: " << int_box.get() << "\n";

    Box<std::string> str_box("Hello");
    std::cout << "Box<std::string> (specialized): " << str_box.get() << "\n";

    int value = 100;
    Box<int*> ptr_box(&value);
    std::cout << "Box<int*> (partial specialization): " << ptr_box.getValue() << "\n";
}

// ============================================================================
// VARIADIC TEMPLATES
// ============================================================================
template<typename... Args>
void print_all(Args... args) {
    ((std::cout << args << " "), ...);  // C++17 fold expression
    std::cout << "\n";
}

template<typename T>
T sum_variadic(T t) {
    return t;
}

template<typename T, typename... Args>
T sum_variadic(T first, Args... rest) {
    return first + sum_variadic(rest...);
}

void demonstrate_variadic_templates() {
    std::cout << "\n=== VARIADIC TEMPLATES ===\n";

    print_all(1, 2.5, "hello", 'A', true);
    std::cout << "Sum: " << sum_variadic(1, 2, 3, 4, 5) << "\n";
}

// ============================================================================
// CONCEPTS (C++20)
// ============================================================================
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

template<Numeric T>
T constrained_add(T a, T b) {
    return a + b;
}

template<typename T>
requires Addable<T>
T constrained_add_requires(T a, T b) {
    return a + b;
}

// Concept with auto
auto concept_with_auto(Numeric auto x, Numeric auto y) {
    return x * y;
}

void demonstrate_concepts() {
    std::cout << "\n=== CONCEPTS (C++20) ===\n";

    std::cout << "constrained_add(5, 3): " << constrained_add(5, 3) << "\n";
    std::cout << "constrained_add(2.5, 3.7): " << constrained_add(2.5, 3.7) << "\n";

    std::cout << "concept_with_auto(4, 5): " << concept_with_auto(4, 5) << "\n";

    // This would fail to compile:
    // constrained_add(std::string("a"), std::string("b"));
}

// ============================================================================
// TEMPLATE METAPROGRAMMING - Compile-time computations
// ============================================================================

// Factorial at compile time
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// Fibonacci at compile time
template<int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

// Type traits
template<typename T>
struct RemovePointer {
    using type = T;
};

template<typename T>
struct RemovePointer<T*> {
    using type = T;
};

// SFINAE (Substitution Failure Is Not An Error)
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
sfinae_function(T t) {
    return t * 2;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
sfinae_function(T t) {
    return t * 3.0;
}

// Constexpr if (C++17)
template<typename T>
auto process_type(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return value * 3.0;
    } else {
        return value;
    }
}

void demonstrate_metaprogramming() {
    std::cout << "\n=== TEMPLATE METAPROGRAMMING ===\n";

    std::cout << "Factorial<5>: " << Factorial<5>::value << "\n";
    std::cout << "Factorial<10>: " << Factorial<10>::value << "\n";

    std::cout << "Fibonacci<10>: " << Fibonacci<10>::value << "\n";

    using IntType = RemovePointer<int*>::type;
    IntType value = 42;
    std::cout << "RemovePointer<int*>: " << value << "\n";

    std::cout << "SFINAE with int: " << sfinae_function(5) << "\n";
    std::cout << "SFINAE with double: " << sfinae_function(2.5) << "\n";

    std::cout << "constexpr if with int: " << process_type(7) << "\n";
    std::cout << "constexpr if with double: " << process_type(3.5) << "\n";
}

// ============================================================================
// CONSTEXPR and CONSTEVAL (C++20)
// ============================================================================
constexpr int constexpr_factorial(int n) {
    return (n <= 1) ? 1 : n * constexpr_factorial(n - 1);
}

consteval int consteval_square(int n) {
    return n * n;  // MUST be evaluated at compile time
}

// C++20 constinit
constinit int global_constinit = 42;

void demonstrate_constexpr_consteval() {
    std::cout << "\n=== CONSTEXPR & CONSTEVAL ===\n";

    constexpr int compile_time = constexpr_factorial(5);
    std::cout << "constexpr factorial(5): " << compile_time << "\n";

    int runtime_value = 6;
    int runtime_result = constexpr_factorial(runtime_value);
    std::cout << "constexpr factorial(6) at runtime: " << runtime_result << "\n";

    constexpr int must_compile = consteval_square(8);
    std::cout << "consteval square(8): " << must_compile << "\n";

    std::cout << "constinit global: " << global_constinit << "\n";
}

// ============================================================================
// TEMPLATE TEMPLATE PARAMETERS
// ============================================================================
template<typename T, template<typename> class Container>
class Stack {
private:
    Container<T> container;
public:
    void push(const T& value) {
        container.push_back(value);
    }
    void display() {
        for (const auto& item : container) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
};

void demonstrate_template_template_params() {
    std::cout << "\n=== TEMPLATE TEMPLATE PARAMETERS ===\n";

    Stack<int, std::vector> int_stack;
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    std::cout << "Stack contents: ";
    int_stack.display();
}

// ============================================================================
// FOLD EXPRESSIONS (C++17)
// ============================================================================
template<typename... Args>
auto sum_fold(Args... args) {
    return (args + ...);  // Unary right fold
}

template<typename... Args>
auto sum_fold_left(Args... args) {
    return (... + args);  // Unary left fold
}

template<typename... Args>
void print_with_fold(Args... args) {
    ((std::cout << args << ", "), ...) << "\n";
}

void demonstrate_fold_expressions() {
    std::cout << "\n=== FOLD EXPRESSIONS (C++17) ===\n";

    std::cout << "Sum with right fold: " << sum_fold(1, 2, 3, 4, 5) << "\n";
    std::cout << "Sum with left fold: " << sum_fold_left(10, 20, 30) << "\n";
    std::cout << "Print with fold: ";
    print_with_fold(1, "hello", 3.14, 'X');
}

// ============================================================================
// DEDUCTION GUIDES (C++17)
// ============================================================================
template<typename T>
class MyContainer {
public:
    T value;
    MyContainer(T v) : value(v) {}
};

// Deduction guide
template<typename T>
MyContainer(T) -> MyContainer<T>;

void demonstrate_deduction_guides() {
    std::cout << "\n=== DEDUCTION GUIDES (C++17) ===\n";

    MyContainer container(42);  // Deduces MyContainer<int>
    std::cout << "Deduced type container: " << container.value << "\n";

    MyContainer str_container(std::string("Hello"));
    std::cout << "Deduced string container: " << str_container.value << "\n";
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_function_templates();
    demonstrate_class_templates();
    demonstrate_variadic_templates();
    demonstrate_concepts();
    demonstrate_metaprogramming();
    demonstrate_constexpr_consteval();
    demonstrate_template_template_params();
    demonstrate_fold_expressions();
    demonstrate_deduction_guides();
}

} // namespace cpp26_templates

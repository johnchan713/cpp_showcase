#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <type_traits>

namespace cpp26_basics {

// ============================================================================
// VARIABLES - Different types and declarations
// ============================================================================
void demonstrate_variables() {
    std::cout << "\n=== VARIABLES ===\n";

    // Basic types
    int integer = 42;
    double floating = 3.14159;
    char character = 'A';
    bool boolean = true;

    // C++11 auto type deduction
    auto auto_int = 100;
    auto auto_string = std::string("Hello");

    // C++20 concepts with auto
    auto lambda = [](auto x) { return x * 2; };

    // C++26 still supports all previous standards
    decltype(auto) deduced = integer;

    std::cout << "integer: " << integer << "\n";
    std::cout << "floating: " << floating << "\n";
    std::cout << "character: " << character << "\n";
    std::cout << "boolean: " << boolean << "\n";
    std::cout << "auto_int: " << auto_int << "\n";
    std::cout << "lambda(5): " << lambda(5) << "\n";
}

// ============================================================================
// POINTERS - Raw pointers and pointer to pointer
// ============================================================================
void demonstrate_pointers() {
    std::cout << "\n=== POINTERS ===\n";

    int value = 42;
    int* ptr = &value;                    // Pointer to int
    int** ptr_to_ptr = &ptr;              // Pointer to pointer
    int*** ptr_to_ptr_to_ptr = &ptr_to_ptr; // Pointer to pointer to pointer

    std::cout << "value: " << value << "\n";
    std::cout << "ptr points to: " << *ptr << "\n";
    std::cout << "ptr_to_ptr points to: " << **ptr_to_ptr << "\n";
    std::cout << "ptr_to_ptr_to_ptr points to: " << ***ptr_to_ptr_to_ptr << "\n";

    std::cout << "Address of value: " << &value << "\n";
    std::cout << "ptr address: " << ptr << "\n";
    std::cout << "ptr_to_ptr dereferenced: " << *ptr_to_ptr << "\n";
}

// ============================================================================
// DEREFERENCING - Various dereferencing operations
// ============================================================================
void demonstrate_dereferencing() {
    std::cout << "\n=== DEREFERENCING ===\n";

    int array[5] = {1, 2, 3, 4, 5};
    int* arr_ptr = array;

    // Dereferencing array pointer
    std::cout << "First element: " << *arr_ptr << "\n";
    std::cout << "Second element: " << *(arr_ptr + 1) << "\n";
    std::cout << "Using array notation: " << arr_ptr[2] << "\n";

    // Arrow operator for dereferencing
    struct Point { int x, y; };
    Point point{10, 20};
    Point* point_ptr = &point;

    std::cout << "Point via arrow: (" << point_ptr->x << ", " << point_ptr->y << ")\n";
    std::cout << "Point via dereference: (" << (*point_ptr).x << ", " << (*point_ptr).y << ")\n";

    // Smart pointer dereferencing
    auto smart_ptr = std::make_unique<int>(100);
    std::cout << "Smart pointer value: " << *smart_ptr << "\n";
}

// ============================================================================
// CASTING - All C++ casting types
// ============================================================================
void demonstrate_casting() {
    std::cout << "\n=== CASTING ===\n";

    // static_cast - compile-time type conversion
    double d = 3.14159;
    int i = static_cast<int>(d);
    std::cout << "static_cast double to int: " << d << " -> " << i << "\n";

    // dynamic_cast - runtime polymorphic casting
    class Base { public: virtual ~Base() = default; };
    class Derived : public Base { public: void derived_method() {} };

    Base* base_ptr = new Derived();
    Derived* derived_ptr = dynamic_cast<Derived*>(base_ptr);
    if (derived_ptr) {
        std::cout << "dynamic_cast successful\n";
    }
    delete base_ptr;

    // const_cast - remove/add const qualifier
    const int const_val = 42;
    int* modifiable = const_cast<int*>(&const_val);
    std::cout << "const_cast value: " << *modifiable << "\n";

    // reinterpret_cast - low-level reinterpretation
    long long address = reinterpret_cast<long long>(&i);
    std::cout << "reinterpret_cast address: 0x" << std::hex << address << std::dec << "\n";

    // C-style cast (avoid in modern C++)
    float f = (float)d;
    std::cout << "C-style cast: " << f << "\n";
}

// ============================================================================
// INLINE - Inline functions
// ============================================================================
inline int inline_add(int a, int b) {
    return a + b;
}

inline constexpr int inline_constexpr_multiply(int a, int b) {
    return a * b;
}

// Inline variable (C++17) at namespace scope
inline int inline_var = 42;

void demonstrate_inline() {
    std::cout << "\n=== INLINE FUNCTIONS ===\n";
    std::cout << "inline_add(5, 3): " << inline_add(5, 3) << "\n";
    std::cout << "inline_constexpr_multiply(4, 7): " << inline_constexpr_multiply(4, 7) << "\n";

    // Inline variable (C++17)
    std::cout << "Inline variable: " << inline_var << "\n";
}

// ============================================================================
// STATIC - Static variables and members
// ============================================================================

// Class with static members
class StaticExample {
public:
    static inline int static_member = 0;  // C++17 inline static
    static int static_method() { return static_member * 2; }
};

void demonstrate_static() {
    std::cout << "\n=== STATIC ===\n";

    // Static local variable
    auto counter_function = []() {
        static int count = 0;
        return ++count;
    };

    std::cout << "Call 1: " << counter_function() << "\n";
    std::cout << "Call 2: " << counter_function() << "\n";
    std::cout << "Call 3: " << counter_function() << "\n";

    // Static class member
    StaticExample::static_member = 25;
    std::cout << "Static member: " << StaticExample::static_member << "\n";
    std::cout << "Static method: " << StaticExample::static_method() << "\n";
}

// ============================================================================
// VOLATILE - Volatile keyword
// ============================================================================
void demonstrate_volatile() {
    std::cout << "\n=== VOLATILE ===\n";

    volatile int volatile_var = 10;
    std::cout << "Volatile variable (prevents optimization): " << volatile_var << "\n";

    // Volatile prevents compiler from optimizing away reads/writes
    // Useful for memory-mapped hardware registers, signal handlers
    volatile_var = 20;
    std::cout << "After modification: " << volatile_var << "\n";

    // Volatile pointer
    volatile int* volatile_ptr = const_cast<int*>(&volatile_var);
    std::cout << "Via volatile pointer: " << *volatile_ptr << "\n";
}

// ============================================================================
// COMPILER HINTS - [[attributes]] and other hints
// ============================================================================
[[nodiscard]] int function_with_nodiscard() {
    return 42;
}

[[maybe_unused]] void function_maybe_unused([[maybe_unused]] int param) {
    // Function or parameter might not be used
}

[[deprecated("Use new_function() instead")]]
void old_function() {
    std::cout << "This is deprecated\n";
}

[[noreturn]] void function_no_return() {
    std::terminate();
}

// C++20 [[likely]] and [[unlikely]]
int process_with_hints(int value) {
    if (value > 0) [[likely]] {
        return value * 2;
    } else [[unlikely]] {
        return -1;
    }
}

// C++20 [[no_unique_address]]
struct Empty {};
struct WithNoUniqueAddress {
    [[no_unique_address]] Empty e;
    int value;
};

void demonstrate_hints() {
    std::cout << "\n=== COMPILER HINTS (Attributes) ===\n";

    int result = function_with_nodiscard();  // [[nodiscard]] warns if unused
    std::cout << "[[nodiscard]] function result: " << result << "\n";

    function_maybe_unused(10);  // [[maybe_unused]] suppresses warnings

    // old_function();  // Would show deprecation warning

    std::cout << "[[likely]]/[[unlikely]] result: " << process_with_hints(5) << "\n";

    std::cout << "Size with [[no_unique_address]]: " << sizeof(WithNoUniqueAddress) << "\n";
    std::cout << "Size of int: " << sizeof(int) << "\n";

    // C++23 [[assume]]
    int x = 10;
    [[assume(x > 0)]];  // Tells compiler to assume this condition
    std::cout << "Used [[assume]] attribute for optimization\n";
}

// ============================================================================
// REFERENCE TYPES
// ============================================================================
void demonstrate_references() {
    std::cout << "\n=== REFERENCES ===\n";

    int value = 42;
    int& ref = value;           // Lvalue reference
    const int& const_ref = value;  // Const lvalue reference

    std::cout << "Original value: " << value << "\n";
    ref = 100;
    std::cout << "After ref modification: " << value << "\n";

    // Rvalue reference (C++11)
    int&& rvalue_ref = 42;
    std::cout << "Rvalue reference: " << rvalue_ref << "\n";

    // Forwarding reference (universal reference)
    auto&& forwarding_ref = value;
    std::cout << "Forwarding reference: " << forwarding_ref << "\n";
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_variables();
    demonstrate_pointers();
    demonstrate_dereferencing();
    demonstrate_casting();
    demonstrate_inline();
    demonstrate_static();
    demonstrate_volatile();
    demonstrate_hints();
    demonstrate_references();
}

} // namespace cpp26_basics

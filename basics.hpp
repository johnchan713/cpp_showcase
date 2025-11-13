#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <type_traits>
#include <utility>
#include <tuple>
#include <functional>

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
// PAIR AND TUPLE - Utility types for grouping values
// ============================================================================
void demonstrate_pair_and_tuple() {
    std::cout << "\n=== PAIR & TUPLE ===\n";

    // std::pair - holds two values
    std::pair<int, std::string> p1(42, "Answer");
    std::cout << "Pair: (" << p1.first << ", " << p1.second << ")\n";

    // make_pair - creates pair with type deduction
    auto p2 = std::make_pair(3.14, "Pi");
    std::cout << "make_pair: (" << p2.first << ", " << p2.second << ")\n";

    // Structured bindings (C++17)
    auto [num, str] = p1;
    std::cout << "Structured binding: num=" << num << ", str=" << str << "\n";

    // std::tuple - holds multiple values of different types
    std::tuple<int, double, std::string> t1(1, 2.5, "tuple");
    std::cout << "Tuple: (" << std::get<0>(t1) << ", "
              << std::get<1>(t1) << ", " << std::get<2>(t1) << ")\n";

    // make_tuple - creates tuple with type deduction
    auto t2 = std::make_tuple(100, 3.14159, "pi", 'x');
    std::cout << "make_tuple size: " << std::tuple_size<decltype(t2)>::value << "\n";

    // Structured bindings with tuple
    auto [a, b, c] = t1;
    std::cout << "Tuple structured binding: a=" << a << ", b=" << b << ", c=" << c << "\n";

    // tie - unpacks values
    int x;
    double y;
    std::string z;
    std::tie(x, y, z) = t1;
    std::cout << "tie unpacked: x=" << x << ", y=" << y << ", z=" << z << "\n";

    // ignore - skip values when unpacking
    std::tie(x, std::ignore, z) = t1;
    std::cout << "tie with ignore: x=" << x << ", z=" << z << "\n";
}

// ============================================================================
// IMPLICIT CONVERSIONS - Automatic type conversions
// ============================================================================
class ImplicitConverter {
private:
    int value;

public:
    // Implicit conversion from int
    ImplicitConverter(int v) : value(v) {
        std::cout << "  Implicit conversion from int: " << v << "\n";
    }

    // Explicit conversion prevents implicit conversion
    explicit ImplicitConverter(double d) : value(static_cast<int>(d)) {
        std::cout << "  Explicit conversion from double: " << d << "\n";
    }

    // Conversion operator - allows implicit conversion TO int
    operator int() const {
        std::cout << "  Converting to int\n";
        return value;
    }

    int getValue() const { return value; }
};

void demonstrate_implicit_conversions() {
    std::cout << "\n=== IMPLICIT CONVERSIONS ===\n";

    // Implicit conversion from int
    ImplicitConverter ic1 = 42;  // Calls ImplicitConverter(int)

    // Explicit keyword prevents implicit conversion from double
    // ImplicitConverter ic2 = 3.14;  // Error: would require explicit
    ImplicitConverter ic2(3.14);     // OK: direct initialization

    // Implicit conversion TO int via conversion operator
    int val = ic1;  // Calls operator int()
    std::cout << "Converted value: " << val << "\n";

    // Standard implicit conversions
    int i = 42;
    double d = i;  // Implicit int to double
    std::cout << "int to double: " << i << " -> " << d << "\n";

    double d2 = 3.14159;
    int i2 = static_cast<int>(d2);  // Explicit (narrowing prevented implicitly)
    std::cout << "double to int (explicit): " << d2 << " -> " << i2 << "\n";

    // Pointer conversions
    int* ptr = &i;
    void* void_ptr = ptr;  // Implicit pointer to void*
    std::cout << "Pointer to void*: OK\n";
}

// ============================================================================
// IF/SWITCH WITH INITIALIZER (C++17)
// ============================================================================
void demonstrate_if_switch_init() {
    std::cout << "\n=== IF/SWITCH WITH INITIALIZER (C++17) ===\n";

    // If with initializer - variable scope limited to if block
    if (auto val = 42; val > 10) {
        std::cout << "if-init: val=" << val << " is greater than 10\n";
    }
    // val not accessible here

    // Useful for checking map insertion/lookup
    std::pair<int, std::string> data = {100, "test"};
    if (auto [key, value] = data; key > 50) {
        std::cout << "if-init with structured binding: key=" << key
                  << ", value=" << value << "\n";
    }

    // Switch with initializer (C++17)
    switch (auto choice = 2; choice) {
        case 1:
            std::cout << "switch-init: choice is 1\n";
            break;
        case 2:
            std::cout << "switch-init: choice is 2\n";
            break;
        default:
            std::cout << "switch-init: default case\n";
            break;
    }
    // choice not accessible here

    // Practical example with switch-init
    enum class Status { OK, ERROR, PENDING };
    switch (auto status = Status::OK; status) {
        case Status::OK:
            std::cout << "Status: OK\n";
            break;
        case Status::ERROR:
            std::cout << "Status: ERROR\n";
            break;
        case Status::PENDING:
            std::cout << "Status: PENDING\n";
            break;
    }
}

// ============================================================================
// FUNCTION POINTERS
// ============================================================================
int add_func(int a, int b) { return a + b; }
int multiply_func(int a, int b) { return a * b; }
int subtract_func(int a, int b) { return a - b; }

void demonstrate_function_pointers() {
    std::cout << "\n=== FUNCTION POINTERS ===\n";

    // Basic function pointer
    int (*func_ptr)(int, int) = add_func;
    std::cout << "Function pointer result: " << func_ptr(5, 3) << "\n";

    // Change function pointer target
    func_ptr = multiply_func;
    std::cout << "Changed to multiply: " << func_ptr(5, 3) << "\n";

    // Array of function pointers
    int (*operations[])(int, int) = {add_func, subtract_func, multiply_func};
    std::cout << "operations[0](10, 5) = " << operations[0](10, 5) << "\n";
    std::cout << "operations[1](10, 5) = " << operations[1](10, 5) << "\n";
    std::cout << "operations[2](10, 5) = " << operations[2](10, 5) << "\n";

    // Using type alias for readability
    using BinaryOp = int(*)(int, int);
    BinaryOp op = add_func;
    std::cout << "Type alias: " << op(7, 3) << "\n";

    // Function pointer as parameter
    auto execute = [](int a, int b, int (*operation)(int, int)) {
        return operation(a, b);
    };
    std::cout << "Passed as parameter: " << execute(6, 4, subtract_func) << "\n";
}

// ============================================================================
// STD::REF and STD::CREF - Reference wrappers
// ============================================================================
void modify_value(int& x) {
    x *= 2;
}

void demonstrate_ref() {
    std::cout << "\n=== STD::REF & STD::CREF ===\n";

    int value = 10;
    std::cout << "Original value: " << value << "\n";

    // std::ref creates a reference wrapper
    auto ref_wrapper = std::ref(value);
    ref_wrapper.get() = 20;
    std::cout << "After ref_wrapper modification: " << value << "\n";

    // Useful with threads and algorithms that copy parameters
    value = 30;
    modify_value(ref_wrapper);
    std::cout << "After modify_value: " << value << "\n";

    // std::cref creates a const reference wrapper
    const int const_value = 100;
    auto cref_wrapper = std::cref(const_value);
    std::cout << "cref_wrapper value: " << cref_wrapper.get() << "\n";

    // Practical use: passing references to std::bind or std::thread
    auto bound_func = std::bind(modify_value, std::ref(value));
    bound_func();
    std::cout << "After bound function with std::ref: " << value << "\n";

    // Type deduction with reference_wrapper
    std::reference_wrapper<int> ref_wrap = value;
    ref_wrap.get() = 100;
    std::cout << "Final value: " << value << "\n";
}

// ============================================================================
// STATIC_ASSERT - Compile-time assertions
// ============================================================================
void demonstrate_static_assert() {
    std::cout << "\n=== STATIC_ASSERT ===\n";

    // Basic static_assert
    static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
    std::cout << "static_assert: sizeof(int) >= 4 passed\n";

    // C++17 static_assert without message
    static_assert(sizeof(void*) >= sizeof(int));
    std::cout << "static_assert: sizeof(void*) >= sizeof(int) passed\n";

    // Type trait checks
    static_assert(std::is_integral_v<int>, "int must be integral type");
    static_assert(std::is_pointer_v<int*>, "int* must be pointer type");
    static_assert(!std::is_const_v<int>, "int must not be const");

    std::cout << "All static_assert checks passed at compile time\n";

    // Template with static_assert
    auto check_type = []<typename T>(T value) {
        static_assert(std::is_arithmetic_v<T>, "Type must be arithmetic");
        std::cout << "Value: " << value << " (arithmetic type)\n";
    };

    check_type(42);
    check_type(3.14);
    // check_type("string");  // Would fail at compile time
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
    demonstrate_pair_and_tuple();
    demonstrate_implicit_conversions();
    demonstrate_if_switch_init();
    demonstrate_function_pointers();
    demonstrate_ref();
    demonstrate_static_assert();
}

} // namespace cpp26_basics

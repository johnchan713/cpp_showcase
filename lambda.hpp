#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <format>
#include <memory>

namespace cpp26_lambda {

// ============================================================================
// LAMBDA EXPRESSIONS - Anonymous functions (C++11 and beyond)
// Reference: https://en.cppreference.com/w/cpp/language/lambda
// ============================================================================

// ============================================================================
// BASIC LAMBDAS
// ============================================================================
void demonstrate_basic_lambdas() {
    std::cout << "\n=== BASIC LAMBDAS ===\n";

    // Simplest lambda
    auto hello = []() {
        std::cout << "Hello from lambda!\n";
    };
    hello();

    // Lambda with parameters
    auto add = [](int a, int b) {
        return a + b;
    };
    std::cout << std::format("add(5, 3) = {}\n", add(5, 3));

    // Lambda with explicit return type
    auto divide = [](double a, double b) -> double {
        return b != 0 ? a / b : 0;
    };
    std::cout << std::format("divide(10, 3) = {:.2f}\n", divide(10, 3));

    // Immediately invoked lambda
    int result = [](int x) { return x * x; }(5);
    std::cout << std::format("Immediately invoked lambda: {}\n", result);
}

// ============================================================================
// CAPTURE MODES - [=], [&], [this], [*this]
// ============================================================================
void demonstrate_capture_modes() {
    std::cout << "\n=== CAPTURE MODES ===\n";

    int x = 10;
    int y = 20;

    // Capture by value [=]
    auto capture_by_value = [=]() {
        std::cout << std::format("Captured by value: x={}, y={}\n", x, y);
    };
    capture_by_value();

    // Capture by reference [&]
    auto capture_by_ref = [&]() {
        x += 5;
        y += 5;
        std::cout << std::format("Modified via reference: x={}, y={}\n", x, y);
    };
    capture_by_ref();
    std::cout << std::format("After lambda: x={}, y={}\n", x, y);

    // Selective capture
    int a = 1, b = 2, c = 3;
    auto selective = [a, &b, c]() mutable {
        a++;  // OK because mutable
        b++;  // Modifies original
        std::cout << std::format("Selective: a={}, b={}, c={}\n", a, b, c);
    };
    selective();
    std::cout << std::format("After selective: a={}, b={}, c={}\n", a, b, c);

    // Mixed capture
    auto mixed = [=, &y]() {
        std::cout << std::format("Mixed: x={} (copy), y={} (ref)\n", x, y);
    };
    mixed();

    // Initialize captures (C++14)
    auto init_capture = [z = 42, ptr = std::make_unique<int>(100)]() {
        std::cout << std::format("Init capture: z={}, ptr={}\n", z, *ptr);
    };
    init_capture();
}

// ============================================================================
// MUTABLE LAMBDAS
// ============================================================================
void demonstrate_mutable_lambdas() {
    std::cout << "\n=== MUTABLE LAMBDAS ===\n";

    int count = 0;

    // Non-mutable (can't modify captured value)
    auto counter = [count]() {
        // count++; // Error: cannot modify captured value
        std::cout << std::format("Count: {}\n", count);
    };

    // Mutable lambda
    auto mutable_counter = [count]() mutable {
        count++;  // OK with mutable
        std::cout << std::format("Mutable count: {}\n", count);
        return count;
    };

    std::cout << "Call 1: "; mutable_counter();
    std::cout << "Call 2: "; mutable_counter();
    std::cout << "Call 3: "; mutable_counter();
    std::cout << std::format("Original count unchanged: {}\n", count);
}

// ============================================================================
// GENERIC LAMBDAS (C++14)
// ============================================================================
void demonstrate_generic_lambdas() {
    std::cout << "\n=== GENERIC LAMBDAS (C++14) ===\n";

    // auto parameters
    auto print = [](auto x) {
        std::cout << x << " ";
    };

    print(42);
    print(3.14);
    print("hello");
    std::cout << "\n";

    // Generic binary operation
    auto multiply = [](auto a, auto b) {
        return a * b;
    };

    std::cout << std::format("multiply(5, 3) = {}\n", multiply(5, 3));
    std::cout << std::format("multiply(2.5, 4.0) = {:.1f}\n", multiply(2.5, 4.0));

    // Template lambda (C++20)
    auto templated = []<typename T>(T a, T b) {
        return a + b;
    };
    std::cout << std::format("templated(10, 20) = {}\n", templated(10, 20));
}

// ============================================================================
// VARIADIC LAMBDAS
// ============================================================================
void demonstrate_variadic_lambdas() {
    std::cout << "\n=== VARIADIC LAMBDAS ===\n";

    // Variadic generic lambda
    auto print_all = [](auto&&... args) {
        ((std::cout << args << " "), ...);  // Fold expression
        std::cout << "\n";
    };

    print_all(1, 2, 3);
    print_all("Hello", "World", "!");
    print_all(1, 2.5, "mixed", 'X');

    // Sum variadic
    auto sum = [](auto... args) {
        return (args + ...);
    };
    std::cout << std::format("sum(1, 2, 3, 4, 5) = {}\n", sum(1, 2, 3, 4, 5));
}

// ============================================================================
// LAMBDA WITH std::function
// ============================================================================
void demonstrate_std_function() {
    std::cout << "\n=== LAMBDA WITH std::function ===\n";

    // Store lambda in std::function
    std::function<int(int, int)> add = [](int a, int b) {
        return a + b;
    };
    std::cout << std::format("add(10, 20) = {}\n", add(10, 20));

    // Function that takes lambda as parameter
    auto apply = [](std::function<int(int)> func, int value) {
        return func(value);
    };

    std::cout << std::format("apply(square, 5) = {}\n",
        apply([](int x) { return x * x; }, 5));
    std::cout << std::format("apply(double, 5) = {}\n",
        apply([](int x) { return x * 2; }, 5));
}

// ============================================================================
// LAMBDAS WITH ALGORITHMS
// ============================================================================
void demonstrate_lambdas_with_algorithms() {
    std::cout << "\n=== LAMBDAS WITH ALGORITHMS ===\n";

    std::vector<int> vec = {5, 2, 8, 1, 9, 3, 7};

    // Sort with lambda
    std::sort(vec.begin(), vec.end(), [](int a, int b) {
        return a > b;  // Descending order
    });
    std::cout << "Sorted descending: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // Find with lambda
    auto it = std::find_if(vec.begin(), vec.end(), [](int x) {
        return x > 5;
    });
    if (it != vec.end()) {
        std::cout << std::format("First element > 5: {}\n", *it);
    }

    // Count with lambda
    int count = std::count_if(vec.begin(), vec.end(), [](int x) {
        return x % 2 == 0;
    });
    std::cout << std::format("Even numbers: {}\n", count);

    // Transform with lambda
    std::vector<int> doubled;
    std::transform(vec.begin(), vec.end(), std::back_inserter(doubled),
        [](int x) { return x * 2; });
    std::cout << "Doubled: ";
    for (auto x : doubled) std::cout << x << " ";
    std::cout << "\n";
}

// ============================================================================
// RECURSIVE LAMBDAS
// ============================================================================
void demonstrate_recursive_lambdas() {
    std::cout << "\n=== RECURSIVE LAMBDAS ===\n";

    // Recursive lambda using std::function
    std::function<int(int)> factorial = [&factorial](int n) {
        return n <= 1 ? 1 : n * factorial(n - 1);
    };
    std::cout << std::format("factorial(5) = {}\n", factorial(5));

    // Fibonacci with Y-combinator style
    auto fib = [](auto&& self, int n) -> int {
        return n <= 1 ? n : self(self, n - 1) + self(self, n - 2);
    };
    std::cout << std::format("fibonacci(10) = {}\n", fib(fib, 10));
}

// ============================================================================
// LAMBDA IN CLASS CONTEXT
// ============================================================================
class LambdaExample {
private:
    int value;

public:
    LambdaExample(int v) : value(v) {}

    void demonstrate_this_capture() {
        std::cout << "\n=== LAMBDA CAPTURING 'this' ===\n";

        // Capture this by reference
        auto lambda_this = [this]() {
            std::cout << std::format("Captured this->value: {}\n", value);
            value += 10;
        };
        lambda_this();
        std::cout << std::format("After modification: {}\n", value);

        // Capture this by copy (C++17)
        auto lambda_copy = [*this]() mutable {
            value += 100;
            std::cout << std::format("Copy modified: {}\n", value);
        };
        lambda_copy();
        std::cout << std::format("Original unchanged: {}\n", value);
    }
};

void demonstrate_class_lambdas() {
    LambdaExample example(42);
    example.demonstrate_this_capture();
}

// ============================================================================
// CONSTEXPR LAMBDAS (C++17)
// ============================================================================
void demonstrate_constexpr_lambdas() {
    std::cout << "\n=== CONSTEXPR LAMBDAS (C++17) ===\n";

    constexpr auto square = [](int x) constexpr {
        return x * x;
    };

    constexpr int result = square(5);
    std::cout << std::format("constexpr square(5) = {}\n", result);

    // Can be used in constant expressions
    std::array<int, square(3)> arr;
    std::cout << std::format("Array size from constexpr lambda: {}\n", arr.size());
}

// ============================================================================
// LAMBDA WITH ATTRIBUTES (C++23)
// ============================================================================
void demonstrate_lambda_attributes() {
    std::cout << "\n=== LAMBDA ATTRIBUTES ===\n";

    // [[maybe_unused]] lambda
    [[maybe_unused]] auto unused_lambda = []() {
        return "not used";
    };
    std::cout << "Lambdas can have attributes like [[maybe_unused]]\n";

    // Note: [[nodiscard]] on lambdas requires newer compiler support (C++23)
    // Example (not available in GCC 13.3):
    // auto get_value = []() [[nodiscard]] { return 42; };

    auto get_value = []() {
        return 42;
    };
    int val = get_value();
    std::cout << std::format("Lambda returned: {}\n", val);
}

// ============================================================================
// PERFECT FORWARDING IN LAMBDAS
// ============================================================================
void demonstrate_perfect_forwarding() {
    std::cout << "\n=== PERFECT FORWARDING IN LAMBDAS ===\n";

    auto forward_print = [](auto&& arg) {
        std::cout << std::format("Forwarded: {}\n", std::forward<decltype(arg)>(arg));
    };

    int x = 42;
    forward_print(x);           // lvalue
    forward_print(100);         // rvalue
    forward_print("hello");     // rvalue
}

// ============================================================================
// PRACTICAL EXAMPLES
// ============================================================================
void demonstrate_practical_examples() {
    std::cout << "\n=== PRACTICAL EXAMPLES ===\n";

    // Event handler
    std::vector<std::function<void()>> event_handlers;

    event_handlers.push_back([]() { std::cout << "Handler 1\n"; });
    event_handlers.push_back([]() { std::cout << "Handler 2\n"; });
    event_handlers.push_back([]() { std::cout << "Handler 3\n"; });

    std::cout << "Triggering events:\n";
    for (auto& handler : event_handlers) {
        handler();
    }

    // Custom comparator
    struct Person {
        std::string name;
        int age;
    };

    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };

    std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
        return a.age < b.age;
    });

    std::cout << "\nPeople sorted by age:\n";
    for (const auto& p : people) {
        std::cout << std::format("  {}: {}\n", p.name, p.age);
    }

    // Filter and transform pipeline
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto pipeline = [](const std::vector<int>& input) {
        std::vector<int> result;
        std::copy_if(input.begin(), input.end(), std::back_inserter(result),
            [](int x) { return x % 2 == 0; });  // Filter evens
        std::transform(result.begin(), result.end(), result.begin(),
            [](int x) { return x * x; });  // Square them
        return result;
    };

    auto processed = pipeline(numbers);
    std::cout << "\nEvens squared: ";
    for (auto x : processed) std::cout << x << " ";
    std::cout << "\n";
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_basic_lambdas();
    demonstrate_capture_modes();
    demonstrate_mutable_lambdas();
    demonstrate_generic_lambdas();
    demonstrate_variadic_lambdas();
    demonstrate_std_function();
    demonstrate_lambdas_with_algorithms();
    demonstrate_recursive_lambdas();
    demonstrate_class_lambdas();
    demonstrate_constexpr_lambdas();
    demonstrate_lambda_attributes();
    demonstrate_perfect_forwarding();
    demonstrate_practical_examples();
}

} // namespace cpp26_lambda

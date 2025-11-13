#pragma once

#include <iostream>
#include <format>

// ============================================================================
// PREPROCESSOR DIRECTIVES - Compile-time text processing
// Reference: https://en.cppreference.com/w/cpp/preprocessor
// ============================================================================

// ============================================================================
// MACRO DEFINITIONS - #define
// ============================================================================

// Object-like macros
#define PI 3.14159265359
#define MAX_BUFFER_SIZE 1024
#define VERSION "1.0.0"

// Function-like macros
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Multi-line macros with backslash continuation
#define PRINT_VAR(var) \
    std::cout << #var << " = " << (var) << "\n"

// Stringification operator (#)
#define TO_STRING(x) #x
#define STRINGIFY(x) TO_STRING(x)

// Token pasting operator (##)
#define CONCAT(a, b) a##b
#define VAR_NAME(prefix, suffix) prefix##_##suffix

// Variadic macros (C++11)
#define LOG(...) std::cout << std::format(__VA_ARGS__) << "\n"
#define DEBUG_PRINT(fmt, ...) \
    std::cout << "[DEBUG] " << std::format(fmt, ##__VA_ARGS__) << "\n"

namespace cpp26_preprocessor {

void demonstrate_macros() {
    std::cout << "\n=== PREPROCESSOR MACROS ===\n";

    // Object-like macros
    std::cout << std::format("PI = {}\n", PI);
    std::cout << std::format("MAX_BUFFER_SIZE = {}\n", MAX_BUFFER_SIZE);
    std::cout << std::format("VERSION = {}\n", VERSION);

    // Function-like macros
    int x = 5;
    std::cout << std::format("SQUARE(5) = {}\n", SQUARE(x));
    std::cout << std::format("MAX(10, 20) = {}\n", MAX(10, 20));
    std::cout << std::format("MIN(10, 20) = {}\n", MIN(10, 20));

    // Stringification
    std::cout << std::format("TO_STRING(Hello) = '{}'\n", TO_STRING(Hello));
    std::cout << std::format("STRINGIFY(123) = '{}'\n", STRINGIFY(123));

    // Token pasting
    int CONCAT(value, 1) = 100;
    int CONCAT(value, 2) = 200;
    std::cout << std::format("value1 = {}, value2 = {}\n", value1, value2);

    // Variable name generation
    int VAR_NAME(test, var) = 42;
    std::cout << std::format("test_var = {}\n", test_var);

    // Variadic macros
    LOG("Simple log message");
    LOG("Formatted: {}, {}", 42, "hello");
    DEBUG_PRINT("Debug value: {}", 99);
}

// ============================================================================
// CONDITIONAL COMPILATION - #if, #ifdef, #ifndef, #else, #elif, #endif
// ============================================================================

#define DEBUG_MODE 1
#define FEATURE_ENABLED
#define PLATFORM_LINUX

void demonstrate_conditional_compilation() {
    std::cout << "\n=== CONDITIONAL COMPILATION ===\n";

    // #ifdef / #ifndef
#ifdef DEBUG_MODE
    std::cout << "DEBUG_MODE is defined\n";
#endif

#ifndef RELEASE_MODE
    std::cout << "RELEASE_MODE is not defined\n";
#endif

    // #if defined()
#if defined(FEATURE_ENABLED)
    std::cout << "FEATURE_ENABLED is defined\n";
#endif

    // #if with expressions
#if DEBUG_MODE == 1
    std::cout << "DEBUG_MODE == 1\n";
#endif

    // #elif for multiple conditions
#if defined(PLATFORM_WINDOWS)
    std::cout << "Platform: Windows\n";
#elif defined(PLATFORM_LINUX)
    std::cout << "Platform: Linux\n";
#elif defined(PLATFORM_MAC)
    std::cout << "Platform: macOS\n";
#else
    std::cout << "Platform: Unknown\n";
#endif

    // Complex conditions
#if defined(DEBUG_MODE) && DEBUG_MODE > 0
    std::cout << "Debug mode is active\n";
#endif

#if !defined(NDEBUG)
    std::cout << "Assertions are enabled\n";
#endif
}

// ============================================================================
// PREDEFINED MACROS - Compiler-provided macros
// ============================================================================

void demonstrate_predefined_macros() {
    std::cout << "\n=== PREDEFINED MACROS ===\n";

    // Standard predefined macros
    std::cout << std::format("__FILE__ = {}\n", __FILE__);
    std::cout << std::format("__LINE__ = {}\n", __LINE__);
    std::cout << std::format("__DATE__ = {}\n", __DATE__);
    std::cout << std::format("__TIME__ = {}\n", __TIME__);

#ifdef __cplusplus
    std::cout << std::format("__cplusplus = {}\n", __cplusplus);
#endif

#ifdef __STDC_HOSTED__
    std::cout << std::format("__STDC_HOSTED__ = {}\n", __STDC_HOSTED__);
#endif

    // Function name macros
    std::cout << std::format("__func__ = {}\n", __func__);

#ifdef __PRETTY_FUNCTION__
    std::cout << std::format("__PRETTY_FUNCTION__ = {}\n", __PRETTY_FUNCTION__);
#endif

    // Compiler identification
#ifdef __GNUC__
    std::cout << std::format("GCC version: {}.{}.{}\n",
        __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

#ifdef __clang__
    std::cout << std::format("Clang version: {}.{}.{}\n",
        __clang_major__, __clang_minor__, __clang_patchlevel__);
#endif

#ifdef _MSC_VER
    std::cout << std::format("MSVC version: {}\n", _MSC_VER);
#endif

    // Platform identification
#ifdef __linux__
    std::cout << "Platform: Linux\n";
#elif defined(_WIN32)
    std::cout << "Platform: Windows\n";
#elif defined(__APPLE__)
    std::cout << "Platform: macOS\n";
#endif

    // Architecture
#ifdef __x86_64__
    std::cout << "Architecture: x86_64\n";
#elif defined(__i386__)
    std::cout << "Architecture: x86\n";
#elif defined(__arm__)
    std::cout << "Architecture: ARM\n";
#elif defined(__aarch64__)
    std::cout << "Architecture: ARM64\n";
#endif
}

// ============================================================================
// #pragma DIRECTIVES
// ============================================================================

void demonstrate_pragma_directives() {
    std::cout << "\n=== #pragma DIRECTIVES ===\n";

    // #pragma once - include guard (shown at top of file)
    std::cout << "This file uses #pragma once\n";

    // Suppress specific warnings (compiler-specific)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
    [[maybe_unused]] int unused_var = 42;
#pragma GCC diagnostic pop

    std::cout << "Demonstrated warning suppression\n";

    // #pragma message - compile-time message
#pragma message("Compilation message: This is a custom build")

    // Pack structures (compiler-specific)
#pragma pack(push, 1)
    struct PackedStruct {
        char c;
        int i;
    };
#pragma pack(pop)

    std::cout << std::format("PackedStruct size: {}\n", sizeof(PackedStruct));
}

// ============================================================================
// INCLUDE GUARDS vs #pragma once
// ============================================================================

// Traditional include guard:
// #ifndef HEADER_NAME_H
// #define HEADER_NAME_H
// ... content ...
// #endif

// Modern #pragma once:
// #pragma once (shown at top of this file)

void demonstrate_include_guards() {
    std::cout << "\n=== INCLUDE GUARDS ===\n";
    std::cout << "This file uses #pragma once\n";
    std::cout << "Traditional guards use: #ifndef, #define, #endif\n";
    std::cout << "#pragma once is simpler and faster\n";
}

// ============================================================================
// MACRO PITFALLS AND BEST PRACTICES
// ============================================================================

// Bad: No parentheses
#define BAD_SQUARE(x) x * x

// Good: Proper parentheses
#define GOOD_SQUARE(x) ((x) * (x))

// Bad: Side effects
#define BAD_MAX(a, b) ((a) > (b) ? (a) : (b))

void demonstrate_macro_pitfalls() {
    std::cout << "\n=== MACRO PITFALLS ===\n";

    // Problem with no parentheses
    int bad_result = BAD_SQUARE(2 + 3);  // Expands to: 2 + 3 * 2 + 3 = 11
    int good_result = GOOD_SQUARE(2 + 3);  // Expands to: ((2 + 3) * (2 + 3)) = 25
    std::cout << std::format("BAD_SQUARE(2+3) = {} (wrong!)\n", bad_result);
    std::cout << std::format("GOOD_SQUARE(2+3) = {} (correct)\n", good_result);

    // Problem with side effects
    int i = 5, j = 3;
    int max = BAD_MAX(i++, j++);  // i++ or j++ evaluated twice!
    std::cout << std::format("After BAD_MAX: max={}, i={}, j={}\n", max, i, j);

    // Best practice: Use inline functions or constexpr instead
    std::cout << "\nBest practice: Use inline/constexpr functions instead of macros\n";
}

// ============================================================================
// #undef - Undefine macros
// ============================================================================

#define TEMP_MACRO 100

void demonstrate_undef() {
    std::cout << "\n=== #undef ===\n";

    std::cout << std::format("TEMP_MACRO before undef: {}\n", TEMP_MACRO);

#undef TEMP_MACRO
#define TEMP_MACRO 200

    std::cout << std::format("TEMP_MACRO after redefine: {}\n", TEMP_MACRO);

#undef TEMP_MACRO
}

// ============================================================================
// #error and #warning
// ============================================================================

void demonstrate_error_warning() {
    std::cout << "\n=== #error and #warning ===\n";

    // Conditional error
#if !defined(__cplusplus)
#error "This code requires a C++ compiler"
#endif

    // Feature checking
#if __cplusplus < 201703L
#warning "C++17 or later recommended"
#endif

    std::cout << "Compile-time checks passed\n";
}

// ============================================================================
// __has_include (C++17)
// ============================================================================

void demonstrate_has_include() {
    std::cout << "\n=== __has_include (C++17) ===\n";

#if __has_include(<optional>)
    std::cout << "<optional> is available\n";
#endif

#if __has_include(<filesystem>)
    std::cout << "<filesystem> is available\n";
#endif

#if __has_include("custom_header.hpp")
    std::cout << "custom_header.hpp found\n";
#else
    std::cout << "custom_header.hpp not found\n";
#endif
}

// ============================================================================
// __has_cpp_attribute (C++20)
// ============================================================================

void demonstrate_has_cpp_attribute() {
    std::cout << "\n=== __has_cpp_attribute (C++20) ===\n";

#if __has_cpp_attribute(nodiscard)
    std::cout << "[[nodiscard]] is supported\n";
#endif

#if __has_cpp_attribute(maybe_unused)
    std::cout << "[[maybe_unused]] is supported\n";
#endif

#if __has_cpp_attribute(likely)
    std::cout << "[[likely]] is supported\n";
#endif

#if __has_cpp_attribute(assume)
    std::cout << "[[assume]] is supported\n";
#endif
}

// ============================================================================
// PRACTICAL EXAMPLES
// ============================================================================

// Debug printing macro
#ifdef DEBUG_MODE
#define ASSERT(condition, message) \
    if (!(condition)) { \
        std::cout << std::format("Assertion failed: {} at {}:{}\n", \
            message, __FILE__, __LINE__); \
    }
#else
#define ASSERT(condition, message) ((void)0)
#endif

// Scope-based timing macro
#define TIME_SCOPE(name) \
    auto _timer_start_##name = std::chrono::high_resolution_clock::now(); \
    std::cout << "Starting: " << #name << "\n"; \
    auto _timer_end_##name = std::chrono::high_resolution_clock::now(); \
    (void)_timer_end_##name;

void demonstrate_practical_examples() {
    std::cout << "\n=== PRACTICAL EXAMPLES ===\n";

    // Assertion example
    int value = 42;
    ASSERT(value > 0, "Value must be positive");
    ASSERT(value < 100, "Value must be less than 100");

    // Platform-specific code
#ifdef __linux__
    std::cout << "Linux-specific code would go here\n";
#elif defined(_WIN32)
    std::cout << "Windows-specific code would go here\n";
#endif

    // Version checking
#if __cplusplus >= 202002L
    std::cout << "Using C++20 features\n";
#elif __cplusplus >= 201703L
    std::cout << "Using C++17 features\n";
#endif
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_macros();
    demonstrate_conditional_compilation();
    demonstrate_predefined_macros();
    demonstrate_pragma_directives();
    demonstrate_include_guards();
    demonstrate_macro_pitfalls();
    demonstrate_undef();
    demonstrate_error_warning();
    demonstrate_has_include();
    demonstrate_has_cpp_attribute();
    demonstrate_practical_examples();
}

} // namespace cpp26_preprocessor

// Clean up macros defined for demonstration
#undef PI
#undef MAX_BUFFER_SIZE
#undef VERSION
#undef SQUARE
#undef MAX
#undef MIN
#undef PRINT_VAR
#undef TO_STRING
#undef STRINGIFY
#undef CONCAT
#undef VAR_NAME
#undef LOG
#undef DEBUG_PRINT
#undef BAD_SQUARE
#undef GOOD_SQUARE
#undef BAD_MAX
#undef TEMP_MACRO
#undef ASSERT
#undef TIME_SCOPE

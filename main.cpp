#include <iostream>
#include <format>
#include <string>
#include <chrono>

// Include all demonstration modules
#include "basics.hpp"
#include "templates.hpp"
#include "oop.hpp"
#include "threading.hpp"
#include "networking.hpp"
#include "coroutines.hpp"
#include "math.hpp"
#include "chrono.hpp"
#include "preprocessor.hpp"
#include "lambda.hpp"

// Include all collection modules
#include "collections/vector.hpp"
#include "collections/array.hpp"
#include "collections/list_deque.hpp"
#include "collections/map.hpp"
#include "collections/set.hpp"
#include "collections/unordered.hpp"
#include "collections/adapters.hpp"
#include "collections/algorithms.hpp"
#include "collections/ranges.hpp"

// ============================================================================
// Menu system for interactive demonstration
// ============================================================================
void display_collections_menu() {
    std::cout << "\n=== COLLECTIONS MENU ===\n";
    std::cout << "  1. Vector (Dynamic Array)\n";
    std::cout << "  2. Array (Fixed-size Array)\n";
    std::cout << "  3. List, Forward_list, Deque (Linked Lists)\n";
    std::cout << "  4. Map & Multimap (Ordered Key-Value)\n";
    std::cout << "  5. Set & Multiset (Ordered Sets)\n";
    std::cout << "  6. Unordered Map & Set (Hash-based)\n";
    std::cout << "  7. Stack, Queue, Priority Queue (Adapters)\n";
    std::cout << "  8. STL Algorithms\n";
    std::cout << "  9. Ranges (C++20)\n";
    std::cout << "  A. Run All Collections\n";
    std::cout << "  0. Back to Main Menu\n";
    std::cout << "\nEnter choice: ";
}

void display_menu() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║           C++26 Comprehensive Feature Showcase            ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
    std::cout << "Select a category to demonstrate:\n";
    std::cout << "  1. Basics (Variables, Pointers, Casting, Keywords, Hints)\n";
    std::cout << "  2. Templates (Function/Class Templates, Metaprogramming)\n";
    std::cout << "  3. OOP (Classes, Inheritance, Polymorphism, Move Semantics)\n";
    std::cout << "  4. Collections (Vector, Map, Set, Algorithms, Ranges)\n";
    std::cout << "  5. Threading (Threads, Mutex, Atomics, Memory Orders)\n";
    std::cout << "  6. Networking (Sockets, Address, Options, Byte Order)\n";
    std::cout << "  7. Coroutines (C++20 Generators, Tasks, Awaitables)\n";
    std::cout << "  8. Math (Constants, Trig, Complex, Special Functions)\n";
    std::cout << "  9. Chrono (Time, Durations, Clocks, Calendar, Timezones)\n";
    std::cout << " 10. Preprocessor (Macros, Directives, Predefined Macros)\n";
    std::cout << " 11. Lambda (Captures, Generic, Variadic, Recursive)\n";
    std::cout << " 12. Run All Demonstrations\n";
    std::cout << "  0. Exit\n";
    std::cout << "\nEnter your choice: ";
}

// ============================================================================
// Utility function to measure execution time
// ============================================================================
template<typename Func>
void time_execution(const std::string& name, Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << std::format("\n[Execution time for '{}': {}ms]\n", name, duration.count());
}

// ============================================================================
// Wait for user input for better readability
// ============================================================================
void wait_for_enter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// ============================================================================
// Main function - Entry point
// ============================================================================
int main() {
    std::cout << std::format("C++ Standard: {}L\n", __cplusplus);
    std::cout << "Compiler: "
#ifdef __clang__
              << "Clang " << __clang_major__ << "." << __clang_minor__
#elif defined(__GNUC__)
              << "GCC " << __GNUC__ << "." << __GNUC_MINOR__
#elif defined(_MSC_VER)
              << "MSVC " << _MSC_VER
#else
              << "Unknown"
#endif
              << "\n";

    // Interactive mode
    int choice;
    bool running = true;

    while (running) {
        display_menu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           BASICS DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("Basics", []() {
                    cpp26_basics::run_all_demos();
                });
                wait_for_enter();
                break;

            case 2:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           TEMPLATES DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("Templates", []() {
                    cpp26_templates::run_all_demos();
                });
                wait_for_enter();
                break;

            case 3:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           OOP DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("OOP", []() {
                    cpp26_oop::run_all_demos();
                });
                wait_for_enter();
                break;

            case 4: {
                // Collections submenu
                bool in_collections = true;
                while (in_collections) {
                    display_collections_menu();
                    char col_choice;
                    std::cin >> col_choice;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Invalid input\n";
                        continue;
                    }

                    switch (col_choice) {
                        case '1':
                            std::cout << "\n=== VECTOR ===\n";
                            time_execution("Vector", cpp26_vector::run_all_demos);
                            wait_for_enter();
                            break;
                        case '2':
                            std::cout << "\n=== ARRAY ===\n";
                            time_execution("Array", cpp26_array::run_all_demos);
                            wait_for_enter();
                            break;
                        case '3':
                            std::cout << "\n=== LIST, DEQUE ===\n";
                            time_execution("List/Deque", cpp26_list_deque::run_all_demos);
                            wait_for_enter();
                            break;
                        case '4':
                            std::cout << "\n=== MAP ===\n";
                            time_execution("Map", cpp26_map::run_all_demos);
                            wait_for_enter();
                            break;
                        case '5':
                            std::cout << "\n=== SET ===\n";
                            time_execution("Set", cpp26_set::run_all_demos);
                            wait_for_enter();
                            break;
                        case '6':
                            std::cout << "\n=== UNORDERED ===\n";
                            time_execution("Unordered", cpp26_unordered::run_all_demos);
                            wait_for_enter();
                            break;
                        case '7':
                            std::cout << "\n=== ADAPTERS ===\n";
                            time_execution("Adapters", cpp26_adapters::run_all_demos);
                            wait_for_enter();
                            break;
                        case '8':
                            std::cout << "\n=== ALGORITHMS ===\n";
                            time_execution("Algorithms", cpp26_algorithms::run_all_demos);
                            wait_for_enter();
                            break;
                        case '9':
                            std::cout << "\n=== RANGES ===\n";
                            time_execution("Ranges", cpp26_ranges::run_all_demos);
                            wait_for_enter();
                            break;
                        case 'A': case 'a':
                            std::cout << "\n=== ALL COLLECTIONS ===\n";
                            time_execution("All Collections", []() {
                                cpp26_vector::run_all_demos();
                                cpp26_array::run_all_demos();
                                cpp26_list_deque::run_all_demos();
                                cpp26_map::run_all_demos();
                                cpp26_set::run_all_demos();
                                cpp26_unordered::run_all_demos();
                                cpp26_adapters::run_all_demos();
                                cpp26_algorithms::run_all_demos();
                                cpp26_ranges::run_all_demos();
                            });
                            wait_for_enter();
                            break;
                        case '0':
                            in_collections = false;
                            break;
                        default:
                            std::cout << "Invalid choice\n";
                            break;
                    }
                }
                break;
            }

            case 5:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           THREADING DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("Threading", []() {
                    cpp26_threading::run_all_demos();
                });
                wait_for_enter();
                break;

            case 6:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           NETWORKING DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("Networking", []() {
                    cpp26_networking::run_all_demos();
                });
                wait_for_enter();
                break;

            case 7:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           COROUTINES DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("Coroutines", []() {
                    cpp26_coroutines::run_all_demos();
                });
                wait_for_enter();
                break;

            case 8:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           MATH DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("Math", []() {
                    cpp26_math::run_all_demos();
                });
                wait_for_enter();
                break;

            case 9:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           CHRONO DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("Chrono", []() {
                    cpp26_chrono::run_all_demos();
                });
                wait_for_enter();
                break;

            case 10:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           PREPROCESSOR DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("Preprocessor", []() {
                    cpp26_preprocessor::run_all_demos();
                });
                wait_for_enter();
                break;

            case 11:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           LAMBDA DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";
                time_execution("Lambda", []() {
                    cpp26_lambda::run_all_demos();
                });
                wait_for_enter();
                break;

            case 12:
                std::cout << "\n" << std::string(60, '=') << "\n";
                std::cout << "           RUNNING ALL DEMONSTRATIONS\n";
                std::cout << std::string(60, '=') << "\n";

                time_execution("All Demos", []() {
                    std::cout << "\n### BASICS ###\n";
                    cpp26_basics::run_all_demos();

                    std::cout << "\n\n### TEMPLATES ###\n";
                    cpp26_templates::run_all_demos();

                    std::cout << "\n\n### OOP ###\n";
                    cpp26_oop::run_all_demos();

                    std::cout << "\n\n### COLLECTIONS ###\n";
                    cpp26_vector::run_all_demos();
                    cpp26_array::run_all_demos();
                    cpp26_list_deque::run_all_demos();
                    cpp26_map::run_all_demos();
                    cpp26_set::run_all_demos();
                    cpp26_unordered::run_all_demos();
                    cpp26_adapters::run_all_demos();
                    cpp26_algorithms::run_all_demos();
                    cpp26_ranges::run_all_demos();

                    std::cout << "\n\n### THREADING ###\n";
                    cpp26_threading::run_all_demos();

                    std::cout << "\n\n### NETWORKING ###\n";
                    cpp26_networking::run_all_demos();

                    std::cout << "\n\n### COROUTINES ###\n";
                    cpp26_coroutines::run_all_demos();

                    std::cout << "\n\n### MATH ###\n";
                    cpp26_math::run_all_demos();

                    std::cout << "\n\n### CHRONO ###\n";
                    cpp26_chrono::run_all_demos();

                    std::cout << "\n\n### PREPROCESSOR ###\n";
                    cpp26_preprocessor::run_all_demos();

                    std::cout << "\n\n### LAMBDA ###\n";
                    cpp26_lambda::run_all_demos();
                });

                wait_for_enter();
                break;

            case 0:
                std::cout << "\nThank you for exploring C++26 features!\n";
                running = false;
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}

/*
 * ============================================================================
 * C++26 FEATURES DEMONSTRATED
 * ============================================================================
 *
 * BASICS:
 *   - Variables (auto, decltype, structured bindings)
 *   - Pointers (raw, smart, pointer to pointer)
 *   - Dereferencing (array, struct, smart pointers)
 *   - Casting (static_cast, dynamic_cast, const_cast, reinterpret_cast)
 *   - Implicit conversions (conversion constructors, conversion operators)
 *   - Inline (inline functions, inline variables, constexpr)
 *   - Static (static variables, static members)
 *   - Volatile (volatile variables, volatile pointers)
 *   - Compiler Hints ([[nodiscard]], [[maybe_unused]], [[deprecated]],
 *                     [[likely]], [[unlikely]], [[no_unique_address]], [[assume]])
 *   - References (lvalue, rvalue, forwarding)
 *   - Pair & Tuple (std::pair, std::tuple, structured bindings, tie)
 *   - If/Switch with initializer (C++17)
 *   - Function pointers (declaration, arrays, callbacks)
 *   - std::ref & std::cref (reference wrappers)
 *   - static_assert (compile-time assertions)
 *
 * TEMPLATES:
 *   - Function templates
 *   - Class templates (full/partial specialization)
 *   - Variadic templates
 *   - Concepts (C++20)
 *   - Template metaprogramming (factorial, fibonacci, type traits)
 *   - SFINAE (Substitution Failure Is Not An Error)
 *   - constexpr/consteval/constinit
 *   - Template template parameters
 *   - Fold expressions (C++17)
 *   - Deduction guides (C++17)
 *   - Diamond operator / CTAD (Class Template Argument Deduction, C++17)
 *
 * OOP:
 *   - Basic classes (encapsulation)
 *   - Inheritance (single, multiple, virtual)
 *   - Polymorphism (virtual functions)
 *   - Abstract classes (pure virtual)
 *   - Operator overloading (arithmetic, comparison, stream, unary)
 *   - Friend functions/classes
 *   - Move semantics (std::move, move constructor, move assignment)
 *   - Rule of Five (destructor, copy ctor, copy assign, move ctor, move assign)
 *   - Constructors (default, deleted, delegating)
 *   - std::format (C++20)
 *
 * COLLECTIONS & ALGORITHMS:
 *   - Sequence containers (vector, array, list, forward_list, deque)
 *   - Associative containers (set, multiset, map, multimap)
 *   - Unordered containers (unordered_set, unordered_map)
 *   - Container adapters (stack, queue, priority_queue)
 *   - Algorithms (sort, find, count, transform, accumulate, etc.)
 *   - Heap operations (make_heap, push_heap, pop_heap, sort_heap)
 *   - Partition algorithms (partition, stable_partition, partition_point)
 *   - Iterators (back_inserter, front_inserter)
 *   - Ranges (C++20 views: filter, transform, take, drop, reverse)
 *   - Range algorithms (all_of, any_of, none_of, count_if)
 *
 * THREADING:
 *   - Basic threads (std::thread)
 *   - Mutex (std::mutex, lock_guard, unique_lock)
 *   - Shared mutex (std::shared_mutex, C++17)
 *   - Condition variables
 *   - Atomic operations (std::atomic)
 *   - Future/Promise
 *   - Packaged task
 *   - Semaphore (C++20)
 *   - Latch (C++20)
 *   - Barrier (C++20)
 *   - Thread-local storage
 *   - jthread (C++20)
 *   - Thread pool implementation
 *
 * NETWORKING:
 *   - Socket creation (TCP/UDP, socket types)
 *   - Socket addressing (sockaddr_in, IPv4/IPv6)
 *   - Socket options (setsockopt, getsockopt, SO_REUSEADDR, etc.)
 *   - Socket operations (bind, listen, accept, connect, send, recv)
 *   - Byte order conversion (htons, ntohs, htonl, ntohl)
 *
 * MODERN C++ FEATURES:
 *   - auto keyword
 *   - Range-based for loops
 *   - Lambda expressions
 *   - std::format (C++20)
 *   - Structured bindings (C++17)
 *   - if/switch with initializer (C++17)
 *   - constexpr if (C++17)
 *   - CTAD - Class Template Argument Deduction (C++17)
 *
 * ============================================================================
 */

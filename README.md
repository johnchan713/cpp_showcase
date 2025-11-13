# C++26 Comprehensive Feature Showcase

A comprehensive demonstration of C++26 features, organized into modular header files for easy learning and reference.

## Project Structure

```
cpp26_showcase/
├── main.cpp              # Entry point with interactive menu
├── basics.hpp            # Variables, pointers, casting, keywords, compiler hints
├── templates.hpp         # Templates, metaprogramming, concepts
├── oop.hpp              # OOP concepts, inheritance, polymorphism
├── collections.hpp      # All STL containers and algorithms
├── threading.hpp        # Threading, synchronization, async operations
├── CMakeLists.txt       # Build configuration
└── README.md           # This file
```

## Features Demonstrated

### 1. Basics (`basics.hpp`)
- **Variables**: auto, decltype, type deduction
- **Pointers**: raw pointers, pointer to pointer, smart pointers
- **Dereferencing**: array, struct, smart pointer dereferencing
- **Casting**: static_cast, dynamic_cast, const_cast, reinterpret_cast
- **Keywords**: inline, static, volatile
- **Compiler Hints**: [[nodiscard]], [[maybe_unused]], [[deprecated]], [[likely]], [[unlikely]], [[no_unique_address]], [[assume]]
- **References**: lvalue, rvalue, forwarding references

### 2. Templates (`templates.hpp`)
- Function templates with type deduction
- Class templates with specialization
- Variadic templates and fold expressions
- Concepts (C++20)
- Template metaprogramming (compile-time factorial, fibonacci)
- SFINAE (Substitution Failure Is Not An Error)
- constexpr, consteval, constinit
- Template template parameters
- Deduction guides (C++17)

### 3. Object-Oriented Programming (`oop.hpp`)
- Basic classes with encapsulation
- Single and multiple inheritance
- Polymorphism with virtual functions
- Abstract classes and interfaces
- Operator overloading
- Friend functions and classes
- Move semantics (C++11)
- Rule of Five
- std::format for modern string formatting

### 4. Collections (`collections.hpp`)
- **Sequence Containers**: vector, array, list, forward_list, deque
- **Associative Containers**: set, multiset, map, multimap
- **Unordered Containers**: unordered_set, unordered_map
- **Container Adapters**: stack, queue, priority_queue
- **Algorithms**: sort, find, count, transform, accumulate, min/max, reverse, unique
- **Ranges (C++20)**: views (filter, transform, take, drop, reverse)
- **Range Algorithms**: all_of, any_of, none_of, count_if

### 5. Threading (`threading.hpp`)
- Basic thread creation and joining
- Mutex and lock_guard
- unique_lock for flexible locking
- shared_mutex for read-write locks (C++17)
- Condition variables for synchronization
- Atomic operations
- Future and Promise
- Packaged tasks
- Semaphore (C++20)
- Latch (C++20)
- Barrier (C++20)
- Thread-local storage
- jthread with stop tokens (C++20)
- Thread pool implementation

## Building the Project

### Prerequisites
- CMake 3.25 or higher
- C++26 compatible compiler (GCC 14+, Clang 18+, or MSVC 19.40+)
  - If C++26 is not available, the project will fall back to C++23

### Build Instructions

#### Linux/macOS
```bash
mkdir build
cd build
cmake ..
make
./cpp26_showcase
```

#### Windows (Visual Studio)
```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
.\Release\cpp26_showcase.exe
```

#### Alternative Build (using cmake directly)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/cpp26_showcase
```

## Usage

Run the executable to launch an interactive menu:

```
╔════════════════════════════════════════════════════════════╗
║           C++26 Comprehensive Feature Showcase            ║
╚════════════════════════════════════════════════════════════╝

Select a category to demonstrate:
  1. Basics (Variables, Pointers, Casting, Keywords, Hints)
  2. Templates (Function/Class Templates, Metaprogramming)
  3. OOP (Classes, Inheritance, Polymorphism, Move Semantics)
  4. Collections (Vector, Map, Set, Algorithms, Ranges)
  5. Threading (Threads, Mutex, Async, Semaphore, Barrier)
  6. Run All Demonstrations
  0. Exit

Enter your choice:
```

Each demonstration includes:
- Clear explanations of the feature
- Practical code examples
- Output showing the results
- Execution time measurements

## Modern C++ Features Highlighted

- **C++11**: Move semantics, lambda expressions, auto, range-based for loops
- **C++14**: Generic lambdas, variable templates
- **C++17**: Structured bindings, if with initializer, fold expressions, std::variant
- **C++20**: Concepts, ranges, std::format, three-way comparison, coroutines basics
- **C++23**: std::expected, std::mdspan (if available)
- **C++26**: Latest standard library features and language improvements

## Learning Path

1. **Start with Basics**: Understand fundamental C++ features
2. **Explore Templates**: Learn generic programming and metaprogramming
3. **Master OOP**: Object-oriented design patterns
4. **Study Collections**: STL containers and algorithms
5. **Dive into Threading**: Concurrent programming and synchronization

## Compiler Compatibility

| Compiler | Minimum Version | C++26 Support |
|----------|----------------|---------------|
| GCC      | 14.0           | Partial       |
| Clang    | 18.0           | Partial       |
| MSVC     | 19.40          | Partial       |

**Note**: C++26 is not yet finalized. This project uses features from C++20/23 and will be updated as C++26 features become available.

## Contributing

This is a showcase project. Feel free to:
- Add more examples
- Improve documentation
- Report issues
- Suggest new features to demonstrate

## License

This project is provided as educational material and is free to use and modify.

## Resources

- [C++ Reference](https://en.cppreference.com/)
- [ISO C++ Standard](https://isocpp.org/)
- [C++20/23/26 Features](https://en.cppreference.com/w/cpp/compiler_support)

---

**Happy Learning! 🚀**

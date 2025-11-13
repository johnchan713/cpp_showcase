#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <format>

namespace cpp26_vector {

// ============================================================================
// VECTOR - Dynamic contiguous array
// std::vector is the most commonly used STL container
// Reference: https://en.cppreference.com/w/cpp/container/vector
// ============================================================================

// Demonstrates vector construction and initialization
void demonstrate_vector_construction() {
    std::cout << "\n=== VECTOR CONSTRUCTION ===\n";

    // Default constructor
    std::vector<int> v1;
    std::cout << "v1 (default): size=" << v1.size() << ", capacity=" << v1.capacity() << "\n";

    // Fill constructor
    std::vector<int> v2(5, 100);  // 5 elements, each with value 100
    std::cout << "v2 (fill 5x100): ";
    for (auto x : v2) std::cout << x << " ";
    std::cout << "\n";

    // Range constructor
    std::vector<int> v3(v2.begin(), v2.end());
    std::cout << "v3 (range from v2): size=" << v3.size() << "\n";

    // Copy constructor
    std::vector<int> v4(v2);
    std::cout << "v4 (copy of v2): size=" << v4.size() << "\n";

    // Move constructor
    std::vector<int> v5(std::move(v3));
    std::cout << "v5 (moved from v3): size=" << v5.size() << ", v3 size=" << v3.size() << "\n";

    // Initializer list constructor (C++11)
    std::vector<int> v6 = {1, 2, 3, 4, 5};
    std::cout << "v6 (initializer list): ";
    for (auto x : v6) std::cout << x << " ";
    std::cout << "\n";
}

// Demonstrates element access methods
void demonstrate_vector_element_access() {
    std::cout << "\n=== VECTOR ELEMENT ACCESS ===\n";

    std::vector<int> vec = {10, 20, 30, 40, 50};

    // at() - bounds-checked access
    std::cout << "at(2): " << vec.at(2) << "\n";

    // operator[] - unchecked access
    std::cout << "vec[3]: " << vec[3] << "\n";

    // front() - first element
    std::cout << "front(): " << vec.front() << "\n";

    // back() - last element
    std::cout << "back(): " << vec.back() << "\n";

    // data() - pointer to underlying array
    int* ptr = vec.data();
    std::cout << "data()[1]: " << ptr[1] << "\n";

    // Modify through access
    vec[0] = 100;
    vec.at(1) = 200;
    std::cout << "After modification: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";
}

// Demonstrates iterator methods
void demonstrate_vector_iterators() {
    std::cout << "\n=== VECTOR ITERATORS ===\n";

    std::vector<int> vec = {1, 2, 3, 4, 5};

    // begin() / end() - forward iteration
    std::cout << "Forward (begin/end): ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // rbegin() / rend() - reverse iteration
    std::cout << "Reverse (rbegin/rend): ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // cbegin() / cend() - const forward iteration
    std::cout << "Const forward: ";
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Range-based for loop (uses begin/end internally)
    std::cout << "Range-based for: ";
    for (const auto& x : vec) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

// Demonstrates capacity methods
void demonstrate_vector_capacity() {
    std::cout << "\n=== VECTOR CAPACITY ===\n";

    std::vector<int> vec;

    std::cout << "Initial - size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";

    // reserve() - allocate memory without changing size
    vec.reserve(100);
    std::cout << "After reserve(100) - size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";

    // Add elements
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    std::cout << "After 10 push_back - size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";

    // resize() - change size
    vec.resize(5);
    std::cout << "After resize(5) - size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";

    vec.resize(15, 99);  // Resize with fill value
    std::cout << "After resize(15, 99) - size: " << vec.size() << ", last element: " << vec.back() << "\n";

    // shrink_to_fit() - reduce capacity to size
    vec.shrink_to_fit();
    std::cout << "After shrink_to_fit - size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";

    // empty() - check if empty
    std::cout << "empty(): " << (vec.empty() ? "true" : "false") << "\n";

    // max_size() - theoretical maximum size
    std::cout << "max_size(): " << vec.max_size() << "\n";
}

// Demonstrates modifier methods
void demonstrate_vector_modifiers() {
    std::cout << "\n=== VECTOR MODIFIERS ===\n";

    std::vector<int> vec = {1, 2, 3};

    // push_back() - add element at end
    vec.push_back(4);
    std::cout << "After push_back(4): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // emplace_back() - construct element in place (C++11)
    vec.emplace_back(5);
    std::cout << "After emplace_back(5): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // pop_back() - remove last element
    vec.pop_back();
    std::cout << "After pop_back(): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // insert() - insert element at position
    auto it = vec.insert(vec.begin() + 2, 99);
    std::cout << "After insert(pos 2, 99): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << " (returned iterator points to: " << *it << ")\n";

    // insert() - insert multiple copies
    vec.insert(vec.begin(), 3, 77);
    std::cout << "After insert(begin, 3x77): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // emplace() - construct element at position
    vec.emplace(vec.begin() + 2, 88);
    std::cout << "After emplace(pos 2, 88): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // erase() - remove element at position
    vec.erase(vec.begin() + 2);
    std::cout << "After erase(pos 2): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // erase() - remove range
    vec.erase(vec.begin(), vec.begin() + 3);
    std::cout << "After erase(begin, begin+3): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // clear() - remove all elements
    vec.clear();
    std::cout << "After clear(): size=" << vec.size() << "\n";

    // assign() - replace contents
    vec.assign(5, 10);
    std::cout << "After assign(5, 10): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // swap() - swap contents with another vector
    std::vector<int> vec2 = {100, 200, 300};
    vec.swap(vec2);
    std::cout << "After swap - vec: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << ", vec2: ";
    for (auto x : vec2) std::cout << x << " ";
    std::cout << "\n";
}

// Demonstrates comparison operators
void demonstrate_vector_comparison() {
    std::cout << "\n=== VECTOR COMPARISON ===\n";

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};
    std::vector<int> v3 = {1, 2, 4};

    std::cout << "v1 == v2: " << (v1 == v2) << "\n";
    std::cout << "v1 != v3: " << (v1 != v3) << "\n";
    std::cout << "v1 < v3: " << (v1 < v3) << "\n";
    std::cout << "v1 <= v2: " << (v1 <= v2) << "\n";
    std::cout << "v3 > v1: " << (v3 > v1) << "\n";
    std::cout << "v2 >= v1: " << (v2 >= v1) << "\n";

    // C++20 three-way comparison (spaceship operator)
    // auto result = v1 <=> v3;
}

// Demonstrates algorithms commonly used with vectors
void demonstrate_vector_algorithms() {
    std::cout << "\n=== VECTOR WITH ALGORITHMS ===\n";

    std::vector<int> vec = {5, 2, 8, 1, 9, 3, 7};

    // std::sort
    std::sort(vec.begin(), vec.end());
    std::cout << "After sort: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // std::reverse
    std::reverse(vec.begin(), vec.end());
    std::cout << "After reverse: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";

    // std::find
    auto it = std::find(vec.begin(), vec.end(), 7);
    if (it != vec.end()) {
        std::cout << "Found 7 at index: " << std::distance(vec.begin(), it) << "\n";
    }

    // std::count
    vec.push_back(7);
    vec.push_back(7);
    int count = std::count(vec.begin(), vec.end(), 7);
    std::cout << "Count of 7: " << count << "\n";

    // std::accumulate
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum: " << sum << "\n";

    // std::transform
    std::vector<int> doubled;
    std::transform(vec.begin(), vec.end(), std::back_inserter(doubled),
                   [](int x) { return x * 2; });
    std::cout << "Doubled: ";
    for (auto x : doubled) std::cout << x << " ";
    std::cout << "\n";

    // std::remove_if + erase (erase-remove idiom)
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [](int x) { return x > 5; }),
              vec.end());
    std::cout << "After removing elements > 5: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";
}

// Demonstrates vector of custom objects
void demonstrate_vector_custom_objects() {
    std::cout << "\n=== VECTOR OF CUSTOM OBJECTS ===\n";

    struct Person {
        std::string name;
        int age;

        Person(std::string n, int a) : name(std::move(n)), age(a) {}
    };

    std::vector<Person> people;

    // emplace_back constructs in place - more efficient
    people.emplace_back("Alice", 30);
    people.emplace_back("Bob", 25);
    people.emplace_back("Charlie", 35);

    std::cout << "People: ";
    for (const auto& p : people) {
        std::cout << "{" << p.name << ", " << p.age << "} ";
    }
    std::cout << "\n";

    // Sort by age
    std::sort(people.begin(), people.end(),
              [](const Person& a, const Person& b) { return a.age < b.age; });

    std::cout << "Sorted by age: ";
    for (const auto& p : people) {
        std::cout << "{" << p.name << ", " << p.age << "} ";
    }
    std::cout << "\n";
}

// Demonstrates vector<bool> specialization
void demonstrate_vector_bool() {
    std::cout << "\n=== VECTOR<BOOL> SPECIALIZATION ===\n";

    // vector<bool> is a special space-efficient specialization
    std::vector<bool> bools = {true, false, true, true, false};

    std::cout << "vector<bool>: ";
    for (bool b : bools) {
        std::cout << (b ? "T" : "F") << " ";
    }
    std::cout << "\n";

    // flip() - invert all bits
    bools.flip();
    std::cout << "After flip(): ";
    for (bool b : bools) {
        std::cout << (b ? "T" : "F") << " ";
    }
    std::cout << "\n";

    std::cout << "Size in bytes (approximate): " << (bools.size() / 8) << "\n";
}

// Main runner for all vector demonstrations
void run_all_demos() {
    demonstrate_vector_construction();
    demonstrate_vector_element_access();
    demonstrate_vector_iterators();
    demonstrate_vector_capacity();
    demonstrate_vector_modifiers();
    demonstrate_vector_comparison();
    demonstrate_vector_algorithms();
    demonstrate_vector_custom_objects();
    demonstrate_vector_bool();
}

} // namespace cpp26_vector

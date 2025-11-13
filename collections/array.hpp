#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <format>

namespace cpp26_array {

// ============================================================================
// ARRAY - Fixed-size contiguous array (C++11)
// std::array is a container that encapsulates fixed size arrays
// Reference: https://en.cppreference.com/w/cpp/container/array
// ============================================================================

// Demonstrates array construction and initialization
void demonstrate_array_construction() {
    std::cout << "\n=== ARRAY CONSTRUCTION ===\n";

    // Aggregate initialization
    std::array<int, 5> arr1 = {1, 2, 3, 4, 5};
    std::cout << "arr1 (aggregate init): size=" << arr1.size() << "\n";

    // Partial initialization (rest are zero-initialized)
    std::array<int, 5> arr2 = {1, 2};
    std::cout << "arr2 (partial init): ";
    for (auto x : arr2) std::cout << x << " ";
    std::cout << "\n";

    // Default initialization (indeterminate values for non-class types)
    std::array<int, 3> arr3;
    std::cout << "arr3 (default): size=" << arr3.size() << "\n";

    // Zero initialization
    std::array<int, 4> arr4 = {};  // All elements are 0
    std::cout << "arr4 (zero init): ";
    for (auto x : arr4) std::cout << x << " ";
    std::cout << "\n";

    // Copy construction
    std::array<int, 5> arr5 = arr1;
    std::cout << "arr5 (copy of arr1): size=" << arr5.size() << "\n";

    // Move construction
    std::array<int, 5> arr6 = std::move(arr1);
    std::cout << "arr6 (moved from arr1): size=" << arr6.size() << "\n";
}

// Demonstrates element access methods
void demonstrate_array_element_access() {
    std::cout << "\n=== ARRAY ELEMENT ACCESS ===\n";

    std::array<int, 5> arr = {10, 20, 30, 40, 50};

    // at() - bounds-checked access
    std::cout << "at(2): " << arr.at(2) << "\n";

    try {
        std::cout << "at(10): " << arr.at(10) << "\n";  // Will throw
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    // operator[] - unchecked access (faster but unsafe)
    std::cout << "arr[3]: " << arr[3] << "\n";

    // front() - first element
    std::cout << "front(): " << arr.front() << "\n";

    // back() - last element
    std::cout << "back(): " << arr.back() << "\n";

    // data() - pointer to underlying array
    int* ptr = arr.data();
    std::cout << "data()[1]: " << ptr[1] << "\n";

    // get<N>() - compile-time indexed access (C++11)
    std::cout << "std::get<4>(arr): " << std::get<4>(arr) << "\n";
}

// Demonstrates iterators
void demonstrate_array_iterators() {
    std::cout << "\n=== ARRAY ITERATORS ===\n";

    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    // begin() / end() - forward iteration
    std::cout << "Forward: ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // rbegin() / rend() - reverse iteration
    std::cout << "Reverse: ";
    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // cbegin() / cend() - const forward iteration
    std::cout << "Const forward: ";
    for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Range-based for loop
    std::cout << "Range-based for: ";
    for (const auto& x : arr) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

// Demonstrates capacity methods
void demonstrate_array_capacity() {
    std::cout << "\n=== ARRAY CAPACITY ===\n";

    std::array<int, 10> arr = {1, 2, 3, 4, 5};

    // size() - number of elements (fixed at compile time)
    std::cout << "size(): " << arr.size() << "\n";

    // max_size() - same as size() for array
    std::cout << "max_size(): " << arr.max_size() << "\n";

    // empty() - check if size is 0
    std::cout << "empty(): " << (arr.empty() ? "true" : "false") << "\n";

    // Zero-sized array
    std::array<int, 0> empty_arr;
    std::cout << "empty_arr.size(): " << empty_arr.size() << "\n";
    std::cout << "empty_arr.empty(): " << (empty_arr.empty() ? "true" : "false") << "\n";
}

// Demonstrates operations
void demonstrate_array_operations() {
    std::cout << "\n=== ARRAY OPERATIONS ===\n";

    std::array<int, 5> arr1 = {1, 2, 3, 4, 5};
    std::array<int, 5> arr2 = {10, 20, 30, 40, 50};

    // fill() - fill all elements with value
    arr1.fill(99);
    std::cout << "After fill(99): ";
    for (auto x : arr1) std::cout << x << " ";
    std::cout << "\n";

    // swap() - swap contents with another array
    arr1 = {1, 2, 3, 4, 5};
    arr1.swap(arr2);
    std::cout << "After swap - arr1: ";
    for (auto x : arr1) std::cout << x << " ";
    std::cout << ", arr2: ";
    for (auto x : arr2) std::cout << x << " ";
    std::cout << "\n";
}

// Demonstrates comparison operators
void demonstrate_array_comparison() {
    std::cout << "\n=== ARRAY COMPARISON ===\n";

    std::array<int, 3> arr1 = {1, 2, 3};
    std::array<int, 3> arr2 = {1, 2, 3};
    std::array<int, 3> arr3 = {1, 2, 4};

    std::cout << "arr1 == arr2: " << (arr1 == arr2) << "\n";
    std::cout << "arr1 != arr3: " << (arr1 != arr3) << "\n";
    std::cout << "arr1 < arr3: " << (arr1 < arr3) << "\n";
    std::cout << "arr1 <= arr2: " << (arr1 <= arr2) << "\n";
    std::cout << "arr3 > arr1: " << (arr3 > arr1) << "\n";
    std::cout << "arr2 >= arr1: " << (arr2 >= arr1) << "\n";
}

// Demonstrates algorithms with arrays
void demonstrate_array_algorithms() {
    std::cout << "\n=== ARRAY WITH ALGORITHMS ===\n";

    std::array<int, 7> arr = {5, 2, 8, 1, 9, 3, 7};

    // std::sort
    std::sort(arr.begin(), arr.end());
    std::cout << "After sort: ";
    for (auto x : arr) std::cout << x << " ";
    std::cout << "\n";

    // std::reverse
    std::reverse(arr.begin(), arr.end());
    std::cout << "After reverse: ";
    for (auto x : arr) std::cout << x << " ";
    std::cout << "\n";

    // std::find
    auto it = std::find(arr.begin(), arr.end(), 7);
    if (it != arr.end()) {
        std::cout << "Found 7 at index: " << std::distance(arr.begin(), it) << "\n";
    }

    // std::count
    int count = std::count(arr.begin(), arr.end(), 7);
    std::cout << "Count of 7: " << count << "\n";

    // std::accumulate
    int sum = std::accumulate(arr.begin(), arr.end(), 0);
    std::cout << "Sum: " << sum << "\n";

    // std::min_element / std::max_element
    auto min_it = std::min_element(arr.begin(), arr.end());
    auto max_it = std::max_element(arr.begin(), arr.end());
    std::cout << "Min: " << *min_it << ", Max: " << *max_it << "\n";
}

// Demonstrates structured bindings with arrays (C++17)
void demonstrate_array_structured_bindings() {
    std::cout << "\n=== ARRAY STRUCTURED BINDINGS (C++17) ===\n";

    std::array<int, 3> arr = {10, 20, 30};

    // Decompose array into variables
    auto [a, b, c] = arr;
    std::cout << std::format("Decomposed: a={}, b={}, c={}\n", a, b, c);

    // Structured binding with references
    auto& [x, y, z] = arr;
    x = 100;
    std::cout << "After modifying x: arr[0]=" << arr[0] << "\n";
}

// Demonstrates multi-dimensional arrays
void demonstrate_array_multidimensional() {
    std::cout << "\n=== MULTI-DIMENSIONAL ARRAYS ===\n";

    // 2D array (array of arrays)
    std::array<std::array<int, 3>, 2> matrix = {{
        {1, 2, 3},
        {4, 5, 6}
    }};

    std::cout << "2D array (2x3 matrix):\n";
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Access elements
    std::cout << "matrix[1][2]: " << matrix[1][2] << "\n";

    // 3D array
    std::array<std::array<std::array<int, 2>, 2>, 2> cube = {{
        {{{1, 2}, {3, 4}}},
        {{{5, 6}, {7, 8}}}
    }};

    std::cout << "3D array (2x2x2 cube): cube[1][1][1]=" << cube[1][1][1] << "\n";
}

// Demonstrates array of custom objects
void demonstrate_array_custom_objects() {
    std::cout << "\n=== ARRAY OF CUSTOM OBJECTS ===\n";

    struct Point {
        int x, y;
        Point(int x = 0, int y = 0) : x(x), y(y) {}
    };

    std::array<Point, 3> points = {
        Point{1, 2},
        Point{3, 4},
        Point{5, 6}
    };

    std::cout << "Points: ";
    for (const auto& p : points) {
        std::cout << "(" << p.x << "," << p.y << ") ";
    }
    std::cout << "\n";

    // Sort by x coordinate
    std::sort(points.begin(), points.end(),
              [](const Point& a, const Point& b) { return a.x < b.x; });

    std::cout << "Sorted by x: ";
    for (const auto& p : points) {
        std::cout << "(" << p.x << "," << p.y << ") ";
    }
    std::cout << "\n";
}

// Demonstrates std::to_array (C++20)
void demonstrate_to_array() {
    std::cout << "\n=== std::to_array (C++20) ===\n";

    // Convert C-style array to std::array
    int c_array[] = {1, 2, 3, 4, 5};
    auto std_array = std::to_array(c_array);

    std::cout << "Converted from C-array: ";
    for (auto x : std_array) std::cout << x << " ";
    std::cout << "\n";

    // Deduce array type from initializer
    auto arr = std::to_array({10, 20, 30, 40});
    std::cout << "From initializer list, size: " << arr.size() << "\n";
}

// Main runner for all array demonstrations
void run_all_demos() {
    demonstrate_array_construction();
    demonstrate_array_element_access();
    demonstrate_array_iterators();
    demonstrate_array_capacity();
    demonstrate_array_operations();
    demonstrate_array_comparison();
    demonstrate_array_algorithms();
    demonstrate_array_structured_bindings();
    demonstrate_array_multidimensional();
    demonstrate_array_custom_objects();
    demonstrate_to_array();
}

} // namespace cpp26_array

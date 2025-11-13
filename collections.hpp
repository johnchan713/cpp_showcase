#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <array>
#include <forward_list>
#include <string>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <format>

namespace cpp26_collections {

// ============================================================================
// VECTOR - Dynamic array with contiguous storage
// Usage: std::vector<T> - Best for dynamic arrays, random access
// ============================================================================
void demonstrate_vector() {
    std::cout << "\n=== VECTOR (Dynamic Array) ===\n";

    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Adding elements
    vec.push_back(6);
    vec.emplace_back(7);  // Construct in place

    // Range-based for loop with auto
    std::cout << "Vector elements: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // C++20 Ranges
    std::cout << "First 3 elements: ";
    for (auto elem : vec | std::views::take(3)) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // Accessing elements
    std::cout << std::format("First: {}, Last: {}, Size: {}, Capacity: {}\n",
                             vec.front(), vec.back(), vec.size(), vec.capacity());

    // Iterators
    auto it = std::find(vec.begin(), vec.end(), 4);
    if (it != vec.end()) {
        std::cout << std::format("Found 4 at index: {}\n", std::distance(vec.begin(), it));
    }
}

// ============================================================================
// ARRAY - Fixed-size array (C++11)
// Usage: std::array<T, N> - Fixed size, stack allocated
// ============================================================================
void demonstrate_array() {
    std::cout << "\n=== ARRAY (Fixed-size) ===\n";

    std::array<int, 5> arr = {10, 20, 30, 40, 50};

    std::cout << "Array elements: ";
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // Structured binding (C++17)
    auto [a, b, c, d, e] = arr;
    std::cout << std::format("Destructured: a={}, b={}, c={}\n", a, b, c);

    std::cout << std::format("Size: {}, Front: {}, Back: {}\n",
                             arr.size(), arr.front(), arr.back());
}

// ============================================================================
// LIST - Doubly-linked list
// Usage: std::list<T> - Good for frequent insertions/deletions
// ============================================================================
void demonstrate_list() {
    std::cout << "\n=== LIST (Doubly-linked) ===\n";

    std::list<std::string> lst = {"apple", "banana", "cherry"};

    lst.push_front("apricot");
    lst.push_back("date");
    lst.emplace(std::next(lst.begin(), 2), "blueberry");

    std::cout << "List elements: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // Sorting
    lst.sort();
    std::cout << "Sorted: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << std::format("Size: {}\n", lst.size());
}

// ============================================================================
// FORWARD_LIST - Singly-linked list (C++11)
// Usage: std::forward_list<T> - Memory efficient linked list
// ============================================================================
void demonstrate_forward_list() {
    std::cout << "\n=== FORWARD_LIST (Singly-linked) ===\n";

    std::forward_list<int> flist = {1, 2, 3, 4, 5};

    flist.push_front(0);
    flist.emplace_front(-1);

    std::cout << "Forward list: ";
    for (const auto& elem : flist) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    flist.sort();
    std::cout << "Sorted: ";
    for (const auto& elem : flist) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

// ============================================================================
// DEQUE - Double-ended queue
// Usage: std::deque<T> - Fast insertion at both ends
// ============================================================================
void demonstrate_deque() {
    std::cout << "\n=== DEQUE (Double-ended Queue) ===\n";

    std::deque<int> deq = {3, 4, 5};

    deq.push_front(2);
    deq.push_back(6);
    deq.emplace_front(1);
    deq.emplace_back(7);

    std::cout << "Deque elements: ";
    for (const auto& elem : deq) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << std::format("Front: {}, Back: {}, Size: {}\n",
                             deq.front(), deq.back(), deq.size());

    deq.pop_front();
    deq.pop_back();
    std::cout << "After pop front & back: ";
    for (const auto& elem : deq) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

// ============================================================================
// SET - Ordered set (unique elements)
// Usage: std::set<T> - Sorted unique elements, log(n) operations
// ============================================================================
void demonstrate_set() {
    std::cout << "\n=== SET (Ordered, Unique) ===\n";

    std::set<int> s = {5, 2, 8, 2, 1, 9, 2};  // Duplicates removed

    s.insert(3);
    s.emplace(7);

    std::cout << "Set elements (sorted): ";
    for (const auto& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // Find element
    if (auto it = s.find(5); it != s.end()) {
        std::cout << "Found: " << *it << "\n";
    }

    std::cout << std::format("Size: {}, Contains 8: {}\n",
                             s.size(), s.contains(8));  // C++20 contains()

    // Lower and upper bound
    auto lower = s.lower_bound(5);
    [[maybe_unused]] auto upper = s.upper_bound(5);
    std::cout << std::format("Lower bound of 5: {}\n", *lower);
}

// ============================================================================
// MULTISET - Ordered set (allows duplicates)
// Usage: std::multiset<T> - Sorted elements, allows duplicates
// ============================================================================
void demonstrate_multiset() {
    std::cout << "\n=== MULTISET (Ordered, Duplicates Allowed) ===\n";

    std::multiset<int> ms = {5, 2, 8, 2, 1, 9, 2};

    ms.insert(2);
    ms.insert(2);

    std::cout << "Multiset elements: ";
    for (const auto& elem : ms) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << std::format("Count of 2: {}\n", ms.count(2));
}

// ============================================================================
// UNORDERED_SET - Hash set (unique elements, unordered)
// Usage: std::unordered_set<T> - O(1) average operations, no order
// ============================================================================
void demonstrate_unordered_set() {
    std::cout << "\n=== UNORDERED_SET (Hash-based, Unique) ===\n";

    std::unordered_set<std::string> us = {"apple", "banana", "cherry"};

    us.insert("date");
    us.emplace("elderberry");
    us.insert("apple");  // Duplicate, won't be added

    std::cout << "Unordered set: ";
    for (const auto& elem : us) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << std::format("Size: {}, Contains 'banana': {}\n",
                             us.size(), us.contains("banana"));

    std::cout << std::format("Bucket count: {}, Load factor: {:.2f}\n",
                             us.bucket_count(), us.load_factor());
}

// ============================================================================
// MAP - Ordered key-value pairs (unique keys)
// Usage: std::map<K, V> - Sorted by key, log(n) operations
// ============================================================================
void demonstrate_map() {
    std::cout << "\n=== MAP (Ordered Key-Value) ===\n";

    std::map<std::string, int> m = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };

    m["David"] = 40;
    m.emplace("Eve", 28);
    m.insert({"Frank", 32});

    // Try emplace (C++17) - doesn't overwrite if key exists
    m.try_emplace("Alice", 100);  // Won't change Alice's value

    std::cout << "Map contents:\n";
    for (const auto& [key, value] : m) {  // Structured binding (C++17)
        std::cout << std::format("  {}: {}\n", key, value);
    }

    // Access elements
    std::cout << std::format("Alice's age: {}\n", m["Alice"]);
    std::cout << std::format("Contains 'Bob': {}\n", m.contains("Bob"));  // C++20

    // Extract value safely
    if (auto it = m.find("Charlie"); it != m.end()) {
        std::cout << std::format("Found Charlie: {}\n", it->second);
    }
}

// ============================================================================
// MULTIMAP - Ordered key-value pairs (allows duplicate keys)
// Usage: std::multimap<K, V> - Multiple values per key
// ============================================================================
void demonstrate_multimap() {
    std::cout << "\n=== MULTIMAP (Ordered, Duplicate Keys) ===\n";

    std::multimap<std::string, int> mm = {
        {"apple", 1},
        {"banana", 2},
        {"apple", 3},
        {"apple", 4}
    };

    mm.insert({"banana", 5});

    std::cout << "Multimap contents:\n";
    for (const auto& [key, value] : mm) {
        std::cout << std::format("  {}: {}\n", key, value);
    }

    std::cout << std::format("Count of 'apple': {}\n", mm.count("apple"));

    // Equal range - get all values for a key
    auto range = mm.equal_range("apple");
    std::cout << "All 'apple' values: ";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->second << " ";
    }
    std::cout << "\n";
}

// ============================================================================
// UNORDERED_MAP - Hash map (unique keys, unordered)
// Usage: std::unordered_map<K, V> - O(1) average operations
// ============================================================================
void demonstrate_unordered_map() {
    std::cout << "\n=== UNORDERED_MAP (Hash-based Key-Value) ===\n";

    std::unordered_map<int, std::string> um = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    um[4] = "four";
    um.emplace(5, "five");
    um.try_emplace(6, "six");

    std::cout << "Unordered map:\n";
    for (const auto& [key, value] : um) {
        std::cout << std::format("  {}: {}\n", key, value);
    }

    std::cout << std::format("Value at key 3: {}\n", um.at(3));
    std::cout << std::format("Contains key 5: {}\n", um.contains(5));
}

// ============================================================================
// STACK - LIFO container adapter
// Usage: std::stack<T> - Last-In-First-Out operations
// ============================================================================
void demonstrate_stack() {
    std::cout << "\n=== STACK (LIFO) ===\n";

    std::stack<int> stk;

    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.emplace(40);

    std::cout << std::format("Stack size: {}, Top: {}\n", stk.size(), stk.top());

    std::cout << "Popping all elements: ";
    while (!stk.empty()) {
        std::cout << stk.top() << " ";
        stk.pop();
    }
    std::cout << "\n";
}

// ============================================================================
// QUEUE - FIFO container adapter
// Usage: std::queue<T> - First-In-First-Out operations
// ============================================================================
void demonstrate_queue() {
    std::cout << "\n=== QUEUE (FIFO) ===\n";

    std::queue<std::string> q;

    q.push("first");
    q.push("second");
    q.push("third");
    q.emplace("fourth");

    std::cout << std::format("Queue size: {}, Front: {}, Back: {}\n",
                             q.size(), q.front(), q.back());

    std::cout << "Dequeuing all: ";
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "\n";
}

// ============================================================================
// PRIORITY_QUEUE - Heap-based priority queue
// Usage: std::priority_queue<T> - Max-heap by default
// ============================================================================
void demonstrate_priority_queue() {
    std::cout << "\n=== PRIORITY_QUEUE (Heap) ===\n";

    std::priority_queue<int> pq;

    pq.push(30);
    pq.push(10);
    pq.push(50);
    pq.push(20);
    pq.emplace(40);

    std::cout << std::format("Priority queue size: {}, Top: {}\n", pq.size(), pq.top());

    std::cout << "Elements in priority order: ";
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";

    // Min-heap version
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    min_pq.push(30);
    min_pq.push(10);
    min_pq.push(50);

    std::cout << "Min-heap top: " << min_pq.top() << "\n";
}

// ============================================================================
// ALGORITHMS - Common STL algorithms on collections
// Usage: Demonstrate various <algorithm> functions
// ============================================================================
void demonstrate_algorithms() {
    std::cout << "\n=== STL ALGORITHMS ===\n";

    std::vector<int> vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    // Sorting
    std::sort(vec.begin(), vec.end());
    std::cout << "Sorted: ";
    for (auto v : vec) std::cout << v << " ";
    std::cout << "\n";

    // Binary search (requires sorted range)
    bool found = std::binary_search(vec.begin(), vec.end(), 5);
    std::cout << std::format("Binary search for 5: {}\n", found);

    // Find
    auto it = std::find(vec.begin(), vec.end(), 7);
    std::cout << std::format("Found 7 at index: {}\n", std::distance(vec.begin(), it));

    // Count
    std::vector<int> vec2 = {1, 2, 2, 3, 2, 4, 2};
    int count = std::count(vec2.begin(), vec2.end(), 2);
    std::cout << std::format("Count of 2: {}\n", count);

    // Transform
    std::vector<int> doubled;
    std::transform(vec.begin(), vec.end(), std::back_inserter(doubled),
                   [](int x) { return x * 2; });
    std::cout << "Doubled: ";
    for (auto v : doubled) std::cout << v << " ";
    std::cout << "\n";

    // Accumulate (sum)
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << std::format("Sum: {}\n", sum);

    // Min/Max element
    auto min_it = std::min_element(vec.begin(), vec.end());
    auto max_it = std::max_element(vec.begin(), vec.end());
    std::cout << std::format("Min: {}, Max: {}\n", *min_it, *max_it);

    // Reverse
    std::reverse(vec.begin(), vec.end());
    std::cout << "Reversed: ";
    for (auto v : vec) std::cout << v << " ";
    std::cout << "\n";

    // Unique (remove consecutive duplicates)
    std::vector<int> vec3 = {1, 1, 2, 2, 2, 3, 3, 4};
    auto last = std::unique(vec3.begin(), vec3.end());
    vec3.erase(last, vec3.end());
    std::cout << "After unique: ";
    for (auto v : vec3) std::cout << v << " ";
    std::cout << "\n";
}

// ============================================================================
// RANGES (C++20) - Modern range-based operations
// Usage: std::ranges and views for functional programming
// ============================================================================
void demonstrate_ranges() {
    std::cout << "\n=== RANGES (C++20) ===\n";

    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Filter and transform using views
    auto even_doubled = vec
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * 2; });

    std::cout << "Even numbers doubled: ";
    for (auto v : even_doubled) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // Take first N elements
    std::cout << "First 5 elements: ";
    for (auto v : vec | std::views::take(5)) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // Drop first N elements
    std::cout << "After dropping 5: ";
    for (auto v : vec | std::views::drop(5)) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // Reverse view
    std::cout << "Reversed: ";
    for (auto v : vec | std::views::reverse) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // All-of, any-of, none-of
    std::cout << std::format("All positive: {}\n",
        std::ranges::all_of(vec, [](int x) { return x > 0; }));
    std::cout << std::format("Any > 5: {}\n",
        std::ranges::any_of(vec, [](int x) { return x > 5; }));
    std::cout << std::format("None > 10: {}\n",
        std::ranges::none_of(vec, [](int x) { return x > 10; }));

    // Count if
    auto count = std::ranges::count_if(vec, [](int x) { return x > 5; });
    std::cout << std::format("Count > 5: {}\n", count);
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_vector();
    demonstrate_array();
    demonstrate_list();
    demonstrate_forward_list();
    demonstrate_deque();
    demonstrate_set();
    demonstrate_multiset();
    demonstrate_unordered_set();
    demonstrate_map();
    demonstrate_multimap();
    demonstrate_unordered_map();
    demonstrate_stack();
    demonstrate_queue();
    demonstrate_priority_queue();
    demonstrate_algorithms();
    demonstrate_ranges();
}

} // namespace cpp26_collections

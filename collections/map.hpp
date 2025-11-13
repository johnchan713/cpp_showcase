#pragma once

#include <iostream>
#include <map>
#include <string>
#include <format>

namespace cpp26_map {

// ============================================================================
// MAP - Ordered associative container (Red-Black Tree)
// std::map stores key-value pairs in sorted order
// Reference: https://en.cppreference.com/w/cpp/container/map
// ============================================================================

// Demonstrates map construction
void demonstrate_map_construction() {
    std::cout << "\n=== MAP CONSTRUCTION ===\n";

    // Default constructor
    std::map<std::string, int> m1;
    std::cout << "m1 (default): size=" << m1.size() << "\n";

    // Initializer list (C++11)
    std::map<std::string, int> m2 = {
        {"apple", 1},
        {"banana", 2},
        {"cherry", 3}
    };
    std::cout << "m2 (initializer list): size=" << m2.size() << "\n";

    // Range constructor
    std::map<std::string, int> m3(m2.begin(), m2.end());
    std::cout << "m3 (range from m2): size=" << m3.size() << "\n";

    // Copy constructor
    std::map<std::string, int> m4(m2);
    std::cout << "m4 (copy of m2): size=" << m4.size() << "\n";

    // Move constructor
    std::map<std::string, int> m5(std::move(m3));
    std::cout << "m5 (moved from m3): size=" << m5.size() << ", m3 size=" << m3.size() << "\n";
}

// Demonstrates element access methods
void demonstrate_map_element_access() {
    std::cout << "\n=== MAP ELEMENT ACCESS ===\n";

    std::map<std::string, int> scores = {
        {"Alice", 95},
        {"Bob", 87},
        {"Charlie", 92}
    };

    // operator[] - inserts if key doesn't exist
    std::cout << "scores[\"Alice\"]: " << scores["Alice"] << "\n";
    scores["David"] = 88;  // Inserts new element
    std::cout << "After scores[\"David\"] = 88, size: " << scores.size() << "\n";

    // at() - throws exception if key doesn't exist
    try {
        std::cout << "scores.at(\"Bob\"): " << scores.at("Bob") << "\n";
        std::cout << "scores.at(\"Eve\"): " << scores.at("Eve") << "\n";  // Will throw
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    // Iterate over map
    std::cout << "All scores:\n";
    for (const auto& [name, score] : scores) {  // Structured binding (C++17)
        std::cout << std::format("  {}: {}\n", name, score);
    }
}

// Demonstrates capacity methods
void demonstrate_map_capacity() {
    std::cout << "\n=== MAP CAPACITY ===\n";

    std::map<int, std::string> map;

    std::cout << "empty(): " << (map.empty() ? "true" : "false") << "\n";
    std::cout << "size(): " << map.size() << "\n";

    map[1] = "one";
    map[2] = "two";
    map[3] = "three";

    std::cout << "After adding 3 elements:\n";
    std::cout << "empty(): " << (map.empty() ? "false" : "true") << "\n";
    std::cout << "size(): " << map.size() << "\n";
    std::cout << "max_size(): " << map.max_size() << "\n";
}

// Demonstrates modifier methods
void demonstrate_map_modifiers() {
    std::cout << "\n=== MAP MODIFIERS ===\n";

    std::map<int, std::string> map;

    // insert() - various forms
    auto [it1, inserted1] = map.insert({1, "one"});
    std::cout << "insert({1, \"one\"}): inserted=" << inserted1 << ", value=" << it1->second << "\n";

    // insert() won't replace existing key
    auto [it2, inserted2] = map.insert({1, "ONE"});
    std::cout << "insert({1, \"ONE\"}) again: inserted=" << inserted2 << ", value=" << it2->second << "\n";

    // insert() with hint
    auto hint = map.end();
    map.insert(hint, {2, "two"});
    std::cout << "After insert with hint: size=" << map.size() << "\n";

    // insert_or_assign() (C++17) - inserts or updates
    auto [it3, inserted3] = map.insert_or_assign(1, "ONE");
    std::cout << "insert_or_assign(1, \"ONE\"): inserted=" << inserted3 << ", value=" << it3->second << "\n";

    // emplace() (C++11) - construct in place
    auto [it4, inserted4] = map.emplace(3, "three");
    std::cout << "emplace(3, \"three\"): inserted=" << inserted4 << "\n";

    // emplace_hint() - construct with hint
    map.emplace_hint(map.end(), 4, "four");
    std::cout << "After emplace_hint: size=" << map.size() << "\n";

    // try_emplace() (C++17) - doesn't move from rvalues if key exists
    map.try_emplace(5, "five");
    map.try_emplace(5, "FIVE");  // Won't replace
    std::cout << "After try_emplace(5): map[5]=" << map[5] << "\n";

    // erase() - by key
    size_t erased = map.erase(2);
    std::cout << "erase(2): count=" << erased << ", size=" << map.size() << "\n";

    // erase() - by iterator
    auto it = map.find(3);
    if (it != map.end()) {
        map.erase(it);
        std::cout << "Erased key 3, size=" << map.size() << "\n";
    }

    // clear() - remove all elements
    map.clear();
    std::cout << "After clear(): size=" << map.size() << "\n";

    // swap()
    std::map<int, std::string> map2 = {{10, "ten"}, {20, "twenty"}};
    map = {{1, "one"}, {2, "two"}};
    map.swap(map2);
    std::cout << "After swap - map.size()=" << map.size() << ", map2.size()=" << map2.size() << "\n";
}

// Demonstrates lookup methods
void demonstrate_map_lookup() {
    std::cout << "\n=== MAP LOOKUP ===\n";

    std::map<std::string, int> map = {
        {"apple", 1},
        {"banana", 2},
        {"cherry", 3},
        {"date", 4}
    };

    // find() - returns iterator
    auto it = map.find("banana");
    if (it != map.end()) {
        std::cout << "find(\"banana\"): key=" << it->first << ", value=" << it->second << "\n";
    }

    // count() - returns 0 or 1 for map (can be > 1 for multimap)
    std::cout << "count(\"cherry\"): " << map.count("cherry") << "\n";
    std::cout << "count(\"elderberry\"): " << map.count("elderberry") << "\n";

    // contains() (C++20) - returns bool
    std::cout << "contains(\"apple\"): " << (map.contains("apple") ? "true" : "false") << "\n";
    std::cout << "contains(\"fig\"): " << (map.contains("fig") ? "true" : "false") << "\n";

    // lower_bound() - first element not less than key
    auto lb = map.lower_bound("cherry");
    std::cout << "lower_bound(\"cherry\"): " << lb->first << "\n";

    // upper_bound() - first element greater than key
    auto ub = map.upper_bound("cherry");
    std::cout << "upper_bound(\"cherry\"): " << ub->first << "\n";

    // equal_range() - range of elements matching key
    auto [first, last] = map.equal_range("banana");
    std::cout << "equal_range(\"banana\"): ";
    for (auto i = first; i != last; ++i) {
        std::cout << i->first << "=" << i->second << " ";
    }
    std::cout << "\n";
}

// Demonstrates custom comparator
void demonstrate_map_custom_comparator() {
    std::cout << "\n=== MAP WITH CUSTOM COMPARATOR ===\n";

    // Map with custom comparator (descending order)
    struct DescendingCompare {
        bool operator()(int a, int b) const {
            return a > b;  // Reverse order
        }
    };

    std::map<int, std::string, DescendingCompare> map = {
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"}
    };

    std::cout << "Map with descending order:\n";
    for (const auto& [key, value] : map) {
        std::cout << std::format("  {}: {}\n", key, value);
    }

    // Map with lambda comparator (C++20)
    auto cmp = [](int a, int b) { return a > b; };
    std::map<int, std::string, decltype(cmp)> map2(cmp);
    map2 = {{10, "ten"}, {5, "five"}, {15, "fifteen"}};

    std::cout << "Map with lambda comparator:\n";
    for (const auto& [key, value] : map2) {
        std::cout << std::format("  {}: {}\n", key, value);
    }
}

// ============================================================================
// MULTIMAP - Allows duplicate keys
// Reference: https://en.cppreference.com/w/cpp/container/multimap
// ============================================================================

void demonstrate_multimap() {
    std::cout << "\n=== MULTIMAP (DUPLICATE KEYS) ===\n";

    std::multimap<std::string, int> multimap = {
        {"apple", 1},
        {"banana", 2},
        {"apple", 3},
        {"cherry", 4},
        {"apple", 5},
        {"banana", 6}
    };

    std::cout << "Multimap contents:\n";
    for (const auto& [key, value] : multimap) {
        std::cout << std::format("  {}: {}\n", key, value);
    }

    // count() - can return > 1
    std::cout << "count(\"apple\"): " << multimap.count("apple") << "\n";

    // equal_range() - get all values for a key
    auto [first, last] = multimap.equal_range("apple");
    std::cout << "All values for \"apple\": ";
    for (auto it = first; it != last; ++it) {
        std::cout << it->second << " ";
    }
    std::cout << "\n";

    // insert() - always inserts (doesn't check for duplicates)
    multimap.insert({"apple", 10});
    std::cout << "After insert(\"apple\", 10): count(\"apple\")=" << multimap.count("apple") << "\n";

    // erase() - removes all elements with key
    size_t erased = multimap.erase("banana");
    std::cout << "erase(\"banana\"): removed " << erased << " elements\n";

    // find() - returns iterator to first element with key
    auto it = multimap.find("apple");
    if (it != multimap.end()) {
        std::cout << "find(\"apple\") returns first: value=" << it->second << "\n";
    }
}

// Main runner for all map demonstrations
void run_all_demos() {
    demonstrate_map_construction();
    demonstrate_map_element_access();
    demonstrate_map_capacity();
    demonstrate_map_modifiers();
    demonstrate_map_lookup();
    demonstrate_map_custom_comparator();
    demonstrate_multimap();
}

} // namespace cpp26_map

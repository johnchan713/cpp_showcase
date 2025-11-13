#pragma once

#include <iostream>
#include <set>
#include <algorithm>
#include <format>

namespace cpp26_set {

// ============================================================================
// SET - Ordered set of unique elements (Red-Black Tree)
// std::set stores unique elements in sorted order
// Reference: https://en.cppreference.com/w/cpp/container/set
// ============================================================================

void demonstrate_set() {
    std::cout << "\n=== SET (Ordered, Unique) ===\n";

    // Construction with duplicates removed
    std::set<int> s = {5, 2, 8, 2, 1, 9, 2};
    
    std::cout << "Set (duplicates removed): ";
    for (auto x : s) std::cout << x << " ";
    std::cout << "\n";

    // insert()
    auto [it1, inserted1] = s.insert(3);
    std::cout << std::format("insert(3): inserted={}, value={}\n", inserted1, *it1);

    auto [it2, inserted2] = s.insert(3);  // Won't insert duplicate
    std::cout << std::format("insert(3) again: inserted={}\n", inserted2);

    // emplace()
    auto [it3, inserted3] = s.emplace(7);
    std::cout << std::format("emplace(7): inserted={}\n", inserted3);

    // find()
    auto it = s.find(5);
    if (it != s.end()) {
        std::cout << "find(5): found=" << *it << "\n";
    }

    // contains() (C++20)
    std::cout << std::format("contains(8): {}\n", s.contains(8));
    std::cout << std::format("contains(100): {}\n", s.contains(100));

    // count() - returns 0 or 1
    std::cout << std::format("count(7): {}\n", s.count(7));

    // lower_bound() / upper_bound()
    auto lb = s.lower_bound(5);
    auto ub = s.upper_bound(5);
    std::cout << std::format("lower_bound(5): {}\n", *lb);
    if (ub != s.end()) {
        std::cout << std::format("upper_bound(5): {}\n", *ub);
    }

    // equal_range()
    auto [first, last] = s.equal_range(5);
    std::cout << "equal_range(5): count=" << std::distance(first, last) << "\n";

    // erase()
    s.erase(2);
    std::cout << "After erase(2): ";
    for (auto x : s) std::cout << x << " ";
    std::cout << "\n";

    // size / empty
    std::cout << std::format("size={}, empty={}\n", s.size(), s.empty());
}

// ============================================================================
// MULTISET - Ordered set allowing duplicates
// Reference: https://en.cppreference.com/w/cpp/container/multiset
// ============================================================================

void demonstrate_multiset() {
    std::cout << "\n=== MULTISET (Ordered, Duplicates) ===\n";

    std::multiset<int> ms = {5, 2, 8, 2, 1, 9, 2};

    std::cout << "Multiset: ";
    for (auto x : ms) std::cout << x << " ";
    std::cout << "\n";

    // count() - can return > 1
    std::cout << std::format("count(2): {}\n", ms.count(2));

    // insert() - always inserts
    ms.insert(2);
    ms.insert(2);
    std::cout << std::format("After 2x insert(2): count(2)={}\n", ms.count(2));

    // equal_range() - get all copies
    auto [first, last] = ms.equal_range(2);
    std::cout << "All values for 2: ";
    for (auto it = first; it != last; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // erase() - removes all copies
    size_t erased = ms.erase(2);
    std::cout << std::format("erase(2): removed {} elements\n", erased);

    std::cout << "After erase: ";
    for (auto x : ms) std::cout << x << " ";
    std::cout << "\n";
}

void run_all_demos() {
    demonstrate_set();
    demonstrate_multiset();
}

} // namespace cpp26_set

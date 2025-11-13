#pragma once

#include <iostream>
#include <set>
#include <algorithm>
#include <format>
#include <vector>

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

// ============================================================================
// SET BOUNDS - Comprehensive upper_bound/lower_bound examples
// ============================================================================
void demonstrate_set_bounds() {
    std::cout << "\n=== SET BOUNDS (lower_bound / upper_bound) ===\n";

    std::set<int> s = {-10, -1, 1, 2};

    // lower_bound() - first element >= value
    auto it = s.lower_bound(-1);
    std::cout << std::format("lower_bound(-1): {}\n", *it);

    it = s.lower_bound(0);
    std::cout << std::format("lower_bound(0): {}\n", *it);

    // upper_bound() - first element > value
    it = s.upper_bound(-1);
    std::cout << std::format("upper_bound(-1): {}\n", *it);

    it = s.upper_bound(2);
    if (it == s.end()) {
        std::cout << "upper_bound(2): end() (no element > 2)\n";
    }

    // Practical example: finding range
    s = {-10, -5, -1, 1, 5, 10};
    std::cout << "\nSet: {-10, -5, -1, 1, 5, 10}\n";

    // Find all elements in range [0, 6)
    auto lb = s.lower_bound(0);   // First >= 0
    auto ub = s.upper_bound(6);   // First > 6
    std::cout << "Elements in [0, 6): ";
    for (auto i = lb; i != ub; ++i) {
        std::cout << *i << " ";
    }
    std::cout << "\n";
}

// ============================================================================
// SET WITH PAIRS - Application for range finding
// ============================================================================
void demonstrate_set_pairs() {
    std::cout << "\n=== SET WITH PAIRS (Range Finding) ===\n";

    // Store ranges as pairs (start, end)
    std::set<std::pair<int, int>> ranges;
    ranges.insert({2, 3});
    ranges.insert({4, 5});
    ranges.insert({7, 9});
    ranges.insert({10, 15});

    std::cout << "Ranges: ";
    for (const auto& [start, end] : ranges) {
        std::cout << std::format("[{}, {}] ", start, end);
    }
    std::cout << "\n";

    // Find which range a number falls into
    auto find_range = [&ranges](int x) {
        // upper_bound finds first range whose start > x
        auto it = ranges.upper_bound({x, INT_MAX});
        if (it != ranges.begin()) {
            --it;
            if (it->first <= x && x <= it->second) {
                std::cout << std::format("{} is in range [{}, {}]\n", x, it->first, it->second);
                return;
            }
        }
        std::cout << std::format("{} is not in any range\n", x);
    };

    find_range(3);   // In [2, 3]
    find_range(8);   // In [7, 9]
    find_range(6);   // Not in any range
    find_range(12);  // In [10, 15]
}

// ============================================================================
// SET ALGORITHMS - Operations on multiple sets
// ============================================================================
void demonstrate_set_algorithms() {
    std::cout << "\n=== SET ALGORITHMS ===\n";

    std::set<int> a = {1, 2, 3, 4, 5};
    std::set<int> b = {3, 4, 5, 6, 7};

    std::cout << "Set A: ";
    for (auto x : a) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "Set B: ";
    for (auto x : b) std::cout << x << " ";
    std::cout << "\n";

    // set_union() - elements in A or B
    std::vector<int> union_result;
    std::set_union(a.begin(), a.end(), b.begin(), b.end(),
                   std::back_inserter(union_result));
    std::cout << "set_union(A, B): ";
    for (auto x : union_result) std::cout << x << " ";
    std::cout << "\n";

    // set_intersection() - elements in both A and B
    std::vector<int> intersection_result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                          std::back_inserter(intersection_result));
    std::cout << "set_intersection(A, B): ";
    for (auto x : intersection_result) std::cout << x << " ";
    std::cout << "\n";

    // set_difference() - elements in A but not in B
    std::vector<int> diff_result;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(),
                        std::back_inserter(diff_result));
    std::cout << "set_difference(A - B): ";
    for (auto x : diff_result) std::cout << x << " ";
    std::cout << "\n";

    // set_symmetric_difference() - elements in A or B but not both
    std::vector<int> sym_diff_result;
    std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(),
                                  std::back_inserter(sym_diff_result));
    std::cout << "set_symmetric_difference(A △ B): ";
    for (auto x : sym_diff_result) std::cout << x << " ";
    std::cout << "\n";

    // includes() - check if A includes B
    std::set<int> subset = {2, 3, 4};
    bool includes_subset = std::includes(a.begin(), a.end(),
                                         subset.begin(), subset.end());
    std::cout << std::format("includes({{2,3,4}} in A): {}\n", includes_subset);

    bool includes_b = std::includes(a.begin(), a.end(), b.begin(), b.end());
    std::cout << std::format("includes(B in A): {}\n", includes_b);
}

// ============================================================================
// SET OPERATIONS - Advanced usage
// ============================================================================
void demonstrate_set_operations() {
    std::cout << "\n=== SET OPERATIONS (Advanced) ===\n";

    std::set<int> s;

    // insert() with hint
    auto it = s.insert(5).first;
    s.insert(it, 6);  // Hint: insert 6 near 5
    s.insert(it, 4);  // Hint: insert 4 near 5

    // insert range
    std::vector<int> v = {1, 2, 3, 7, 8, 9};
    s.insert(v.begin(), v.end());

    std::cout << "Set after inserts: ";
    for (auto x : s) std::cout << x << " ";
    std::cout << "\n";

    // erase by iterator
    it = s.find(5);
    if (it != s.end()) {
        s.erase(it);
        std::cout << "After erase(iterator to 5): ";
        for (auto x : s) std::cout << x << " ";
        std::cout << "\n";
    }

    // erase range
    auto first = s.find(3);
    auto last = s.find(7);
    s.erase(first, last);  // Erases [3, 7)
    std::cout << "After erase([3, 7)): ";
    for (auto x : s) std::cout << x << " ";
    std::cout << "\n";

    // clear()
    s.clear();
    std::cout << std::format("After clear(): size={}\n", s.size());
}

// ============================================================================
// CUSTOM COMPARATOR
// ============================================================================
void demonstrate_custom_comparator() {
    std::cout << "\n=== SET WITH CUSTOM COMPARATOR ===\n";

    // Set with reverse order (descending)
    std::set<int, std::greater<int>> desc_set = {5, 2, 8, 1, 9};

    std::cout << "Descending set: ";
    for (auto x : desc_set) std::cout << x << " ";
    std::cout << "\n";

    // Custom comparator for pairs (sort by second element)
    auto cmp = [](const std::pair<int, std::string>& a,
                  const std::pair<int, std::string>& b) {
        return a.second < b.second;
    };

    std::set<std::pair<int, std::string>, decltype(cmp)> custom_set(cmp);
    custom_set.insert({1, "banana"});
    custom_set.insert({2, "apple"});
    custom_set.insert({3, "cherry"});

    std::cout << "Custom comparator (by string): ";
    for (const auto& [id, name] : custom_set) {
        std::cout << name << " ";
    }
    std::cout << "\n";
}

void run_all_demos() {
    demonstrate_set();
    demonstrate_multiset();
    demonstrate_set_bounds();
    demonstrate_set_pairs();
    demonstrate_set_algorithms();
    demonstrate_set_operations();
    demonstrate_custom_comparator();
}

} // namespace cpp26_set

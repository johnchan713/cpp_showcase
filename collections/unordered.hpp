#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <format>

namespace cpp26_unordered {

// ============================================================================
// UNORDERED_MAP - Hash map (O(1) average lookup)
// Reference: https://en.cppreference.com/w/cpp/container/unordered_map
// ============================================================================

void demonstrate_unordered_map() {
    std::cout << "\n=== UNORDERED_MAP (Hash Map) ===\n";

    std::unordered_map<std::string, int> umap = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };

    // operator[]
    umap["David"] = 40;
    std::cout << std::format("umap[\"Alice\"]: {}\n", umap["Alice"]);

    // insert()
    auto [it1, inserted1] = umap.insert({"Eve", 28});
    std::cout << std::format("insert Eve: inserted={}\n", inserted1);

    // emplace()
    umap.emplace("Frank", 32);
    
    // try_emplace() (C++17)
    umap.try_emplace("Alice", 100);  // Won't overwrite

    std::cout << "All elements:\n";
    for (const auto& [key, value] : umap) {
        std::cout << std::format("  {}: {}\n", key, value);
    }

    // find()
    auto it = umap.find("Bob");
    if (it != umap.end()) {
        std::cout << std::format("find(Bob): {}\n", it->second);
    }

    // contains() (C++20)
    std::cout << std::format("contains(Charlie): {}\n", umap.contains("Charlie"));

    // erase()
    umap.erase("David");
    std::cout << std::format("After erase(David): size={}\n", umap.size());

    // Hash function stats
    std::cout << std::format("Bucket count: {}\n", umap.bucket_count());
    std::cout << std::format("Load factor: {:.2f}\n", umap.load_factor());
    std::cout << std::format("Max load factor: {:.2f}\n", umap.max_load_factor());

    // reserve()
    umap.reserve(100);
    std::cout << std::format("After reserve(100): bucket_count={}\n", umap.bucket_count());
}

// ============================================================================
// UNORDERED_SET - Hash set (O(1) average lookup)
// Reference: https://en.cppreference.com/w/cpp/container/unordered_set
// ============================================================================

void demonstrate_unordered_set() {
    std::cout << "\n=== UNORDERED_SET (Hash Set) ===\n";

    std::unordered_set<int> uset = {5, 2, 8, 2, 1, 9};

    std::cout << "Set elements (unordered): ";
    for (auto x : uset) std::cout << x << " ";
    std::cout << "\n";

    // insert()
    auto [it1, inserted1] = uset.insert(3);
    std::cout << std::format("insert(3): inserted={}\n", inserted1);

    auto [it2, inserted2] = uset.insert(3);
    std::cout << std::format("insert(3) again: inserted={}\n", inserted2);

    // emplace()
    uset.emplace(7);

    // find()
    auto it = uset.find(5);
    if (it != uset.end()) {
        std::cout << "find(5): found\n";
    }

    // contains() (C++20)
    std::cout << std::format("contains(8): {}\n", uset.contains(8));

    // count()
    std::cout << std::format("count(7): {}\n", uset.count(7));

    // erase()
    uset.erase(2);
    std::cout << "After erase(2): ";
    for (auto x : uset) std::cout << x << " ";
    std::cout << "\n";

    std::cout << std::format("size={}, bucket_count={}\n", uset.size(), uset.bucket_count());
}

void run_all_demos() {
    demonstrate_unordered_map();
    demonstrate_unordered_set();
}

} // namespace cpp26_unordered

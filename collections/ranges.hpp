#pragma once

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <format>

namespace cpp26_ranges {

// ============================================================================
// RANGES (C++20) - Modern functional-style operations
// Reference: https://en.cppreference.com/w/cpp/ranges
// ============================================================================

void demonstrate_range_views() {
    std::cout << "\n=== RANGE VIEWS (C++20) ===\n";

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // filter view
    auto evens = v | std::views::filter([](int x) { return x % 2 == 0; });
    std::cout << "filter (evens): ";
    for (auto x : evens) std::cout << x << " ";
    std::cout << "\n";

    // transform view
    auto doubled = v | std::views::transform([](int x) { return x * 2; });
    std::cout << "transform (*2): ";
    for (auto x : doubled) std::cout << x << " ";
    std::cout << "\n";

    // Chaining: filter then transform
    auto even_doubled = v
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * 2; });
    std::cout << "filter + transform: ";
    for (auto x : even_doubled) std::cout << x << " ";
    std::cout << "\n";

    // take view - first N elements
    auto first_5 = v | std::views::take(5);
    std::cout << "take(5): ";
    for (auto x : first_5) std::cout << x << " ";
    std::cout << "\n";

    // drop view - skip first N elements
    auto skip_5 = v | std::views::drop(5);
    std::cout << "drop(5): ";
    for (auto x : skip_5) std::cout << x << " ";
    std::cout << "\n";

    // reverse view
    auto reversed = v | std::views::reverse;
    std::cout << "reverse: ";
    for (auto x : reversed) std::cout << x << " ";
    std::cout << "\n";

    // elements view (for tuples/pairs)
    std::vector<std::pair<int, std::string>> pairs = {
        {1, "one"}, {2, "two"}, {3, "three"}
    };
    auto keys = pairs | std::views::elements<0>;
    std::cout << "elements<0> (keys): ";
    for (auto x : keys) std::cout << x << " ";
    std::cout << "\n";

    // keys view / values view (for maps)
    // auto keys = map | std::views::keys;
    // auto values = map | std::views::values;
}

void demonstrate_range_factories() {
    std::cout << "\n=== RANGE FACTORIES (C++20) ===\n";

    // iota view - infinite sequence
    auto numbers = std::views::iota(1) | std::views::take(10);
    std::cout << "iota(1) | take(10): ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";

    // iota with bounds
    auto range = std::views::iota(5, 15);
    std::cout << "iota(5, 15): ";
    for (auto x : range) std::cout << x << " ";
    std::cout << "\n";

    // single view
    auto single = std::views::single(42);
    std::cout << "single(42): " << *single.begin() << "\n";

    // empty view
    auto empty = std::views::empty<int>;
    std::cout << "empty view size: " << std::ranges::distance(empty) << "\n";
}

void demonstrate_range_algorithms() {
    std::cout << "\n=== RANGE ALGORITHMS (C++20) ===\n";

    std::vector<int> v = {5, 2, 8, 1, 9, 3, 7};

    // ranges::sort
    std::ranges::sort(v);
    std::cout << "ranges::sort: ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // ranges::reverse
    std::ranges::reverse(v);
    std::cout << "ranges::reverse: ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // ranges::find
    auto it = std::ranges::find(v, 7);
    if (it != v.end()) {
        std::cout << std::format("ranges::find(7): found at index {}\n", 
                                 std::distance(v.begin(), it));
    }

    // ranges::count_if
    int count = std::ranges::count_if(v, [](int x) { return x > 5; });
    std::cout << std::format("ranges::count_if (>5): {}\n", count);

    // ranges::all_of / any_of / none_of
    bool all_positive = std::ranges::all_of(v, [](int x) { return x > 0; });
    bool any_gt8 = std::ranges::any_of(v, [](int x) { return x > 8; });
    bool none_negative = std::ranges::none_of(v, [](int x) { return x < 0; });

    std::cout << std::format("all_of (positive): {}\n", all_positive);
    std::cout << std::format("any_of (>8): {}\n", any_gt8);
    std::cout << std::format("none_of (negative): {}\n", none_negative);

    // ranges::copy
    std::vector<int> dest;
    std::ranges::copy(v, std::back_inserter(dest));
    std::cout << "ranges::copy: dest.size=" << dest.size() << "\n";

    // ranges::transform
    std::vector<int> doubled;
    std::ranges::transform(v, std::back_inserter(doubled),
                          [](int x) { return x * 2; });
    std::cout << "ranges::transform: ";
    for (auto x : doubled) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_projection() {
    std::cout << "\n=== PROJECTIONS (C++20) ===\n";

    struct Person {
        std::string name;
        int age;
    };

    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };

    // Sort by age using projection
    std::ranges::sort(people, {}, &Person::age);
    
    std::cout << "Sorted by age:\n";
    for (const auto& p : people) {
        std::cout << std::format("  {}: {}\n", p.name, p.age);
    }

    // Find by name using projection
    auto it = std::ranges::find(people, "Bob", &Person::name);
    if (it != people.end()) {
        std::cout << std::format("Found Bob, age: {}\n", it->age);
    }
}

void run_all_demos() {
    demonstrate_range_views();
    demonstrate_range_factories();
    demonstrate_range_algorithms();
    demonstrate_projection();
}

} // namespace cpp26_ranges

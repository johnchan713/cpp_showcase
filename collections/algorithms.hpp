#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <format>

namespace cpp26_algorithms {

// ============================================================================
// STL ALGORITHMS - Comprehensive coverage of <algorithm> and <numeric>
// Reference: https://en.cppreference.com/w/cpp/algorithm
// ============================================================================

void demonstrate_sorting_algorithms() {
    std::cout << "\n=== SORTING ALGORITHMS ===\n";

    // sort()
    std::vector<int> v1 = {5, 2, 8, 1, 9};
    std::sort(v1.begin(), v1.end());
    std::cout << "sort(): ";
    for (auto x : v1) std::cout << x << " ";
    std::cout << "\n";

    // sort with custom comparator
    std::sort(v1.begin(), v1.end(), std::greater<int>());
    std::cout << "sort (descending): ";
    for (auto x : v1) std::cout << x << " ";
    std::cout << "\n";

    // stable_sort()
    std::vector<int> v2 = {5, 2, 8, 1, 9, 2};
    std::stable_sort(v2.begin(), v2.end());
    std::cout << "stable_sort(): ";
    for (auto x : v2) std::cout << x << " ";
    std::cout << "\n";

    // partial_sort()
    std::vector<int> v3 = {5, 2, 8, 1, 9, 3, 7};
    std::partial_sort(v3.begin(), v3.begin() + 3, v3.end());
    std::cout << "partial_sort (first 3): ";
    for (auto x : v3) std::cout << x << " ";
    std::cout << "\n";

    // nth_element()
    std::vector<int> v4 = {5, 2, 8, 1, 9, 3, 7};
    std::nth_element(v4.begin(), v4.begin() + 3, v4.end());
    std::cout << std::format("nth_element (4th): {}\n", v4[3]);
}

void demonstrate_search_algorithms() {
    std::cout << "\n=== SEARCH ALGORITHMS ===\n";

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // find()
    auto it = std::find(v.begin(), v.end(), 5);
    std::cout << std::format("find(5): found at index {}\n", std::distance(v.begin(), it));

    // find_if()
    it = std::find_if(v.begin(), v.end(), [](int x) { return x > 7; });
    std::cout << std::format("find_if(>7): found {}\n", *it);

    // binary_search() - requires sorted range
    bool found = std::binary_search(v.begin(), v.end(), 5);
    std::cout << std::format("binary_search(5): {}\n", found);

    // lower_bound() / upper_bound()
    auto lb = std::lower_bound(v.begin(), v.end(), 5);
    auto ub = std::upper_bound(v.begin(), v.end(), 5);
    std::cout << std::format("lower_bound(5): {}, upper_bound(5): {}\n", *lb, *ub);

    // equal_range()
    auto [first, last] = std::equal_range(v.begin(), v.end(), 5);
    std::cout << std::format("equal_range(5): count={}\n", std::distance(first, last));
}

void demonstrate_modifying_algorithms() {
    std::cout << "\n=== MODIFYING ALGORITHMS ===\n";

    // copy()
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst(5);
    std::copy(src.begin(), src.end(), dst.begin());
    std::cout << "copy(): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // copy_if()
    std::vector<int> filtered;
    std::copy_if(src.begin(), src.end(), std::back_inserter(filtered),
                 [](int x) { return x % 2 == 0; });
    std::cout << "copy_if (even): ";
    for (auto x : filtered) std::cout << x << " ";
    std::cout << "\n";

    // transform()
    std::vector<int> doubled;
    std::transform(src.begin(), src.end(), std::back_inserter(doubled),
                   [](int x) { return x * 2; });
    std::cout << "transform (*2): ";
    for (auto x : doubled) std::cout << x << " ";
    std::cout << "\n";

    // fill()
    std::vector<int> v(5);
    std::fill(v.begin(), v.end(), 99);
    std::cout << "fill(99): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // generate()
    int n = 0;
    std::generate(v.begin(), v.end(), [&n] { return n++; });
    std::cout << "generate(): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // replace()
    v = {1, 2, 3, 2, 5, 2};
    std::replace(v.begin(), v.end(), 2, 99);
    std::cout << "replace(2→99): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // remove() + erase() (erase-remove idiom)
    v = {1, 2, 3, 2, 5, 2};
    v.erase(std::remove(v.begin(), v.end(), 2), v.end());
    std::cout << "remove(2): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // unique()
    v = {1, 1, 2, 2, 2, 3, 3, 4};
    v.erase(std::unique(v.begin(), v.end()), v.end());
    std::cout << "unique(): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // reverse()
    std::reverse(v.begin(), v.end());
    std::cout << "reverse(): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // rotate()
    v = {1, 2, 3, 4, 5};
    std::rotate(v.begin(), v.begin() + 2, v.end());
    std::cout << "rotate(2): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // shuffle()
    // std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});
}

void demonstrate_numeric_algorithms() {
    std::cout << "\n=== NUMERIC ALGORITHMS ===\n";

    std::vector<int> v = {1, 2, 3, 4, 5};

    // accumulate()
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << std::format("accumulate (sum): {}\n", sum);

    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
    std::cout << std::format("accumulate (product): {}\n", product);

    // inner_product()
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    int dot_product = std::inner_product(v.begin(), v.end(), v2.begin(), 0);
    std::cout << std::format("inner_product: {}\n", dot_product);

    // partial_sum()
    std::vector<int> partial;
    std::partial_sum(v.begin(), v.end(), std::back_inserter(partial));
    std::cout << "partial_sum: ";
    for (auto x : partial) std::cout << x << " ";
    std::cout << "\n";

    // adjacent_difference()
    std::vector<int> diffs;
    std::adjacent_difference(v.begin(), v.end(), std::back_inserter(diffs));
    std::cout << "adjacent_difference: ";
    for (auto x : diffs) std::cout << x << " ";
    std::cout << "\n";

    // iota()
    std::vector<int> iota_vec(10);
    std::iota(iota_vec.begin(), iota_vec.end(), 0);
    std::cout << "iota(0): ";
    for (auto x : iota_vec) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_set_algorithms() {
    std::cout << "\n=== SET ALGORITHMS ===\n";

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {3, 4, 5, 6, 7};

    // set_union()
    std::vector<int> result;
    std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(),
                   std::back_inserter(result));
    std::cout << "set_union: ";
    for (auto x : result) std::cout << x << " ";
    std::cout << "\n";

    // set_intersection()
    result.clear();
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                          std::back_inserter(result));
    std::cout << "set_intersection: ";
    for (auto x : result) std::cout << x << " ";
    std::cout << "\n";

    // set_difference()
    result.clear();
    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                        std::back_inserter(result));
    std::cout << "set_difference: ";
    for (auto x : result) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_min_max_algorithms() {
    std::cout << "\n=== MIN/MAX ALGORITHMS ===\n";

    std::vector<int> v = {5, 2, 8, 1, 9, 3, 7};

    // min / max
    std::cout << std::format("min(3, 7): {}\n", std::min(3, 7));
    std::cout << std::format("max(3, 7): {}\n", std::max(3, 7));

    // min_element / max_element
    auto min_it = std::min_element(v.begin(), v.end());
    auto max_it = std::max_element(v.begin(), v.end());
    std::cout << std::format("min_element: {}, max_element: {}\n", *min_it, *max_it);

    // minmax_element
    auto [min, max] = std::minmax_element(v.begin(), v.end());
    std::cout << std::format("minmax_element: min={}, max={}\n", *min, *max);

    // clamp (C++17)
    std::cout << std::format("clamp(5, 3, 7): {}\n", std::clamp(5, 3, 7));
    std::cout << std::format("clamp(1, 3, 7): {}\n", std::clamp(1, 3, 7));
    std::cout << std::format("clamp(10, 3, 7): {}\n", std::clamp(10, 3, 7));
}

void demonstrate_query_algorithms() {
    std::cout << "\n=== QUERY ALGORITHMS ===\n";

    std::vector<int> v = {2, 4, 6, 8, 10};

    // all_of / any_of / none_of
    bool all_even = std::all_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    bool any_gt5 = std::any_of(v.begin(), v.end(), [](int x) { return x > 5; });
    bool none_odd = std::none_of(v.begin(), v.end(), [](int x) { return x % 2 == 1; });

    std::cout << std::format("all_of (even): {}\n", all_even);
    std::cout << std::format("any_of (>5): {}\n", any_gt5);
    std::cout << std::format("none_of (odd): {}\n", none_odd);

    // count / count_if
    std::vector<int> v2 = {1, 2, 2, 3, 2, 4};
    int count_2 = std::count(v2.begin(), v2.end(), 2);
    int count_even = std::count_if(v2.begin(), v2.end(), [](int x) { return x % 2 == 0; });

    std::cout << std::format("count(2): {}\n", count_2);
    std::cout << std::format("count_if (even): {}\n", count_even);
}

void run_all_demos() {
    demonstrate_sorting_algorithms();
    demonstrate_search_algorithms();
    demonstrate_modifying_algorithms();
    demonstrate_numeric_algorithms();
    demonstrate_set_algorithms();
    demonstrate_min_max_algorithms();
    demonstrate_query_algorithms();
}

} // namespace cpp26_algorithms

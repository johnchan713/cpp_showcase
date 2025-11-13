#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
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

void demonstrate_heap_operations() {
    std::cout << "\n=== HEAP OPERATIONS ===\n";

    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

    // make_heap - converts range into a max heap
    std::make_heap(v.begin(), v.end());
    std::cout << "After make_heap (max heap): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";
    std::cout << std::format("Heap top (max element): {}\n", v.front());

    // push_heap - adds new element to heap
    v.push_back(10);
    std::push_heap(v.begin(), v.end());
    std::cout << "After push_heap(10): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << std::format("\nNew heap top: {}\n", v.front());

    // pop_heap - moves max element to end
    std::pop_heap(v.begin(), v.end());
    int max = v.back();
    v.pop_back();
    std::cout << std::format("Popped max element: {}\n", max);
    std::cout << "Heap after pop_heap: ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // sort_heap - sorts heap in ascending order (destroys heap property)
    std::sort_heap(v.begin(), v.end());
    std::cout << "After sort_heap (ascending): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // Min heap example
    std::vector<int> v2 = {3, 1, 4, 1, 5, 9, 2, 6};
    std::make_heap(v2.begin(), v2.end(), std::greater<int>());
    std::cout << "Min heap: ";
    for (auto x : v2) std::cout << x << " ";
    std::cout << std::format("\nMin heap top: {}\n", v2.front());
}

void demonstrate_partition_algorithms() {
    std::cout << "\n=== PARTITION ALGORITHMS ===\n";

    // partition - reorders elements so that those satisfying predicate come first
    std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto partition_point_it = std::partition(v1.begin(), v1.end(),
                                             [](int x) { return x % 2 == 0; });
    std::cout << "After partition (even first): ";
    for (auto x : v1) std::cout << x << " ";
    std::cout << std::format("\nPartition point index: {}\n",
                            std::distance(v1.begin(), partition_point_it));

    // stable_partition - like partition but preserves relative order
    std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto stable_part_it = std::stable_partition(v2.begin(), v2.end(),
                                                [](int x) { return x % 2 == 0; });
    std::cout << "After stable_partition (even first): ";
    for (auto x : v2) std::cout << x << " ";
    std::cout << std::format("\nStable partition point: {}\n",
                            std::distance(v2.begin(), stable_part_it));

    // partition_point - finds partition point in already partitioned range
    std::vector<int> v3 = {2, 4, 6, 8, 1, 3, 5, 7, 9};  // Already partitioned (even, then odd)
    auto pp = std::partition_point(v3.begin(), v3.end(),
                                   [](int x) { return x % 2 == 0; });
    std::cout << std::format("partition_point on pre-partitioned range: index {}\n",
                            std::distance(v3.begin(), pp));

    // is_partitioned - checks if range is partitioned
    bool is_part = std::is_partitioned(v3.begin(), v3.end(),
                                       [](int x) { return x % 2 == 0; });
    std::cout << std::format("is_partitioned (even first): {}\n", is_part);
}

void demonstrate_back_inserter() {
    std::cout << "\n=== BACK_INSERTER & ITERATORS ===\n";

    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst;

    // back_inserter - creates an insert iterator that appends elements
    std::cout << "Source: ";
    for (auto x : src) std::cout << x << " ";
    std::cout << "\n";

    // Using back_inserter with copy
    std::copy(src.begin(), src.end(), std::back_inserter(dst));
    std::cout << "After copy with back_inserter: ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // Using back_inserter with transform
    std::vector<int> squared;
    std::transform(src.begin(), src.end(), std::back_inserter(squared),
                   [](int x) { return x * x; });
    std::cout << "Squared with back_inserter: ";
    for (auto x : squared) std::cout << x << " ";
    std::cout << "\n";

    // Using back_inserter with copy_if
    std::vector<int> evens;
    std::copy_if(src.begin(), src.end(), std::back_inserter(evens),
                 [](int x) { return x % 2 == 0; });
    std::cout << "Even numbers with back_inserter: ";
    for (auto x : evens) std::cout << x << " ";
    std::cout << "\n";

    // front_inserter (for containers like deque, list)
    std::list<int> lst;
    std::copy(src.begin(), src.end(), std::front_inserter(lst));
    std::cout << "List with front_inserter (reversed): ";
    for (auto x : lst) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_permutation_algorithms() {
    std::cout << "\n=== PERMUTATION ALGORITHMS ===\n";

    // next_permutation() - generates next lexicographical permutation
    std::vector<int> v = {1, 2, 3};
    std::cout << "All permutations of {1, 2, 3}:\n";
    do {
        std::cout << "  ";
        for (auto x : v) std::cout << x << " ";
        std::cout << "\n";
    } while (std::next_permutation(v.begin(), v.end()));

    // prev_permutation()
    v = {3, 2, 1};
    std::cout << "Reverse permutations from {3, 2, 1}:\n";
    int count = 0;
    do {
        std::cout << "  ";
        for (auto x : v) std::cout << x << " ";
        std::cout << "\n";
        if (++count >= 3) break;  // Show first 3
    } while (std::prev_permutation(v.begin(), v.end()));

    // is_permutation()
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {5, 4, 3, 2, 1};
    std::vector<int> v3 = {1, 2, 3, 4, 6};
    std::cout << std::format("is_permutation(v1, v2): {}\n",
                             std::is_permutation(v1.begin(), v1.end(), v2.begin()));
    std::cout << std::format("is_permutation(v1, v3): {}\n",
                             std::is_permutation(v1.begin(), v1.end(), v3.begin()));
}

// ============================================================================
// HEAP ALGORITHMS
// ============================================================================
void demonstrate_heap_algorithms() {
    std::cout << "\n=== HEAP ALGORITHMS ===\n";

    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

    // make_heap()
    std::make_heap(v.begin(), v.end());
    std::cout << "make_heap(): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << std::format(" (max: {})\n", v.front());

    // push_heap() - add element to heap
    v.push_back(10);
    std::push_heap(v.begin(), v.end());
    std::cout << std::format("push_heap(10): max={}\n", v.front());

    // pop_heap() - move max to end
    std::pop_heap(v.begin(), v.end());
    int max = v.back();
    v.pop_back();
    std::cout << std::format("pop_heap(): removed {}\n", max);

    // sort_heap() - converts heap to sorted range
    v = {3, 1, 4, 1, 5, 9, 2, 6};
    std::make_heap(v.begin(), v.end());
    std::sort_heap(v.begin(), v.end());
    std::cout << "sort_heap(): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // is_heap()
    std::cout << std::format("is_heap (after sort): {}\n", std::is_heap(v.begin(), v.end()));

    // is_heap_until()
    v = {9, 5, 4, 1, 1, 3, 2, 6, 100};  // 100 breaks heap property
    auto it = std::is_heap_until(v.begin(), v.end());
    std::cout << std::format("is_heap_until: valid up to index {}\n",
                             std::distance(v.begin(), it));
}

// ============================================================================
// MERGE ALGORITHMS
// ============================================================================
void demonstrate_merge_algorithms() {
    std::cout << "\n=== MERGE ALGORITHMS ===\n";

    // merge() - merge two sorted ranges
    std::vector<int> v1 = {1, 3, 5, 7};
    std::vector<int> v2 = {2, 4, 6, 8};
    std::vector<int> result;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(result));
    std::cout << "merge(): ";
    for (auto x : result) std::cout << x << " ";
    std::cout << "\n";

    // inplace_merge() - merge two sorted partitions in-place
    std::vector<int> v = {1, 3, 5, 7, 2, 4, 6, 8};
    std::inplace_merge(v.begin(), v.begin() + 4, v.end());
    std::cout << "inplace_merge(): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";
}

// ============================================================================
// COMPARISON ALGORITHMS
// ============================================================================
void demonstrate_comparison_algorithms() {
    std::cout << "\n=== COMPARISON ALGORITHMS ===\n";

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 3, 4, 5};
    std::vector<int> v3 = {1, 2, 3, 4, 6};

    // equal()
    bool eq = std::equal(v1.begin(), v1.end(), v2.begin());
    std::cout << std::format("equal(v1, v2): {}\n", eq);

    // mismatch() - finds first difference
    auto [it1, it2] = std::mismatch(v1.begin(), v1.end(), v3.begin());
    if (it1 != v1.end()) {
        std::cout << std::format("mismatch at index {}: {} vs {}\n",
                                 std::distance(v1.begin(), it1), *it1, *it2);
    }

    // lexicographical_compare() - dictionary order comparison
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2, 4};
    bool less = std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    std::cout << std::format("lexicographical_compare({{1,2,3}} < {{1,2,4}}): {}\n", less);
}

// ============================================================================
// SEARCH ALGORITHMS (Advanced)
// ============================================================================
void demonstrate_advanced_search() {
    std::cout << "\n=== ADVANCED SEARCH ALGORITHMS ===\n";

    // adjacent_find() - finds first pair of equal adjacent elements
    std::vector<int> v = {1, 2, 3, 3, 4, 5};
    auto it = std::adjacent_find(v.begin(), v.end());
    if (it != v.end()) {
        std::cout << std::format("adjacent_find: {} at index {}\n",
                                 *it, std::distance(v.begin(), it));
    }

    // search() - search for subsequence
    std::vector<int> haystack = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> needle = {3, 4, 5};
    it = std::search(haystack.begin(), haystack.end(), needle.begin(), needle.end());
    std::cout << std::format("search({{3,4,5}}): found at index {}\n",
                             std::distance(haystack.begin(), it));

    // find_end() - find last occurrence of subsequence
    haystack = {1, 2, 3, 1, 2, 3, 4};
    needle = {1, 2, 3};
    it = std::find_end(haystack.begin(), haystack.end(), needle.begin(), needle.end());
    std::cout << std::format("find_end({{1,2,3}}): last occurrence at index {}\n",
                             std::distance(haystack.begin(), it));

    // search_n() - search for n consecutive values
    v = {1, 2, 3, 3, 3, 4, 5};
    it = std::search_n(v.begin(), v.end(), 3, 3);  // Find 3 consecutive 3's
    std::cout << std::format("search_n(3x3): found at index {}\n",
                             std::distance(v.begin(), it));

    // find_if_not()
    v = {2, 4, 6, 8, 9, 10};
    it = std::find_if_not(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    std::cout << std::format("find_if_not(even): found {} at index {}\n",
                             *it, std::distance(v.begin(), it));
}

// ============================================================================
// SORTED RANGE CHECKS
// ============================================================================
void demonstrate_sorted_checks() {
    std::cout << "\n=== SORTED RANGE CHECKS ===\n";

    std::vector<int> v = {1, 2, 3, 4, 5};

    // is_sorted()
    std::cout << std::format("is_sorted({{1,2,3,4,5}}): {}\n",
                             std::is_sorted(v.begin(), v.end()));

    // is_sorted_until() - finds first unsorted element
    v = {1, 2, 3, 5, 4, 6};
    auto it = std::is_sorted_until(v.begin(), v.end());
    std::cout << std::format("is_sorted_until: sorted up to index {}\n",
                             std::distance(v.begin(), it));
}

// ============================================================================
// COPYING ALGORITHMS
// ============================================================================
void demonstrate_copy_variants() {
    std::cout << "\n=== COPY ALGORITHMS ===\n";

    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst(10, 0);

    // copy_backward() - copy from right to left
    std::copy_backward(src.begin(), src.end(), dst.end());
    std::cout << "copy_backward(): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // copy_n() - copy n elements
    dst.assign(10, 0);
    std::copy_n(src.begin(), 3, dst.begin());
    std::cout << "copy_n(3): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // move() - move elements (destructive)
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::move(v.begin(), v.begin() + 3, v.begin() + 2);
    std::cout << "move(): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // swap_ranges()
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {7, 8, 9};
    std::swap_ranges(v1.begin(), v1.end(), v2.begin());
    std::cout << "swap_ranges(): v1=";
    for (auto x : v1) std::cout << x << " ";
    std::cout << ", v2=";
    for (auto x : v2) std::cout << x << " ";
    std::cout << "\n";
}

// ============================================================================
// _COPY VARIANTS (non-mutating copies)
// ============================================================================
void demonstrate_copy_to_variants() {
    std::cout << "\n=== _COPY ALGORITHMS (non-mutating) ===\n";

    std::vector<int> src = {1, 2, 3, 2, 5, 2, 7};

    // remove_copy() - copy without specified value
    std::vector<int> dst;
    std::remove_copy(src.begin(), src.end(), std::back_inserter(dst), 2);
    std::cout << "remove_copy(2): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // remove_copy_if()
    dst.clear();
    std::remove_copy_if(src.begin(), src.end(), std::back_inserter(dst),
                        [](int x) { return x % 2 == 0; });
    std::cout << "remove_copy_if(even): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // unique_copy()
    src = {1, 1, 2, 2, 2, 3, 3, 4};
    dst.clear();
    std::unique_copy(src.begin(), src.end(), std::back_inserter(dst));
    std::cout << "unique_copy(): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // reverse_copy()
    src = {1, 2, 3, 4, 5};
    dst.clear();
    std::reverse_copy(src.begin(), src.end(), std::back_inserter(dst));
    std::cout << "reverse_copy(): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // rotate_copy()
    dst.clear();
    std::rotate_copy(src.begin(), src.begin() + 2, src.end(), std::back_inserter(dst));
    std::cout << "rotate_copy(2): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // replace_copy() / replace_copy_if()
    dst.clear();
    std::replace_copy(src.begin(), src.end(), std::back_inserter(dst), 3, 99);
    std::cout << "replace_copy(3→99): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";

    // partition_copy() - split into two outputs
    std::vector<int> evens, odds;
    std::partition_copy(src.begin(), src.end(),
                       std::back_inserter(evens), std::back_inserter(odds),
                       [](int x) { return x % 2 == 0; });
    std::cout << "partition_copy(): evens=";
    for (auto x : evens) std::cout << x << " ";
    std::cout << ", odds=";
    for (auto x : odds) std::cout << x << " ";
    std::cout << "\n";

    // partial_sort_copy()
    src = {5, 2, 8, 1, 9, 3, 7};
    dst.resize(3);
    std::partial_sort_copy(src.begin(), src.end(), dst.begin(), dst.end());
    std::cout << "partial_sort_copy(3): ";
    for (auto x : dst) std::cout << x << " ";
    std::cout << "\n";
}

// ============================================================================
// _N VARIANTS (counted algorithms)
// ============================================================================
void demonstrate_n_variants() {
    std::cout << "\n=== _N ALGORITHMS (counted) ===\n";

    // fill_n()
    std::vector<int> v(10);
    std::fill_n(v.begin(), 5, 42);
    std::cout << "fill_n(5, 42): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // generate_n()
    int n = 0;
    std::generate_n(v.begin(), 5, [&n] { return n++; });
    std::cout << "generate_n(5): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // for_each_n()
    std::for_each_n(v.begin(), 5, [](int& x) { x *= 2; });
    std::cout << "for_each_n(5, *2): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";
}

// ============================================================================
// FOR_EACH
// ============================================================================
void demonstrate_for_each() {
    std::cout << "\n=== FOR_EACH ===\n";

    std::vector<int> v = {1, 2, 3, 4, 5};

    // for_each() - apply function to each element
    std::for_each(v.begin(), v.end(), [](int& x) { x *= 2; });
    std::cout << "for_each(*2): ";
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // for_each with return value
    auto sum = std::for_each(v.begin(), v.end(), [sum = 0](int x) mutable {
        sum += x;
        return sum;
    });
}

// ============================================================================
// PARALLEL ALGORITHMS (C++17)
// ============================================================================
void demonstrate_parallel_algorithms() {
    std::cout << "\n=== PARALLEL ALGORITHMS (C++17) ===\n";

    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), 1);

    // reduce() - parallel sum
    int sum = std::reduce(std::execution::par, v.begin(), v.end());
    std::cout << std::format("reduce (parallel sum): {}\n", sum);

    // inclusive_scan() - parallel partial_sum
    std::vector<int> small = {1, 2, 3, 4, 5};
    std::vector<int> result(5);
    std::inclusive_scan(small.begin(), small.end(), result.begin());
    std::cout << "inclusive_scan: ";
    for (auto x : result) std::cout << x << " ";
    std::cout << "\n";

    // exclusive_scan() - partial_sum excluding current element
    std::exclusive_scan(small.begin(), small.end(), result.begin(), 0);
    std::cout << "exclusive_scan: ";
    for (auto x : result) std::cout << x << " ";
    std::cout << "\n";

    // transform_reduce() - map then reduce
    int product_sum = std::transform_reduce(small.begin(), small.end(),
                                            small.begin(), 0);
    std::cout << std::format("transform_reduce (dot product): {}\n", product_sum);
}

// ============================================================================
// SAMPLE (C++17)
// ============================================================================
void demonstrate_sample() {
    std::cout << "\n=== SAMPLE (C++17) ===\n";

    std::vector<int> v(100);
    std::iota(v.begin(), v.end(), 1);

    std::vector<int> samples;
    std::mt19937 rng{std::random_device{}()};
    std::sample(v.begin(), v.end(), std::back_inserter(samples), 10, rng);

    std::cout << "sample(10 from 100): ";
    for (auto x : samples) std::cout << x << " ";
    std::cout << "\n";
}

// ============================================================================
// SET ALGORITHMS (Extended)
// ============================================================================
void demonstrate_set_algorithms_extended() {
    std::cout << "\n=== SET ALGORITHMS (Extended) ===\n";

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {3, 4, 5, 6, 7};
    std::vector<int> result;

    // set_symmetric_difference() - elements in A or B but not both
    std::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                                  std::back_inserter(result));
    std::cout << "set_symmetric_difference: ";
    for (auto x : result) std::cout << x << " ";
    std::cout << "\n";

    // includes() - check if one set includes another
    std::vector<int> subset = {2, 3, 4};
    bool inc = std::includes(v1.begin(), v1.end(), subset.begin(), subset.end());
    std::cout << std::format("includes({{2,3,4}} in {{1,2,3,4,5}}): {}\n", inc);
}

// ============================================================================
// UNINITIALIZED MEMORY ALGORITHMS
// ============================================================================
void demonstrate_uninitialized_memory() {
    std::cout << "\n=== UNINITIALIZED MEMORY ALGORITHMS ===\n";

    // Allocate raw memory
    auto buffer = std::make_unique<char[]>(sizeof(int) * 5);
    int* ptr = reinterpret_cast<int*>(buffer.get());

    // uninitialized_fill() - construct objects with value
    std::uninitialized_fill_n(ptr, 5, 42);
    std::cout << "uninitialized_fill_n(5, 42): ";
    for (int i = 0; i < 5; ++i) std::cout << ptr[i] << " ";
    std::cout << "\n";

    // destroy() - call destructors
    std::destroy_n(ptr, 5);

    // uninitialized_default_construct()
    std::uninitialized_default_construct_n(ptr, 5);
    std::cout << "uninitialized_default_construct_n done\n";

    // uninitialized_value_construct() - zero-initialize
    std::destroy_n(ptr, 5);
    std::uninitialized_value_construct_n(ptr, 5);
    std::cout << "uninitialized_value_construct_n: ";
    for (int i = 0; i < 5; ++i) std::cout << ptr[i] << " ";
    std::cout << "\n";

    // Cleanup
    std::destroy_n(ptr, 5);
}

// ============================================================================
// C LIBRARY ALGORITHMS - qsort, bsearch
// ============================================================================
void demonstrate_c_algorithms() {
    std::cout << "\n=== C LIBRARY ALGORITHMS ===\n";

    // qsort() - C library quick sort
    int arr[] = {5, 2, 8, 1, 9, 3, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    auto compare_ints = [](const void* a, const void* b) -> int {
        return (*(int*)a - *(int*)b);
    };

    std::cout << "Before qsort: ";
    for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
    std::cout << "\n";

    std::qsort(arr, n, sizeof(int), compare_ints);

    std::cout << "After qsort: ";
    for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
    std::cout << "\n";

    // bsearch() - C library binary search
    int key = 7;
    int* result = (int*)std::bsearch(&key, arr, n, sizeof(int), compare_ints);

    if (result) {
        std::cout << std::format("bsearch found {} at index {}\n",
                                 *result, (result - arr));
    } else {
        std::cout << std::format("bsearch did not find {}\n", key);
    }

    // Search for non-existent element
    key = 100;
    result = (int*)std::bsearch(&key, arr, n, sizeof(int), compare_ints);
    if (!result) {
        std::cout << std::format("bsearch did not find {}\n", key);
    }

    // Note: Prefer C++ std::sort and std::binary_search in modern code
    std::cout << "\nNote: Use std::sort and std::binary_search in modern C++\n";
}

void run_all_demos() {
    demonstrate_sorting_algorithms();
    demonstrate_search_algorithms();
    demonstrate_modifying_algorithms();
    demonstrate_numeric_algorithms();
    demonstrate_set_algorithms();
    demonstrate_min_max_algorithms();
    demonstrate_query_algorithms();
    demonstrate_heap_operations();
    demonstrate_partition_algorithms();
    demonstrate_back_inserter();
    demonstrate_permutation_algorithms();
    demonstrate_heap_algorithms();
    demonstrate_merge_algorithms();
    demonstrate_comparison_algorithms();
    demonstrate_advanced_search();
    demonstrate_sorted_checks();
    demonstrate_copy_variants();
    demonstrate_copy_to_variants();
    demonstrate_n_variants();
    demonstrate_for_each();
    demonstrate_parallel_algorithms();
    demonstrate_sample();
    demonstrate_set_algorithms_extended();
    demonstrate_uninitialized_memory();
    demonstrate_c_algorithms();
}

} // namespace cpp26_algorithms

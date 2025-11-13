#pragma once

#include <iostream>
#include <list>
#include <forward_list>
#include <deque>
#include <algorithm>
#include <format>

namespace cpp26_list_deque {

// ============================================================================
// LIST - Doubly-linked list
// std::list allows fast insertions/deletions anywhere, but no random access
// Reference: https://en.cppreference.com/w/cpp/container/list
// ============================================================================

// Demonstrates list construction
void demonstrate_list_construction() {
    std::cout << "\n=== LIST CONSTRUCTION ===\n";

    // Default constructor
    std::list<int> l1;
    std::cout << "l1 (default): size=" << l1.size() << "\n";

    // Fill constructor
    std::list<int> l2(5, 100);
    std::cout << "l2 (5x100): size=" << l2.size() << "\n";

    // Range constructor
    std::list<int> l3(l2.begin(), l2.end());
    std::cout << "l3 (range): size=" << l3.size() << "\n";

    // Initializer list
    std::list<int> l4 = {1, 2, 3, 4, 5};
    std::cout << "l4 (init list): ";
    for (auto x : l4) std::cout << x << " ";
    std::cout << "\n";
}

// Demonstrates list element access
void demonstrate_list_element_access() {
    std::cout << "\n=== LIST ELEMENT ACCESS ===\n";

    std::list<int> lst = {10, 20, 30, 40, 50};

    // front() - first element
    std::cout << "front(): " << lst.front() << "\n";

    // back() - last element
    std::cout << "back(): " << lst.back() << "\n";

    // No operator[] or at() - list doesn't support random access!
    // Must use iterators to access middle elements
    auto it = lst.begin();
    std::advance(it, 2);  // Move to 3rd element
    std::cout << "3rd element (via iterator): " << *it << "\n";
}

// Demonstrates list modifiers
void demonstrate_list_modifiers() {
    std::cout << "\n=== LIST MODIFIERS ===\n";

    std::list<int> lst = {1, 2, 3};

    // push_back() / push_front()
    lst.push_back(4);
    lst.push_front(0);
    std::cout << "After push_back(4) and push_front(0): ";
    for (auto x : lst) std::cout << x << " ";
    std::cout << "\n";

    // emplace_back() / emplace_front()
    lst.emplace_back(5);
    lst.emplace_front(-1);
    std::cout << "After emplace operations: ";
    for (auto x : lst) std::cout << x << " ";
    std::cout << "\n";

    // insert() - insert at position
    auto it = lst.begin();
    std::advance(it, 3);
    lst.insert(it, 99);
    std::cout << "After insert(99 at pos 3): ";
    for (auto x : lst) std::cout << x << " ";
    std::cout << "\n";

    // emplace() - construct at position
    it = lst.begin();
    std::advance(it, 2);
    lst.emplace(it, 88);
    std::cout << "After emplace(88 at pos 2): ";
    for (auto x : lst) std::cout << x << " ";
    std::cout << "\n";

    // erase() - remove element
    it = lst.begin();
    std::advance(it, 2);
    lst.erase(it);
    std::cout << "After erase(pos 2): ";
    for (auto x : lst) std::cout << x << " ";
    std::cout << "\n";

    // pop_back() / pop_front()
    lst.pop_back();
    lst.pop_front();
    std::cout << "After pop operations: ";
    for (auto x : lst) std::cout << x << " ";
    std::cout << "\n";

    // clear()
    lst.clear();
    std::cout << "After clear(): size=" << lst.size() << "\n";
}

// Demonstrates list operations
void demonstrate_list_operations() {
    std::cout << "\n=== LIST OPERATIONS ===\n";

    std::list<int> lst1 = {1, 3, 5, 7, 9};
    std::list<int> lst2 = {2, 4, 6, 8, 10};

    // sort() - in-place sort
    std::list<int> unsorted = {5, 2, 8, 1, 9};
    unsorted.sort();
    std::cout << "After sort(): ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << "\n";

    // reverse() - reverse order
    unsorted.reverse();
    std::cout << "After reverse(): ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << "\n";

    // unique() - remove consecutive duplicates
    std::list<int> dups = {1, 1, 2, 2, 2, 3, 3, 4};
    dups.unique();
    std::cout << "After unique(): ";
    for (auto x : dups) std::cout << x << " ";
    std::cout << "\n";

    // merge() - merge two sorted lists
    lst1.merge(lst2);
    std::cout << "After merge(lst1, lst2): ";
    for (auto x : lst1) std::cout << x << " ";
    std::cout << " (lst2 size=" << lst2.size() << ")\n";

    // splice() - transfer elements from another list
    std::list<int> l1 = {1, 2, 3};
    std::list<int> l2 = {10, 20, 30};
    auto it = l1.begin();
    ++it;
    l1.splice(it, l2);  // Insert all of l2 before position
    std::cout << "After splice: l1=";
    for (auto x : l1) std::cout << x << " ";
    std::cout << ", l2.size=" << l2.size() << "\n";

    // remove() - remove all elements with value
    l1.remove(20);
    std::cout << "After remove(20): ";
    for (auto x : l1) std::cout << x << " ";
    std::cout << "\n";

    // remove_if() - remove elements matching predicate
    l1.remove_if([](int x) { return x > 5; });
    std::cout << "After remove_if(x > 5): ";
    for (auto x : l1) std::cout << x << " ";
    std::cout << "\n";
}

// ============================================================================
// FORWARD_LIST - Singly-linked list (C++11)
// std::forward_list is more memory-efficient than list
// Reference: https://en.cppreference.com/w/cpp/container/forward_list
// ============================================================================

void demonstrate_forward_list() {
    std::cout << "\n=== FORWARD_LIST (Singly-linked) ===\n";

    std::forward_list<int> flist = {1, 2, 3, 4, 5};

    // Only forward iteration (no rbegin/rend)
    std::cout << "Elements: ";
    for (auto x : flist) std::cout << x << " ";
    std::cout << "\n";

    // push_front() - only front operations (no push_back!)
    flist.push_front(0);
    flist.emplace_front(-1);
    std::cout << "After push_front operations: ";
    for (auto x : flist) std::cout << x << " ";
    std::cout << "\n";

    // insert_after() - insert after position (not before!)
    auto it = flist.before_begin();
    flist.insert_after(it, 99);
    std::cout << "After insert_after(before_begin, 99): ";
    for (auto x : flist) std::cout << x << " ";
    std::cout << "\n";

    // erase_after() - erase after position
    it = flist.begin();
    flist.erase_after(it);
    std::cout << "After erase_after(begin): ";
    for (auto x : flist) std::cout << x << " ";
    std::cout << "\n";

    // sort(), reverse(), unique() - same as list
    flist.sort();
    std::cout << "After sort(): ";
    for (auto x : flist) std::cout << x << " ";
    std::cout << "\n";

    flist.reverse();
    std::cout << "After reverse(): ";
    for (auto x : flist) std::cout << x << " ";
    std::cout << "\n";

    // remove() - remove all elements with value
    flist.remove(99);
    std::cout << "After remove(99): ";
    for (auto x : flist) std::cout << x << " ";
    std::cout << "\n";

    // No size() method! (for efficiency)
    // Use std::distance to count elements
    std::cout << "Size (via distance): " << std::distance(flist.begin(), flist.end()) << "\n";
}

// ============================================================================
// DEQUE - Double-ended queue
// std::deque allows fast insertions/deletions at both ends with random access
// Reference: https://en.cppreference.com/w/cpp/container/deque
// ============================================================================

void demonstrate_deque_construction() {
    std::cout << "\n=== DEQUE CONSTRUCTION ===\n";

    // Default constructor
    std::deque<int> d1;
    std::cout << "d1 (default): size=" << d1.size() << "\n";

    // Fill constructor
    std::deque<int> d2(5, 100);
    std::cout << "d2 (5x100): ";
    for (auto x : d2) std::cout << x << " ";
    std::cout << "\n";

    // Initializer list
    std::deque<int> d3 = {1, 2, 3, 4, 5};
    std::cout << "d3 (init list): ";
    for (auto x : d3) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_deque_element_access() {
    std::cout << "\n=== DEQUE ELEMENT ACCESS ===\n";

    std::deque<int> deq = {10, 20, 30, 40, 50};

    // Random access (like vector)
    std::cout << "deq[2]: " << deq[2] << "\n";
    std::cout << "at(3): " << deq.at(3) << "\n";
    std::cout << "front(): " << deq.front() << "\n";
    std::cout << "back(): " << deq.back() << "\n";
}

void demonstrate_deque_modifiers() {
    std::cout << "\n=== DEQUE MODIFIERS ===\n";

    std::deque<int> deq = {3, 4, 5};

    // Fast insertions at both ends
    deq.push_front(2);
    deq.push_back(6);
    deq.emplace_front(1);
    deq.emplace_back(7);

    std::cout << "After push/emplace operations: ";
    for (auto x : deq) std::cout << x << " ";
    std::cout << "\n";

    // Remove from both ends
    deq.pop_front();
    deq.pop_back();
    std::cout << "After pop operations: ";
    for (auto x : deq) std::cout << x << " ";
    std::cout << "\n";

    // insert() - insert at any position
    auto it = deq.begin();
    std::advance(it, 2);
    deq.insert(it, 99);
    std::cout << "After insert(99 at pos 2): ";
    for (auto x : deq) std::cout << x << " ";
    std::cout << "\n";

    // erase() - remove element
    it = deq.begin();
    std::advance(it, 2);
    deq.erase(it);
    std::cout << "After erase(pos 2): ";
    for (auto x : deq) std::cout << x << " ";
    std::cout << "\n";

    // resize()
    deq.resize(10, 88);
    std::cout << "After resize(10, 88): size=" << deq.size() << ", last=" << deq.back() << "\n";

    // shrink_to_fit() (C++11)
    deq.shrink_to_fit();
    std::cout << "After shrink_to_fit()\n";
}

void demonstrate_deque_capacity() {
    std::cout << "\n=== DEQUE CAPACITY ===\n";

    std::deque<int> deq = {1, 2, 3, 4, 5};

    std::cout << "size(): " << deq.size() << "\n";
    std::cout << "max_size(): " << deq.max_size() << "\n";
    std::cout << "empty(): " << (deq.empty() ? "true" : "false") << "\n";

    deq.resize(10);
    std::cout << "After resize(10): size=" << deq.size() << "\n";

    deq.clear();
    std::cout << "After clear(): size=" << deq.size() << ", empty=" << (deq.empty() ? "true" : "false") << "\n";
}

void demonstrate_deque_algorithms() {
    std::cout << "\n=== DEQUE WITH ALGORITHMS ===\n";

    std::deque<int> deq = {5, 2, 8, 1, 9, 3, 7};

    // std::sort
    std::sort(deq.begin(), deq.end());
    std::cout << "After sort: ";
    for (auto x : deq) std::cout << x << " ";
    std::cout << "\n";

    // std::reverse
    std::reverse(deq.begin(), deq.end());
    std::cout << "After reverse: ";
    for (auto x : deq) std::cout << x << " ";
    std::cout << "\n";

    // std::find
    auto it = std::find(deq.begin(), deq.end(), 7);
    if (it != deq.end()) {
        std::cout << "Found 7 at index: " << std::distance(deq.begin(), it) << "\n";
    }
}

// Main runner for all list/deque demonstrations
void run_all_demos() {
    // List demonstrations
    demonstrate_list_construction();
    demonstrate_list_element_access();
    demonstrate_list_modifiers();
    demonstrate_list_operations();

    // Forward list demonstrations
    demonstrate_forward_list();

    // Deque demonstrations
    demonstrate_deque_construction();
    demonstrate_deque_element_access();
    demonstrate_deque_modifiers();
    demonstrate_deque_capacity();
    demonstrate_deque_algorithms();
}

} // namespace cpp26_list_deque

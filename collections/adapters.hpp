#pragma once

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <deque>
#include <format>

namespace cpp26_adapters {

// ============================================================================
// STACK - LIFO (Last-In-First-Out) container adapter
// Reference: https://en.cppreference.com/w/cpp/container/stack
// ============================================================================

void demonstrate_stack() {
    std::cout << "\n=== STACK (LIFO) ===\n";

    std::stack<int> stk;

    // push()
    stk.push(10);
    stk.push(20);
    stk.push(30);
    
    // emplace()
    stk.emplace(40);

    std::cout << std::format("size={}, top={}\n", stk.size(), stk.top());

    // pop() and top()
    std::cout << "Popping all: ";
    while (!stk.empty()) {
        std::cout << stk.top() << " ";
        stk.pop();
    }
    std::cout << "\n";

    // Stack with custom underlying container
    std::stack<int, std::vector<int>> vec_stack;
    vec_stack.push(1);
    vec_stack.push(2);
    std::cout << std::format("Vector-based stack top: {}\n", vec_stack.top());
}

// ============================================================================
// QUEUE - FIFO (First-In-First-Out) container adapter
// Reference: https://en.cppreference.com/w/cpp/container/queue
// ============================================================================

void demonstrate_queue() {
    std::cout << "\n=== QUEUE (FIFO) ===\n";

    std::queue<int> q;

    // push()
    q.push(10);
    q.push(20);
    q.push(30);
    
    // emplace()
    q.emplace(40);

    std::cout << std::format("size={}, front={}, back={}\n", q.size(), q.front(), q.back());

    // pop() and front()
    std::cout << "Dequeuing all: ";
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "\n";
}

// ============================================================================
// PRIORITY_QUEUE - Heap-based priority queue (max-heap by default)
// Reference: https://en.cppreference.com/w/cpp/container/priority_queue
// ============================================================================

void demonstrate_priority_queue() {
    std::cout << "\n=== PRIORITY_QUEUE (Max-Heap) ===\n";

    std::priority_queue<int> pq;

    // push()
    pq.push(30);
    pq.push(10);
    pq.push(50);
    pq.push(20);
    
    // emplace()
    pq.emplace(40);

    std::cout << std::format("size={}, top={}\n", pq.size(), pq.top());

    // Extract all in priority order
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
    min_pq.push(20);

    std::cout << "Min-heap elements: ";
    while (!min_pq.empty()) {
        std::cout << min_pq.top() << " ";
        min_pq.pop();
    }
    std::cout << "\n";
}

void run_all_demos() {
    demonstrate_stack();
    demonstrate_queue();
    demonstrate_priority_queue();
}

} // namespace cpp26_adapters

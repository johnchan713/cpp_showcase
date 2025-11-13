#pragma once

#include <iostream>
#include <coroutine>
#include <optional>
#include <vector>
#include <format>

namespace cpp26_coroutines {

// ============================================================================
// COROUTINES (C++20) - Stackless coroutines for asynchronous programming
// Reference: https://en.cppreference.com/w/cpp/language/coroutines
// ============================================================================

// ============================================================================
// GENERATOR - Simple generator using coroutines
// Usage: Lazy evaluation of sequences
// ============================================================================
template<typename T>
struct Generator {
    struct promise_type {
        T current_value;
        std::exception_ptr exception;

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        void unhandled_exception() {
            exception = std::current_exception();
        }

        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }

        void return_void() {}
    };

    std::coroutine_handle<promise_type> handle;

    explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}

    ~Generator() {
        if (handle) handle.destroy();
    }

    // Move only
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    Generator(Generator&& other) noexcept : handle(other.handle) {
        other.handle = nullptr;
    }

    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (handle) handle.destroy();
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }

    // Iterator interface
    struct iterator {
        std::coroutine_handle<promise_type> handle;

        iterator& operator++() {
            handle.resume();
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return handle != other.handle && !handle.done();
        }

        T operator*() const {
            return handle.promise().current_value;
        }
    };

    iterator begin() {
        if (handle) handle.resume();
        return iterator{handle};
    }

    iterator end() {
        return iterator{nullptr};
    }
};

// Simple generator example - generate integers
Generator<int> range(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
    }
}

// Fibonacci generator
Generator<int> fibonacci(int count) {
    int a = 0, b = 1;
    for (int i = 0; i < count; ++i) {
        co_yield a;
        auto next = a + b;
        a = b;
        b = next;
    }
}

void demonstrate_generator() {
    std::cout << "\n=== GENERATOR COROUTINE ===\n";

    // Generate range
    std::cout << "Range [0, 10): ";
    for (auto value : range(0, 10)) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Fibonacci sequence
    std::cout << "First 10 Fibonacci numbers: ";
    for (auto fib : fibonacci(10)) {
        std::cout << fib << " ";
    }
    std::cout << "\n";
}

// ============================================================================
// TASK - Coroutine task for async operations
// Usage: Represents an asynchronous computation
// ============================================================================
template<typename T>
struct Task {
    struct promise_type {
        std::optional<T> result;
        std::exception_ptr exception;

        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        void return_value(T value) {
            result = value;
        }

        void unhandled_exception() {
            exception = std::current_exception();
        }
    };

    std::coroutine_handle<promise_type> handle;

    explicit Task(std::coroutine_handle<promise_type> h) : handle(h) {}

    ~Task() {
        if (handle) handle.destroy();
    }

    // Move only
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Task(Task&& other) noexcept : handle(other.handle) {
        other.handle = nullptr;
    }

    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            if (handle) handle.destroy();
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }

    T get() {
        if (!handle.done()) {
            handle.resume();
        }
        if (handle.promise().exception) {
            std::rethrow_exception(handle.promise().exception);
        }
        return *handle.promise().result;
    }
};

// Async task example
Task<int> async_computation(int x) {
    std::cout << "Computing " << x << " * 2...\n";
    co_return x * 2;
}

void demonstrate_task() {
    std::cout << "\n=== TASK COROUTINE ===\n";

    auto task = async_computation(21);
    int result = task.get();
    std::cout << std::format("Result: {}\n", result);
}

// ============================================================================
// AWAITABLE - Custom awaitable type
// Usage: Control suspension and resumption
// ============================================================================
struct Awaitable {
    int value;

    bool await_ready() const noexcept {
        std::cout << "await_ready() called\n";
        return false;  // Always suspend
    }

    void await_suspend(std::coroutine_handle<> handle) const noexcept {
        std::cout << "await_suspend() called\n";
        // Could schedule resumption here
        handle.resume();
    }

    int await_resume() const noexcept {
        std::cout << "await_resume() called\n";
        return value;
    }
};

Task<int> use_awaitable() {
    std::cout << "Before co_await\n";
    int result = co_await Awaitable{42};
    std::cout << "After co_await\n";
    co_return result;
}

void demonstrate_awaitable() {
    std::cout << "\n=== AWAITABLE ===\n";

    auto task = use_awaitable();
    int result = task.get();
    std::cout << std::format("Awaitable result: {}\n", result);
}

// ============================================================================
// CO_YIELD EXAMPLES - More yield patterns
// ============================================================================
Generator<int> even_numbers(int max) {
    for (int i = 0; i <= max; i += 2) {
        co_yield i;
    }
}

Generator<std::string> string_generator() {
    co_yield "Hello";
    co_yield "Coroutine";
    co_yield "World";
}

void demonstrate_co_yield() {
    std::cout << "\n=== CO_YIELD PATTERNS ===\n";

    std::cout << "Even numbers up to 20: ";
    for (auto num : even_numbers(20)) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    std::cout << "String generator: ";
    for (const auto& str : string_generator()) {
        std::cout << str << " ";
    }
    std::cout << "\n";
}

// ============================================================================
// COROUTINE STATE - Understanding coroutine lifetime
// ============================================================================
void demonstrate_coroutine_state() {
    std::cout << "\n=== COROUTINE STATE ===\n";

    auto gen = range(0, 5);
    auto it = gen.begin();

    std::cout << "Manual iteration:\n";
    std::cout << "  First value: " << *it << "\n";
    ++it;
    std::cout << "  Second value: " << *it << "\n";
    ++it;
    std::cout << "  Third value: " << *it << "\n";

    std::cout << "Coroutine demonstrates lazy evaluation - values computed on demand\n";
}

// ============================================================================
// PRACTICAL EXAMPLE - Tree traversal with coroutines
// ============================================================================
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : value(v), left(l), right(r) {}
};

Generator<int> inorder_traversal(TreeNode* node) {
    if (node == nullptr) {
        co_return;
    }

    // Traverse left subtree
    for (auto val : inorder_traversal(node->left)) {
        co_yield val;
    }

    // Visit current node
    co_yield node->value;

    // Traverse right subtree
    for (auto val : inorder_traversal(node->right)) {
        co_yield val;
    }
}

void demonstrate_tree_traversal() {
    std::cout << "\n=== COROUTINE TREE TRAVERSAL ===\n";

    // Build a simple binary tree
    //       4
    //      / backslash
    //     2   6
    //    / backslash / backslash
    //   1  3 5  7
    TreeNode* root = new TreeNode(4,
        new TreeNode(2,
            new TreeNode(1),
            new TreeNode(3)),
        new TreeNode(6,
            new TreeNode(5),
            new TreeNode(7))
    );

    std::cout << "Inorder traversal: ";
    for (auto val : inorder_traversal(root)) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Cleanup (simplified - proper code would use smart pointers)
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right->left;
    delete root->right->right;
    delete root->right;
    delete root;
}

// ============================================================================
// COROUTINE ADVANTAGES
// ============================================================================
void demonstrate_coroutine_advantages() {
    std::cout << "\n=== COROUTINE ADVANTAGES ===\n";
    std::cout << "Benefits of coroutines:\n";
    std::cout << "  1. Lazy evaluation - compute values on demand\n";
    std::cout << "  2. Memory efficient - no need to store entire sequence\n";
    std::cout << "  3. Natural syntax - looks like regular code\n";
    std::cout << "  4. Composable - can chain coroutines together\n";
    std::cout << "  5. State preservation - maintain state between calls\n";
    std::cout << "  6. Asynchronous programming - without callback hell\n";
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_generator();
    demonstrate_task();
    demonstrate_awaitable();
    demonstrate_co_yield();
    demonstrate_coroutine_state();
    demonstrate_tree_traversal();
    demonstrate_coroutine_advantages();
}

} // namespace cpp26_coroutines

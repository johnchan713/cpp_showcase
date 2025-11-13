#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <chrono>
#include <vector>
#include <queue>
#include <functional>
#include <format>
#include <semaphore>
#include <barrier>
#include <latch>

namespace cpp26_threading {

// ============================================================================
// BASIC THREAD - Creating and joining threads
// Usage: std::thread for concurrent execution
// ============================================================================
void demonstrate_basic_thread() {
    std::cout << "\n=== BASIC THREAD ===\n";

    auto worker = [](int id) {
        std::cout << std::format("Thread {} is working\n", id);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << std::format("Thread {} finished\n", id);
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "All threads completed\n";
}

// ============================================================================
// MUTEX - Mutual exclusion for thread safety
// Usage: std::mutex to protect shared data
// ============================================================================
void demonstrate_mutex() {
    std::cout << "\n=== MUTEX ===\n";

    std::mutex mtx;
    int shared_counter = 0;

    auto increment = [&](int id, int iterations) {
        for (int i = 0; i < iterations; ++i) {
            std::lock_guard<std::mutex> lock(mtx);  // RAII lock
            ++shared_counter;
            std::cout << std::format("Thread {}: counter = {}\n", id, shared_counter);
        }
    };

    std::thread t1(increment, 1, 3);
    std::thread t2(increment, 2, 3);

    t1.join();
    t2.join();

    std::cout << std::format("Final counter: {}\n", shared_counter);
}

// ============================================================================
// UNIQUE_LOCK - More flexible locking mechanism
// Usage: std::unique_lock for deferred/manual locking
// ============================================================================
void demonstrate_unique_lock() {
    std::cout << "\n=== UNIQUE_LOCK ===\n";

    std::mutex mtx;
    int value = 0;

    auto worker = [&]() {
        std::unique_lock<std::mutex> lock(mtx, std::defer_lock);  // Don't lock yet

        // Do some work without lock
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        lock.lock();  // Now lock
        value += 10;
        std::cout << std::format("Value updated to: {}\n", value);
        lock.unlock();  // Explicit unlock

        // Do more work without lock
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    };

    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();
}

// ============================================================================
// SHARED_MUTEX - Read-write lock (C++17)
// Usage: Multiple readers or single writer
// ============================================================================
void demonstrate_shared_mutex() {
    std::cout << "\n=== SHARED_MUTEX (Read-Write Lock) ===\n";

    std::shared_mutex sh_mtx;
    int shared_data = 0;

    auto reader = [&](int id) {
        std::shared_lock<std::shared_mutex> lock(sh_mtx);  // Shared lock for reading
        std::cout << std::format("Reader {} reads: {}\n", id, shared_data);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    };

    auto writer = [&](int id, int value) {
        std::unique_lock<std::shared_mutex> lock(sh_mtx);  // Exclusive lock for writing
        shared_data = value;
        std::cout << std::format("Writer {} writes: {}\n", id, value);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    };

    std::vector<std::thread> threads;
    threads.emplace_back(writer, 1, 42);
    threads.emplace_back(reader, 1);
    threads.emplace_back(reader, 2);
    threads.emplace_back(writer, 2, 100);

    for (auto& t : threads) {
        t.join();
    }
}

// ============================================================================
// CONDITION_VARIABLE - Thread synchronization
// Usage: Wait/notify mechanism for threads
// ============================================================================
void demonstrate_condition_variable() {
    std::cout << "\n=== CONDITION_VARIABLE ===\n";

    std::mutex mtx;
    std::condition_variable cv;
    std::queue<int> queue;
    bool finished = false;

    auto producer = [&]() {
        for (int i = 1; i <= 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            {
                std::lock_guard<std::mutex> lock(mtx);
                queue.push(i);
                std::cout << std::format("Produced: {}\n", i);
            }
            cv.notify_one();
        }
        {
            std::lock_guard<std::mutex> lock(mtx);
            finished = true;
        }
        cv.notify_all();
    };

    auto consumer = [&](int id) {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&] { return !queue.empty() || finished; });

            if (!queue.empty()) {
                int value = queue.front();
                queue.pop();
                lock.unlock();
                std::cout << std::format("Consumer {} consumed: {}\n", id, value);
            } else if (finished) {
                break;
            }
        }
    };

    std::thread prod(producer);
    std::thread cons1(consumer, 1);
    std::thread cons2(consumer, 2);

    prod.join();
    cons1.join();
    cons2.join();
}

// ============================================================================
// ATOMIC - Lock-free atomic operations
// Usage: std::atomic<T> for lock-free concurrent access
// ============================================================================
void demonstrate_atomic() {
    std::cout << "\n=== ATOMIC ===\n";

    std::atomic<int> counter{0};
    std::atomic<bool> flag{false};

    auto increment = [&](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            counter.fetch_add(1, std::memory_order_relaxed);
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(increment, 1000);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << std::format("Atomic counter: {}\n", counter.load());

    // Atomic operations
    int expected = 5000;
    bool success = counter.compare_exchange_strong(expected, 9999);
    std::cout << std::format("CAS success: {}, counter: {}\n", success, counter.load());
}

// ============================================================================
// MEMORY ORDERS - Fine-grained control over atomic operations
// Usage: Control synchronization and ordering guarantees
// ============================================================================
void demonstrate_memory_orders() {
    std::cout << "\n=== MEMORY ORDERS ===\n";

    std::atomic<int> data{0};
    std::atomic<bool> ready{false};

    // memory_order_relaxed - No synchronization, only atomicity
    std::cout << "memory_order_relaxed: No ordering guarantees, just atomicity\n";
    data.store(42, std::memory_order_relaxed);
    int val = data.load(std::memory_order_relaxed);
    std::cout << std::format("  Relaxed load: {}\n", val);

    // memory_order_acquire/release - Synchronizes with other threads
    std::cout << "\nmemory_order_release/acquire: Synchronization pair\n";
    std::thread producer([&]() {
        data.store(100, std::memory_order_relaxed);
        ready.store(true, std::memory_order_release);  // Release
    });

    std::thread consumer([&]() {
        while (!ready.load(std::memory_order_acquire));  // Acquire
        std::cout << std::format("  Acquired data: {}\n", data.load(std::memory_order_relaxed));
    });

    producer.join();
    consumer.join();

    // memory_order_seq_cst - Sequentially consistent (default, strongest)
    std::cout << "\nmemory_order_seq_cst: Sequentially consistent (default)\n";
    std::atomic<int> x{0}, y{0};
    std::atomic<int> r1{0}, r2{0};

    std::thread t1([&]() {
        x.store(1, std::memory_order_seq_cst);
        r1.store(y.load(std::memory_order_seq_cst), std::memory_order_relaxed);
    });

    std::thread t2([&]() {
        y.store(1, std::memory_order_seq_cst);
        r2.store(x.load(std::memory_order_seq_cst), std::memory_order_relaxed);
    });

    t1.join();
    t2.join();
    std::cout << std::format("  r1={}, r2={} (never both 0 with seq_cst)\n", r1.load(), r2.load());

    // memory_order_acq_rel - Both acquire and release
    std::cout << "\nmemory_order_acq_rel: Combined acquire+release\n";
    std::atomic<int> counter{0};
    counter.fetch_add(1, std::memory_order_acq_rel);
    std::cout << "  Used in fetch_add for read-modify-write\n";

    // memory_order_consume - Data dependency ordering (rarely used)
    std::cout << "\nmemory_order_consume: Data dependency ordering\n";
    std::cout << "  (Rarely used, similar to acquire but weaker)\n";
}

// ============================================================================
// COMPARE-EXCHANGE - Lock-free compare-and-swap operations
// Usage: Atomic read-modify-write with expected value check
// ============================================================================
void demonstrate_compare_exchange() {
    std::cout << "\n=== COMPARE-EXCHANGE OPERATIONS ===\n";

    std::atomic<int> value{10};

    // compare_exchange_strong - Never spuriously fails
    int expected = 10;
    bool success = value.compare_exchange_strong(expected, 20);
    std::cout << std::format("CAS strong: expected={}, new={}, success={}\n",
                             expected, value.load(), success);

    // Failed CAS updates expected
    expected = 15;  // Wrong expected value
    success = value.compare_exchange_strong(expected, 30);
    std::cout << std::format("CAS strong (fail): expected was {}, actual={}, success={}\n",
                             expected, value.load(), success);

    // compare_exchange_weak - May spuriously fail (use in loops)
    value.store(20);
    expected = 20;
    success = value.compare_exchange_weak(expected, 25);
    std::cout << std::format("CAS weak: new={}, success={}\n", value.load(), success);

    // Typical CAS loop pattern
    std::cout << "\nCAS loop pattern (increment):\n";
    value.store(100);
    int old_val = value.load();
    while (!value.compare_exchange_weak(old_val, old_val + 5)) {
        // old_val is updated on failure, retry
    }
    std::cout << std::format("  After CAS loop: {}\n", value.load());

    // With memory orders
    expected = 105;
    value.compare_exchange_strong(expected, 200,
                                   std::memory_order_release,
                                   std::memory_order_relaxed);
    std::cout << std::format("CAS with memory orders: {}\n", value.load());
}

// ============================================================================
// LOCK-FREE PROGRAMMING - Lock-free data structures
// Usage: High-performance concurrent data structures without locks
// ============================================================================

// Lock-free stack
template<typename T>
class LockFreeStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    std::atomic<Node*> head{nullptr};

public:
    void push(T value) {
        Node* new_node = new Node(value);
        new_node->next = head.load(std::memory_order_relaxed);

        while (!head.compare_exchange_weak(new_node->next, new_node,
                                            std::memory_order_release,
                                            std::memory_order_relaxed)) {
            // Retry on failure
        }
    }

    bool pop(T& result) {
        Node* old_head = head.load(std::memory_order_relaxed);

        while (old_head &&
               !head.compare_exchange_weak(old_head, old_head->next,
                                            std::memory_order_acquire,
                                            std::memory_order_relaxed)) {
            // Retry on failure
        }

        if (old_head) {
            result = old_head->data;
            delete old_head;
            return true;
        }
        return false;
    }

    bool is_lock_free() const {
        return head.is_lock_free();
    }
};

void demonstrate_lock_free() {
    std::cout << "\n=== LOCK-FREE DATA STRUCTURES ===\n";

    LockFreeStack<int> stack;

    std::cout << std::format("Stack is lock-free: {}\n", stack.is_lock_free());

    // Push from multiple threads
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&stack, i]() {
            for (int j = 0; j < 10; ++j) {
                stack.push(i * 10 + j);
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    // Pop all elements
    int value;
    int count = 0;
    while (stack.pop(value)) {
        count++;
    }

    std::cout << std::format("Pushed/popped {} elements\n", count);

    // is_lock_free for various types
    std::atomic<int> atomic_int;
    std::atomic<long long> atomic_ll;
    std::atomic<void*> atomic_ptr;

    std::cout << std::format("\nLock-free status:\n");
    std::cout << std::format("  int: {}\n", atomic_int.is_lock_free());
    std::cout << std::format("  long long: {}\n", atomic_ll.is_lock_free());
    std::cout << std::format("  pointer: {}\n", atomic_ptr.is_lock_free());
}

// ============================================================================
// ATOMIC FLAG - Simplest atomic type
// Usage: Lock-free boolean flag
// ============================================================================
void demonstrate_atomic_flag() {
    std::cout << "\n=== ATOMIC FLAG ===\n";

    std::atomic_flag flag = ATOMIC_FLAG_INIT;

    // test_and_set
    bool was_set = flag.test_and_set();
    std::cout << std::format("test_and_set() returned: {}\n", was_set);

    was_set = flag.test_and_set();
    std::cout << std::format("test_and_set() again: {}\n", was_set);

    // clear
    flag.clear();
    std::cout << "Flag cleared\n";

    was_set = flag.test_and_set();
    std::cout << std::format("test_and_set() after clear: {}\n", was_set);

    // test (C++20) - non-modifying test
    flag.clear();
    bool is_set = flag.test();
    std::cout << std::format("test() (C++20): {}\n", is_set);

    // Spinlock using atomic_flag
    std::cout << "\nSpinlock example:\n";
    std::atomic_flag spinlock = ATOMIC_FLAG_INIT;
    int shared_data = 0;

    auto worker = [&](int id) {
        // Acquire lock
        while (spinlock.test_and_set(std::memory_order_acquire));

        // Critical section
        shared_data++;
        std::cout << std::format("  Thread {} incremented to {}\n", id, shared_data);

        // Release lock
        spinlock.clear(std::memory_order_release);
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    t1.join();
    t2.join();
}

// ============================================================================
// ATOMIC OPERATIONS - All atomic operations
// Usage: Complete set of atomic operations
// ============================================================================
void demonstrate_atomic_operations() {
    std::cout << "\n=== ATOMIC OPERATIONS ===\n";

    std::atomic<int> counter{0};

    // fetch_add
    int old = counter.fetch_add(5);
    std::cout << std::format("fetch_add(5): old={}, new={}\n", old, counter.load());

    // fetch_sub
    old = counter.fetch_sub(2);
    std::cout << std::format("fetch_sub(2): old={}, new={}\n", old, counter.load());

    // fetch_and (bitwise AND)
    counter.store(0b1111);
    old = counter.fetch_and(0b1010);
    std::cout << std::format("fetch_and: old={:04b}, new={:04b}\n", old, counter.load());

    // fetch_or (bitwise OR)
    counter.store(0b1010);
    old = counter.fetch_or(0b0101);
    std::cout << std::format("fetch_or: old={:04b}, new={:04b}\n", old, counter.load());

    // fetch_xor (bitwise XOR)
    counter.store(0b1010);
    old = counter.fetch_xor(0b1100);
    std::cout << std::format("fetch_xor: old={:04b}, new={:04b}\n", old, counter.load());

    // exchange
    old = counter.exchange(100);
    std::cout << std::format("exchange(100): old={}, new={}\n", old, counter.load());

    // Atomic operations return old value
    counter.store(10);
    old = counter++;  // Equivalent to fetch_add(1)
    std::cout << std::format("operator++: returned old={}, new={}\n", old, counter.load());

    old = ++counter;  // Increment then return new
    std::cout << std::format("++operator: returned new={}\n", old);
}

// ============================================================================
// MEMORY FENCES - Explicit memory barriers
// Usage: Control memory ordering without atomic variables
// ============================================================================
void demonstrate_memory_fences() {
    std::cout << "\n=== MEMORY FENCES ===\n";

    std::atomic<bool> ready{false};
    int data = 0;

    // atomic_thread_fence - Memory barrier
    std::thread writer([&]() {
        data = 42;  // Non-atomic write
        std::atomic_thread_fence(std::memory_order_release);
        ready.store(true, std::memory_order_relaxed);
    });

    std::thread reader([&]() {
        while (!ready.load(std::memory_order_relaxed));
        std::atomic_thread_fence(std::memory_order_acquire);
        std::cout << std::format("Data read: {}\n", data);  // Non-atomic read
    });

    writer.join();
    reader.join();

    std::cout << "Fence types:\n";
    std::cout << "  atomic_thread_fence(release) - Prevents earlier writes from moving after\n";
    std::cout << "  atomic_thread_fence(acquire) - Prevents later reads from moving before\n";
    std::cout << "  atomic_thread_fence(seq_cst) - Full memory barrier\n";
}

// ============================================================================
// THREAD_LOCAL STORAGE - Expanded examples
// Usage: Per-thread variables with detailed examples
// ============================================================================
void demonstrate_thread_local_expanded() {
    std::cout << "\n=== THREAD_LOCAL EXPANDED ===\n";

    // Thread-local counter
    thread_local int tls_counter = 0;

    auto worker = [](int id, int iterations) {
        for (int i = 0; i < iterations; ++i) {
            tls_counter++;
        }
        std::cout << std::format("Thread {}: tls_counter = {}\n", id, tls_counter);
    };

    std::thread t1(worker, 1, 5);
    std::thread t2(worker, 2, 10);
    t1.join();
    t2.join();

    std::cout << "Main thread tls_counter: " << tls_counter << "\n";

    // Thread-local with class
    struct ThreadData {
        int id = 0;
        std::string name;

        ThreadData() {
            id = std::hash<std::thread::id>{}(std::this_thread::get_id()) % 1000;
            name = std::format("Thread-{}", id);
        }
    };

    thread_local ThreadData data;

    auto print_data = []() {
        std::cout << std::format("  {}: id={}\n", data.name, data.id);
    };

    std::thread t3(print_data);
    std::thread t4(print_data);
    t3.join();
    t4.join();
}

// ============================================================================
// PACKAGED_TASK EXPANDED - More examples
// Usage: Advanced packaged_task usage
// ============================================================================
void demonstrate_packaged_task_expanded() {
    std::cout << "\n=== PACKAGED_TASK EXPANDED ===\n";

    // Basic packaged_task
    std::packaged_task<int(int, int)> task([](int a, int b) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return a + b;
    });

    std::future<int> result = task.get_future();
    std::thread worker(std::move(task), 10, 20);

    std::cout << "Waiting for result...\n";
    std::cout << std::format("Result: {}\n", result.get());
    worker.join();

    // Reusable task with reset
    std::packaged_task<int(int)> reusable_task([](int x) {
        return x * x;
    });

    auto fut1 = reusable_task.get_future();
    reusable_task(5);
    std::cout << std::format("First run: {}\n", fut1.get());

    // Reset for reuse
    reusable_task.reset();
    auto fut2 = reusable_task.get_future();
    reusable_task(7);
    std::cout << std::format("After reset: {}\n", fut2.get());

    // Task with exception handling
    std::packaged_task<int()> error_task([]() -> int {
        throw std::runtime_error("Task error!");
    });

    auto error_fut = error_task.get_future();
    error_task();

    try {
        error_fut.get();
    } catch (const std::exception& e) {
        std::cout << std::format("Caught exception: {}\n", e.what());
    }
}

// ============================================================================
// THREAD_GUARD - RAII wrapper for std::thread
// Usage: Ensures thread is joined or detached
// ============================================================================
class thread_guard {
private:
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) : t(t_) {}

    ~thread_guard() {
        if (t.joinable()) {
            t.join();
        }
    }

    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
};

void demonstrate_thread_guard() {
    std::cout << "\n=== THREAD_GUARD (RAII) ===\n";

    auto worker = [](int id) {
        std::cout << std::format("Thread {} starting\n", id);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << std::format("Thread {} finished\n", id);
    };

    std::thread t1(worker, 1);
    thread_guard guard1(t1);  // RAII: automatically joins on scope exit

    std::thread t2(worker, 2);
    thread_guard guard2(t2);

    std::cout << "Threads will be automatically joined when guards go out of scope\n";
    // No need to call t1.join() or t2.join() - guards handle it
}

// ============================================================================
// FUTURE & PROMISE - Asynchronous result retrieval
// Usage: std::future/promise for async task results
// ============================================================================
void demonstrate_future_promise() {
    std::cout << "\n=== FUTURE & PROMISE ===\n";

    // Using promise/future
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread worker([&prom]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        prom.set_value(42);
        std::cout << "Promise set to 42\n";
    });

    std::cout << "Waiting for result...\n";
    int result = fut.get();
    std::cout << std::format("Future result: {}\n", result);

    worker.join();

    // Using std::async
    auto async_task = [](int x, int y) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return x + y;
    };

    std::future<int> async_result = std::async(std::launch::async, async_task, 10, 20);
    std::cout << std::format("Async result: {}\n", async_result.get());
}

// ============================================================================
// SHARED_FUTURE - Multiple threads can wait on same result
// Usage: std::shared_future for broadcasting results
// ============================================================================
void demonstrate_shared_future() {
    std::cout << "\n=== SHARED_FUTURE ===\n";

    std::promise<int> prom;
    std::shared_future<int> sfut = prom.get_future().share();

    auto waiter = [](int id, std::shared_future<int> fut) {
        std::cout << std::format("Thread {} waiting...\n", id);
        int value = fut.get();  // Multiple threads can call get()
        std::cout << std::format("Thread {} received: {}\n", id, value);
    };

    // Multiple threads can share the same future
    std::thread t1(waiter, 1, sfut);
    std::thread t2(waiter, 2, sfut);
    std::thread t3(waiter, 3, sfut);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    prom.set_value(100);  // Broadcast to all waiting threads

    t1.join();
    t2.join();
    t3.join();

    std::cout << "All threads received the shared value\n";
}

// ============================================================================
// PACKAGED_TASK - Wraps callable object for async execution
// Usage: std::packaged_task to wrap functions for threading
// ============================================================================
void demonstrate_packaged_task() {
    std::cout << "\n=== PACKAGED_TASK ===\n";

    auto task_func = [](int x) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return x * x;
    };

    std::packaged_task<int(int)> task(task_func);
    std::future<int> result = task.get_future();

    std::thread worker(std::move(task), 7);

    std::cout << std::format("Packaged task result: {}\n", result.get());

    worker.join();
}

// ============================================================================
// SEMAPHORE (C++20) - Counting semaphore for resource management
// Usage: std::counting_semaphore to limit concurrent access
// ============================================================================
void demonstrate_semaphore() {
    std::cout << "\n=== SEMAPHORE (C++20) ===\n";

    std::counting_semaphore<3> sem(3);  // Allow 3 concurrent accesses

    auto worker = [&](int id) {
        sem.acquire();
        std::cout << std::format("Thread {} entered critical section\n", id);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << std::format("Thread {} leaving critical section\n", id);
        sem.release();
    };

    std::vector<std::thread> threads;
    for (int i = 1; i <= 6; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }
}

// ============================================================================
// LATCH (C++20) - Single-use countdown synchronization
// Usage: std::latch for one-time synchronization point
// ============================================================================
void demonstrate_latch() {
    std::cout << "\n=== LATCH (C++20) ===\n";

    std::latch work_done(3);  // Wait for 3 threads

    auto worker = [&](int id) {
        std::cout << std::format("Thread {} working...\n", id);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << std::format("Thread {} done\n", id);
        work_done.count_down();
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    work_done.wait();
    std::cout << "All workers completed!\n";

    t1.join();
    t2.join();
    t3.join();
}

// ============================================================================
// BARRIER (C++20) - Reusable synchronization point
// Usage: std::barrier for multiple synchronization cycles
// ============================================================================
void demonstrate_barrier() {
    std::cout << "\n=== BARRIER (C++20) ===\n";

    auto on_completion = []() noexcept {
        std::cout << "--- Phase completed ---\n";
    };

    std::barrier sync_point(3, on_completion);

    auto worker = [&](int id) {
        for (int phase = 1; phase <= 2; ++phase) {
            std::cout << std::format("Thread {} in phase {}\n", id, phase);
            std::this_thread::sleep_for(std::chrono::milliseconds(50 * id));
            sync_point.arrive_and_wait();
        }
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();
}

// ============================================================================
// THREAD_LOCAL - Thread-local storage
// Usage: thread_local for per-thread variables
// ============================================================================
void demonstrate_thread_local() {
    std::cout << "\n=== THREAD_LOCAL ===\n";

    thread_local int tls_counter = 0;

    auto worker = [](int id) {
        for (int i = 0; i < 3; ++i) {
            ++tls_counter;
            std::cout << std::format("Thread {}: tls_counter = {}\n", id, tls_counter);
        }
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);

    t1.join();
    t2.join();

    std::cout << "Each thread has its own counter\n";
}

// ============================================================================
// JTHREAD (C++20) - Auto-joining thread with stop token
// Usage: std::jthread automatically joins on destruction
// ============================================================================
void demonstrate_jthread() {
    std::cout << "\n=== JTHREAD (C++20) ===\n";

    auto worker = [](std::stop_token stoken, int id) {
        int count = 0;
        while (!stoken.stop_requested() && count < 5) {
            std::cout << std::format("jthread {}: iteration {}\n", id, count++);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        std::cout << std::format("jthread {} stopped\n", id);
    };

    {
        std::jthread jt1(worker, 1);
        std::jthread jt2(worker, 2);

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        jt1.request_stop();

        // jthreads automatically join when going out of scope
    }

    std::cout << "jthreads auto-joined\n";
}

// ============================================================================
// HELPER FUNCTIONS - Demonstrate std::ranges algorithms like all_of
// Usage: Using all_of with threading context
// ============================================================================
void demonstrate_helper_functions() {
    std::cout << "\n=== HELPER FUNCTIONS (all_of example) ===\n";

    std::vector<std::atomic<bool>> flags(5);
    for (auto& flag : flags) {
        flag.store(false);
    }

    // Spawn threads to set flags
    std::vector<std::thread> threads;
    for (size_t i = 0; i < flags.size(); ++i) {
        threads.emplace_back([&flags, i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50 * (i + 1)));
            flags[i].store(true);
            std::cout << std::format("Flag {} set to true\n", i);
        });
    }

    // Wait for all flags to be true
    while (true) {
        bool all_true = true;
        for (const auto& flag : flags) {
            if (!flag.load()) {
                all_true = false;
                break;
            }
        }

        if (all_true) {
            std::cout << "All flags are true!\n";
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    for (auto& t : threads) {
        t.join();
    }

    // Using std::all_of on regular vector
    std::vector<int> numbers = {2, 4, 6, 8, 10};
    bool all_even = std::all_of(numbers.begin(), numbers.end(), [](int x) { return x % 2 == 0; });
    std::cout << std::format("All numbers even: {}\n", all_even);
}

// ============================================================================
// THREAD POOL - Simple thread pool implementation
// Usage: Reusable worker threads for task execution
// ============================================================================
class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;

public:
    ThreadPool(size_t num_threads) : stop(false) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });

                        if (stop && tasks.empty()) {
                            return;
                        }

                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template<typename F>
    void enqueue(F&& task) {
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(task));
        }
        condition.notify_one();
    }

    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (auto& worker : workers) {
            worker.join();
        }
    }
};

void demonstrate_thread_pool() {
    std::cout << "\n=== THREAD POOL ===\n";

    ThreadPool pool(4);

    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i] {
            std::cout << std::format("Task {} executing on thread {}\n",
                                     i, std::hash<std::thread::id>{}(std::this_thread::get_id()) % 100);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "All tasks completed\n";
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_basic_thread();
    demonstrate_mutex();
    demonstrate_unique_lock();
    demonstrate_shared_mutex();
    demonstrate_condition_variable();
    demonstrate_atomic();
    demonstrate_memory_orders();
    demonstrate_compare_exchange();
    demonstrate_lock_free();
    demonstrate_atomic_flag();
    demonstrate_atomic_operations();
    demonstrate_memory_fences();
    demonstrate_thread_local_expanded();
    demonstrate_packaged_task_expanded();
    demonstrate_thread_guard();
    demonstrate_future_promise();
    demonstrate_shared_future();
    demonstrate_packaged_task();
    demonstrate_semaphore();
    demonstrate_latch();
    demonstrate_barrier();
    demonstrate_thread_local();
    demonstrate_jthread();
    demonstrate_helper_functions();
    demonstrate_thread_pool();
}

} // namespace cpp26_threading

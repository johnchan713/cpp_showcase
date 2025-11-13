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

    // Using std::ranges::all_of on regular vector
    std::vector<int> numbers = {2, 4, 6, 8, 10};
    bool all_even = std::ranges::all_of(numbers, [](int x) { return x % 2 == 0; });
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
    demonstrate_future_promise();
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

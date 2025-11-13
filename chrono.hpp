#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <format>
#include <iomanip>
#include <ctime>

namespace cpp26_chrono {

// ============================================================================
// CHRONO - Time utilities (C++11 and beyond)
// Reference: https://en.cppreference.com/w/cpp/chrono
// ============================================================================

// ============================================================================
// DURATIONS - Represents time intervals
// ============================================================================
void demonstrate_durations() {
    std::cout << "\n=== CHRONO DURATIONS ===\n";

    // Standard duration types
    std::chrono::nanoseconds ns(1000);
    std::chrono::microseconds us(1000);
    std::chrono::milliseconds ms(1000);
    std::chrono::seconds s(60);
    std::chrono::minutes m(60);
    std::chrono::hours h(24);

    std::cout << std::format("1000 nanoseconds = {}ns\n", ns.count());
    std::cout << std::format("1000 microseconds = {}μs\n", us.count());
    std::cout << std::format("1000 milliseconds = {}ms\n", ms.count());
    std::cout << std::format("60 seconds = {}s\n", s.count());
    std::cout << std::format("60 minutes = {}min\n", m.count());
    std::cout << std::format("24 hours = {}h\n", h.count());

    // Duration arithmetic
    auto total_ms = ms + std::chrono::milliseconds(500);
    std::cout << std::format("1000ms + 500ms = {}ms\n", total_ms.count());

    // Duration conversions
    auto s_to_ms = std::chrono::duration_cast<std::chrono::milliseconds>(s);
    std::cout << std::format("60 seconds = {}ms\n", s_to_ms.count());

    // C++20 duration literals
    using namespace std::chrono_literals;
    auto d1 = 100ms;
    auto d2 = 5s;
    auto d3 = 10min;
    auto d4 = 2h;

    std::cout << std::format("Using literals: {}ms, {}s, {}min, {}h\n",
                             d1.count(), d2.count(), d3.count(), d4.count());

    // Custom duration
    using days = std::chrono::duration<int, std::ratio<86400>>;
    days week(7);
    std::cout << std::format("1 week = {} days\n", week.count());
}

// ============================================================================
// TIME POINTS - Represents points in time
// ============================================================================
void demonstrate_time_points() {
    std::cout << "\n=== TIME POINTS ===\n";

    // Get current time point
    auto now = std::chrono::system_clock::now();

    // Time since epoch
    auto epoch = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);
    std::cout << std::format("Seconds since epoch: {}\n", seconds.count());

    // Time point arithmetic
    using namespace std::chrono_literals;
    auto future = now + 24h;
    auto past = now - 1h;

    // Convert to time_t for printing
    auto now_t = std::chrono::system_clock::to_time_t(now);
    std::cout << "Current time: " << std::ctime(&now_t);

    auto future_t = std::chrono::system_clock::to_time_t(future);
    std::cout << "24 hours later: " << std::ctime(&future_t);

    auto past_t = std::chrono::system_clock::to_time_t(past);
    std::cout << "1 hour ago: " << std::ctime(&past_t);

    // Time point difference
    auto diff = future - now;
    auto diff_hours = std::chrono::duration_cast<std::chrono::hours>(diff);
    std::cout << std::format("Difference: {} hours\n", diff_hours.count());
}

// ============================================================================
// CLOCKS - Different clock types
// ============================================================================
void demonstrate_clocks() {
    std::cout << "\n=== CLOCKS ===\n";

    // system_clock - wall clock time
    auto sys_now = std::chrono::system_clock::now();
    auto sys_time = std::chrono::system_clock::to_time_t(sys_now);
    std::cout << "system_clock: " << std::ctime(&sys_time);

    // steady_clock - monotonic clock (never goes backwards)
    auto steady_start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto steady_end = std::chrono::steady_clock::now();
    auto steady_diff = steady_end - steady_start;
    std::cout << std::format("steady_clock elapsed: {}ms\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(steady_diff).count());

    // high_resolution_clock - highest precision clock
    auto hr_start = std::chrono::high_resolution_clock::now();
    // Do some work
    volatile int sum = 0;
    for (int i = 0; i < 1000000; ++i) sum += i;
    auto hr_end = std::chrono::high_resolution_clock::now();
    auto hr_diff = hr_end - hr_start;
    std::cout << std::format("high_resolution_clock elapsed: {}μs\n",
        std::chrono::duration_cast<std::chrono::microseconds>(hr_diff).count());

    // Clock properties
    std::cout << std::format("system_clock is_steady: {}\n",
        std::chrono::system_clock::is_steady);
    std::cout << std::format("steady_clock is_steady: {}\n",
        std::chrono::steady_clock::is_steady);
}

// ============================================================================
// DURATION CONVERSIONS
// ============================================================================
void demonstrate_duration_conversions() {
    std::cout << "\n=== DURATION CONVERSIONS ===\n";

    using namespace std::chrono_literals;

    auto hours = 2h;
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(hours);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(hours);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(hours);

    std::cout << std::format("2 hours = {} minutes\n", minutes.count());
    std::cout << std::format("2 hours = {} seconds\n", seconds.count());
    std::cout << std::format("2 hours = {} milliseconds\n", ms.count());

    // Implicit conversions (coarser to finer)
    std::chrono::milliseconds implicit_ms = 5s;
    std::cout << std::format("5s implicitly converts to {}ms\n", implicit_ms.count());

    // Floor, ceil, round (C++17)
    auto precise = 1500ms;
    auto floored = std::chrono::floor<std::chrono::seconds>(precise);
    auto ceiled = std::chrono::ceil<std::chrono::seconds>(precise);
    auto rounded = std::chrono::round<std::chrono::seconds>(precise);

    std::cout << std::format("1500ms floored to seconds: {}s\n", floored.count());
    std::cout << std::format("1500ms ceiled to seconds: {}s\n", ceiled.count());
    std::cout << std::format("1500ms rounded to seconds: {}s\n", rounded.count());
}

// ============================================================================
// TIMING OPERATIONS
// ============================================================================
void demonstrate_timing_operations() {
    std::cout << "\n=== TIMING OPERATIONS ===\n";

    // Measure function execution time
    auto start = std::chrono::high_resolution_clock::now();

    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;

    std::cout << std::format("Operation took:\n");
    std::cout << std::format("  {}ns\n",
        std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count());
    std::cout << std::format("  {}μs\n",
        std::chrono::duration_cast<std::chrono::microseconds>(duration).count());
    std::cout << std::format("  {}ms\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
    std::cout << std::format("  {:.3f}s\n",
        std::chrono::duration<double>(duration).count());
}

// ============================================================================
// CALENDAR (C++20) - Date and time utilities
// ============================================================================
void demonstrate_calendar() {
    std::cout << "\n=== CALENDAR (C++20) ===\n";

    using namespace std::chrono;

    // Current date/time
    auto now = system_clock::now();
    auto dp = floor<days>(now);
    year_month_day ymd{dp};

    std::cout << std::format("Today: {}-{:02}-{:02}\n",
        (int)ymd.year(), (unsigned)ymd.month(), (unsigned)ymd.day());

    // Specific date
    auto date = 2025y / November / 13d;
    std::cout << std::format("Specific date: {}\n", date);

    // Last day of month
    auto last_day = 2025y / November / std::chrono::last;
    std::cout << std::format("Last day of Nov 2025: {}\n", last_day);

    // Weekday operations
    auto wd = weekday{dp};
    std::cout << std::format("Today is weekday: {}\n", wd.c_encoding());

    // Duration since epoch in days
    auto days_since_epoch = dp.time_since_epoch();
    std::cout << std::format("Days since epoch: {}\n",
        duration_cast<days>(days_since_epoch).count());
}

// ============================================================================
// TIME ZONES (C++20)
// ============================================================================
void demonstrate_time_zones() {
    std::cout << "\n=== TIME ZONES (C++20) ===\n";

    using namespace std::chrono;

    auto now = system_clock::now();

    // UTC time
    auto utc = zoned_time{current_zone(), now};
    std::cout << std::format("UTC time: {}\n", utc);

    // Get current timezone
    auto tz = current_zone();
    std::cout << std::format("Current timezone: {}\n", tz->name());
}

// ============================================================================
// SLEEP AND WAIT
// ============================================================================
void demonstrate_sleep_wait() {
    std::cout << "\n=== SLEEP AND WAIT ===\n";

    using namespace std::chrono_literals;

    std::cout << "Sleeping for 100ms...\n";
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(100ms);
    auto end = std::chrono::steady_clock::now();
    auto actual = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << std::format("Actual sleep time: {}ms\n", actual.count());

    std::cout << "Sleeping until specific time...\n";
    auto wake_time = std::chrono::steady_clock::now() + 50ms;
    std::this_thread::sleep_until(wake_time);
    std::cout << "Woke up!\n";
}

// ============================================================================
// PRACTICAL EXAMPLES
// ============================================================================
void demonstrate_practical_examples() {
    std::cout << "\n=== PRACTICAL EXAMPLES ===\n";

    using namespace std::chrono;
    using namespace std::chrono_literals;

    // Timeout example
    auto timeout = 5s;
    auto start = steady_clock::now();
    std::cout << std::format("Waiting with {}s timeout...\n",
        duration_cast<seconds>(timeout).count());

    while (steady_clock::now() - start < timeout) {
        // Simulate checking for condition
        std::this_thread::sleep_for(100ms);
        if (steady_clock::now() - start > 500ms) {
            std::cout << "Condition met early!\n";
            break;
        }
    }

    // Rate limiting example
    std::cout << "\nRate limiting (max 5 ops/second):\n";
    auto rate_limit = 200ms;
    for (int i = 0; i < 5; ++i) {
        auto op_start = steady_clock::now();
        std::cout << std::format("  Operation {}\n", i + 1);

        auto elapsed = steady_clock::now() - op_start;
        if (elapsed < rate_limit) {
            std::this_thread::sleep_for(rate_limit - elapsed);
        }
    }

    // Benchmark template
    auto benchmark = [](auto func, const std::string& name) {
        auto start = high_resolution_clock::now();
        func();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        std::cout << std::format("{}: {}μs\n", name, duration.count());
    };

    benchmark([]() {
        volatile int sum = 0;
        for (int i = 0; i < 10000; ++i) sum += i;
    }, "Loop benchmark");
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_durations();
    demonstrate_time_points();
    demonstrate_clocks();
    demonstrate_duration_conversions();
    demonstrate_timing_operations();
    demonstrate_calendar();
    demonstrate_time_zones();
    demonstrate_sleep_wait();
    demonstrate_practical_examples();
}

} // namespace cpp26_chrono

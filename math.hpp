#pragma once

#include <iostream>
#include <cmath>
#include <numbers>
#include <numeric>
#include <format>
#include <vector>
#include <complex>

namespace cpp26_math {

// ============================================================================
// MATHEMATICAL CONSTANTS (C++20)
// std::numbers provides mathematical constants
// Reference: https://en.cppreference.com/w/cpp/numeric/constants
// ============================================================================
void demonstrate_constants() {
    std::cout << "\n=== MATHEMATICAL CONSTANTS (C++20) ===\n";

    std::cout << std::format("π (pi): {:.15f}\n", std::numbers::pi);
    std::cout << std::format("e: {:.15f}\n", std::numbers::e);
    std::cout << std::format("√2: {:.15f}\n", std::numbers::sqrt2);
    std::cout << std::format("√3: {:.15f}\n", std::numbers::sqrt3);
    std::cout << std::format("ln(2): {:.15f}\n", std::numbers::ln2);
    std::cout << std::format("ln(10): {:.15f}\n", std::numbers::ln10);
    std::cout << std::format("log₂(e): {:.15f}\n", std::numbers::log2e);
    std::cout << std::format("log₁₀(e): {:.15f}\n", std::numbers::log10e);
    std::cout << std::format("φ (phi/golden ratio): {:.15f}\n", std::numbers::phi);

    // Inverse constants
    std::cout << std::format("1/π: {:.15f}\n", std::numbers::inv_pi);
    std::cout << std::format("1/√π: {:.15f}\n", std::numbers::inv_sqrtpi);
}

// ============================================================================
// TRIGONOMETRIC FUNCTIONS
// Reference: https://en.cppreference.com/w/cpp/numeric/math
// ============================================================================
void demonstrate_trigonometry() {
    std::cout << "\n=== TRIGONOMETRIC FUNCTIONS ===\n";

    double angle = std::numbers::pi / 4;  // 45 degrees

    // Basic trig functions
    std::cout << std::format("sin(π/4): {:.6f}\n", std::sin(angle));
    std::cout << std::format("cos(π/4): {:.6f}\n", std::cos(angle));
    std::cout << std::format("tan(π/4): {:.6f}\n", std::tan(angle));

    // Inverse trig functions
    std::cout << std::format("asin(0.5): {:.6f}\n", std::asin(0.5));
    std::cout << std::format("acos(0.5): {:.6f}\n", std::acos(0.5));
    std::cout << std::format("atan(1.0): {:.6f}\n", std::atan(1.0));
    std::cout << std::format("atan2(1, 1): {:.6f}\n", std::atan2(1, 1));

    // Hyperbolic functions
    std::cout << std::format("sinh(1.0): {:.6f}\n", std::sinh(1.0));
    std::cout << std::format("cosh(1.0): {:.6f}\n", std::cosh(1.0));
    std::cout << std::format("tanh(1.0): {:.6f}\n", std::tanh(1.0));

    // Inverse hyperbolic
    std::cout << std::format("asinh(1.0): {:.6f}\n", std::asinh(1.0));
    std::cout << std::format("acosh(2.0): {:.6f}\n", std::acosh(2.0));
    std::cout << std::format("atanh(0.5): {:.6f}\n", std::atanh(0.5));
}

// ============================================================================
// EXPONENTIAL AND LOGARITHMIC FUNCTIONS
// ============================================================================
void demonstrate_exp_log() {
    std::cout << "\n=== EXPONENTIAL & LOGARITHMIC ===\n";

    // Exponential
    std::cout << std::format("exp(1.0): {:.6f}\n", std::exp(1.0));
    std::cout << std::format("exp2(3.0): {:.1f}\n", std::exp2(3.0));  // 2^3

    // Logarithms
    std::cout << std::format("log(e): {:.6f}\n", std::log(std::numbers::e));
    std::cout << std::format("log10(100): {:.1f}\n", std::log10(100));
    std::cout << std::format("log2(8): {:.1f}\n", std::log2(8));

    // Special exponential functions
    std::cout << std::format("expm1(0.01): {:.8f}\n", std::expm1(0.01));  // exp(x)-1
    std::cout << std::format("log1p(0.01): {:.8f}\n", std::log1p(0.01));  // log(1+x)
}

// ============================================================================
// POWER FUNCTIONS
// ============================================================================
void demonstrate_power() {
    std::cout << "\n=== POWER FUNCTIONS ===\n";

    std::cout << std::format("pow(2, 10): {:.1f}\n", std::pow(2, 10));
    std::cout << std::format("sqrt(16): {:.1f}\n", std::sqrt(16));
    std::cout << std::format("cbrt(27): {:.1f}\n", std::cbrt(27));  // Cube root
    std::cout << std::format("hypot(3, 4): {:.1f}\n", std::hypot(3, 4));  // √(3²+4²)

    // C++17: hypot for 3 arguments
    std::cout << std::format("hypot(2, 3, 6): {:.1f}\n", std::hypot(2, 3, 6));
}

// ============================================================================
// ROUNDING AND REMAINDER FUNCTIONS
// ============================================================================
void demonstrate_rounding() {
    std::cout << "\n=== ROUNDING FUNCTIONS ===\n";

    double value = 3.7;

    std::cout << std::format("ceil({:.1f}): {:.1f}\n", value, std::ceil(value));
    std::cout << std::format("floor({:.1f}): {:.1f}\n", value, std::floor(value));
    std::cout << std::format("trunc({:.1f}): {:.1f}\n", value, std::trunc(value));
    std::cout << std::format("round({:.1f}): {:.1f}\n", value, std::round(value));

    // Remainder functions
    std::cout << std::format("fmod(7.5, 2.3): {:.2f}\n", std::fmod(7.5, 2.3));
    std::cout << std::format("remainder(7.5, 2.3): {:.2f}\n", std::remainder(7.5, 2.3));

    // Nearest integer using current rounding mode
    std::cout << std::format("nearbyint(3.5): {:.1f}\n", std::nearbyint(3.5));
    std::cout << std::format("rint(3.5): {:.1f}\n", std::rint(3.5));
}

// ============================================================================
// FLOATING POINT MANIPULATION
// ============================================================================
void demonstrate_float_manipulation() {
    std::cout << "\n=== FLOATING POINT MANIPULATION ===\n";

    double value = 123.456;

    // Decompose into mantissa and exponent
    int exp;
    double mantissa = std::frexp(value, &exp);
    std::cout << std::format("frexp({:.3f}): mantissa={:.6f}, exponent={}\n",
                             value, mantissa, exp);

    // Reconstruct from mantissa and exponent
    double reconstructed = std::ldexp(mantissa, exp);
    std::cout << std::format("ldexp({:.6f}, {}): {:.3f}\n",
                             mantissa, exp, reconstructed);

    // Split into integer and fractional parts
    double intpart;
    double fracpart = std::modf(value, &intpart);
    std::cout << std::format("modf({:.3f}): int={:.0f}, frac={:.3f}\n",
                             value, intpart, fracpart);

    // Get exponent
    std::cout << std::format("logb({:.3f}): {}\n", value, (int)std::logb(value));
    std::cout << std::format("ilogb({:.3f}): {}\n", value, std::ilogb(value));

    // Next representable value
    std::cout << std::format("nextafter(1.0, 2.0): {:.20f}\n", std::nextafter(1.0, 2.0));
}

// ============================================================================
// COMPARISON AND CLASSIFICATION
// ============================================================================
void demonstrate_classification() {
    std::cout << "\n=== FLOATING POINT CLASSIFICATION ===\n";

    double normal = 42.0;
    double inf = INFINITY;
    double nan = NAN;
    double zero = 0.0;

    std::cout << std::format("isfinite(42.0): {}\n", std::isfinite(normal));
    std::cout << std::format("isfinite(inf): {}\n", std::isfinite(inf));

    std::cout << std::format("isinf(inf): {}\n", std::isinf(inf));
    std::cout << std::format("isnan(nan): {}\n", std::isnan(nan));

    std::cout << std::format("isnormal(42.0): {}\n", std::isnormal(normal));
    std::cout << std::format("isnormal(0.0): {}\n", std::isnormal(zero));

    std::cout << std::format("signbit(-5.0): {}\n", std::signbit(-5.0));
    std::cout << std::format("signbit(5.0): {}\n", std::signbit(5.0));

    // Copy sign
    std::cout << std::format("copysign(10, -1): {:.1f}\n", std::copysign(10, -1));
}

// ============================================================================
// NUMERIC OPERATIONS (from <numeric>)
// ============================================================================
void demonstrate_numeric_operations() {
    std::cout << "\n=== NUMERIC OPERATIONS ===\n";

    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // GCD (C++17)
    std::cout << std::format("gcd(48, 18): {}\n", std::gcd(48, 18));

    // LCM (C++17)
    std::cout << std::format("lcm(12, 18): {}\n", std::lcm(12, 18));

    // Midpoint (C++20)
    std::cout << std::format("midpoint(10, 20): {}\n", std::midpoint(10, 20));
    std::cout << std::format("midpoint(1.0, 2.0): {:.1f}\n", std::midpoint(1.0, 2.0));

    // Accumulate
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << std::format("accumulate [1..5]: {}\n", sum);

    // Inner product (dot product)
    int dot = std::inner_product(numbers.begin(), numbers.end(),
                                  numbers.begin(), 0);
    std::cout << std::format("inner_product [1..5]·[1..5]: {}\n", dot);

    // Partial sum
    std::vector<int> partial_sums;
    std::partial_sum(numbers.begin(), numbers.end(),
                     std::back_inserter(partial_sums));
    std::cout << "partial_sum [1..5]: ";
    for (auto v : partial_sums) std::cout << v << " ";
    std::cout << "\n";

    // Adjacent difference
    std::vector<int> diffs;
    std::adjacent_difference(numbers.begin(), numbers.end(),
                             std::back_inserter(diffs));
    std::cout << "adjacent_difference [1..5]: ";
    for (auto v : diffs) std::cout << v << " ";
    std::cout << "\n";

    // Iota - fill with incrementing values
    std::vector<int> iota_vec(10);
    std::iota(iota_vec.begin(), iota_vec.end(), 1);
    std::cout << "iota(1): ";
    for (auto v : iota_vec) std::cout << v << " ";
    std::cout << "\n";
}

// ============================================================================
// COMPLEX NUMBERS (C++20 improvements)
// ============================================================================
void demonstrate_complex_numbers() {
    std::cout << "\n=== COMPLEX NUMBERS ===\n";

    std::complex<double> c1(3.0, 4.0);
    std::complex<double> c2(1.0, 2.0);

    std::cout << std::format("c1 = ({:.1f}, {:.1f}i)\n", c1.real(), c1.imag());
    std::cout << std::format("c2 = ({:.1f}, {:.1f}i)\n", c2.real(), c2.imag());

    // Arithmetic
    auto sum = c1 + c2;
    auto product = c1 * c2;
    std::cout << std::format("c1 + c2 = ({:.1f}, {:.1f}i)\n", sum.real(), sum.imag());
    std::cout << std::format("c1 * c2 = ({:.1f}, {:.1f}i)\n", product.real(), product.imag());

    // Magnitude and phase
    std::cout << std::format("|c1| = {:.2f}\n", std::abs(c1));
    std::cout << std::format("arg(c1) = {:.4f} rad\n", std::arg(c1));

    // Conjugate
    auto conj = std::conj(c1);
    std::cout << std::format("conj(c1) = ({:.1f}, {:.1f}i)\n", conj.real(), conj.imag());

    // Polar form
    auto polar = std::polar(5.0, std::numbers::pi / 4);
    std::cout << std::format("polar(5, π/4) = ({:.2f}, {:.2f}i)\n",
                             polar.real(), polar.imag());
}

// ============================================================================
// SPECIAL MATH FUNCTIONS (C++17)
// ============================================================================
void demonstrate_special_functions() {
    std::cout << "\n=== SPECIAL MATH FUNCTIONS (C++17) ===\n";

    // Bessel functions
    std::cout << std::format("cyl_bessel_j(0, 1.0): {:.6f}\n", std::cyl_bessel_j(0, 1.0));

    // Legendre polynomials
    std::cout << std::format("legendre(2, 0.5): {:.6f}\n", std::legendre(2, 0.5));

    // Hermite polynomials
    std::cout << std::format("hermite(3, 1.0): {:.6f}\n", std::hermite(3, 1.0));

    // Laguerre polynomials
    std::cout << std::format("laguerre(2, 1.0): {:.6f}\n", std::laguerre(2, 1.0));

    // Beta function
    std::cout << std::format("beta(2.0, 3.0): {:.6f}\n", std::beta(2.0, 3.0));

    // Gamma functions
    std::cout << std::format("tgamma(5.0): {:.1f}\n", std::tgamma(5.0));  // 4! = 24
    std::cout << std::format("lgamma(5.0): {:.6f}\n", std::lgamma(5.0));  // log(4!)

    // Error functions
    std::cout << std::format("erf(1.0): {:.6f}\n", std::erf(1.0));
    std::cout << std::format("erfc(1.0): {:.6f}\n", std::erfc(1.0));

    // Elliptic integrals
    std::cout << std::format("ellint_1(0.5, π/4): {:.6f}\n",
                             std::ellint_1(0.5, std::numbers::pi / 4));
}

// ============================================================================
// PRACTICAL EXAMPLES
// ============================================================================
void demonstrate_practical_examples() {
    std::cout << "\n=== PRACTICAL EXAMPLES ===\n";

    // Distance between two points
    auto distance = [](double x1, double y1, double x2, double y2) {
        return std::hypot(x2 - x1, y2 - y1);
    };
    std::cout << std::format("Distance (0,0) to (3,4): {:.2f}\n", distance(0, 0, 3, 4));

    // Angle between two vectors
    auto angle = [](double x1, double y1, double x2, double y2) {
        return std::acos((x1 * x2 + y1 * y2) /
                        (std::hypot(x1, y1) * std::hypot(x2, y2)));
    };
    std::cout << std::format("Angle between (1,0) and (1,1): {:.4f} rad\n",
                             angle(1, 0, 1, 1));

    // Area of circle
    auto circle_area = [](double radius) {
        return std::numbers::pi * radius * radius;
    };
    std::cout << std::format("Area of circle (r=5): {:.2f}\n", circle_area(5));

    // Compound interest
    auto compound_interest = [](double principal, double rate, int years) {
        return principal * std::pow(1 + rate, years);
    };
    std::cout << std::format("$1000 at 5%% for 10 years: ${:.2f}\n",
                             compound_interest(1000, 0.05, 10));
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_constants();
    demonstrate_trigonometry();
    demonstrate_exp_log();
    demonstrate_power();
    demonstrate_rounding();
    demonstrate_float_manipulation();
    demonstrate_classification();
    demonstrate_numeric_operations();
    demonstrate_complex_numbers();
    demonstrate_special_functions();
    demonstrate_practical_examples();
}

} // namespace cpp26_math

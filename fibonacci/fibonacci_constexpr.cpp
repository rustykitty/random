#include <iostream>

// fibonacci at compile-time?
constexpr unsigned long long fibonacci_constexpr (unsigned char n) {
    return (n == 0 || n == 1) ? 1 : fibonacci_constexpr(n - 1) + fibonacci_constexpr(n - 2);
}

int main() { 
    constexpr unsigned char n = 93;
    constexpr unsigned long long result = fibonacci_constexpr(n);
    std::cout << result << std::endl;
}
#include <cstdio>

template <unsigned char N>
class Fibonacci {
public:
    static constexpr unsigned long long value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template <>
class Fibonacci<0> {
public:
    static constexpr unsigned long long value = 0;
};

template <>
class Fibonacci<1> {
public:
    static constexpr unsigned long long value = 1;
};

int main() {
    constexpr unsigned long long value = Fibonacci<93>::value;
    printf("%llu\n", value);
}

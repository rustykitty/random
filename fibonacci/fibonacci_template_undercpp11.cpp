#include <cstdio>

template <unsigned char N>
struct Fibonacci
{
    enum
    {
        value = Fibonacci<N-1>::value + Fibonacci<N-2>::value
    };
};

template <>
struct Fibonacci<1>
{
    enum
    {
        value = 1
    };
};

template <>
struct Fibonacci<0>
{
    enum
    {
        value = 0
    };
};

int main() {
    const unsigned long long value = Fibonacci<10>::value;
    printf("%llu\n", value);
}

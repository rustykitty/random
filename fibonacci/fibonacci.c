#include <stdio.h>

unsigned long long fibonacci(unsigned int n) {
    if (n == 0 || n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}


int main() {
    printf("%lld\n", fibonacci(100));
}
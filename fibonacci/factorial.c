#include <stdio.h>

unsigned long long factorial(unsigned int n) {
    if (n == 1) return 1;
    return factorial(n - 1) * n;
}

int main() {
    printf("%lld\n", factorial(20));
}
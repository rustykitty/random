#include <stdio.h>

unsigned long long factorial(unsigned int n) {
    unsigned long result = 1;
    mult: 
    result *= n;
    --n;
    if (n != 1) goto mult;
    return result;
}

int main() {
    printf("%lld\n", factorial(20));
}
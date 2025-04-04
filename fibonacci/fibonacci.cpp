#include <iostream>

unsigned long long fibonacci (unsigned char n) {
    if (n == 0 || n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{ 
    std::cout << fibonacci(93) << std::endl;
}
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

int main() {
    void* a = 0;
    void* b = SIZE_MAX;
    ptrdiff_t diff = b - a;
    printf("%td", diff);
}

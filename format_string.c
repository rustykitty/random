#include <stdio.h>
#include "format_string.h"

int main() {
    int x = 999;
    int y = 420;
    char* c = "Goodbye world";
    puts(rustykitty_format_string("x is %d and y is %d", x, y));
    puts(rustykitty_format_string("%s", c));
    return 0;
}
// Binary "Whitespace": Whitespace instructions, but as a machine code-style language
// https://esolangs.org/wiki/Whitespace

/*
01 -> space
10 -> tab
11 -> LF
*/

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    FILE* file = argc == 0 ? stdin : fopen(argv[1], "r");

    int c;
    while ((c = fgetc(file)) != EOF) {
        // assuming CHAR_BIT is 8
        uint8_t arr[4] = {
            (c & 0b11000000) >> 6,
            (c & 0b00110000) >> 4,
            (c & 0b00001100) >> 2,
            (c & 0b00000011) >> 0
        };
        for (int i = 0; i < 4; ++i) {
            char res = arr[i] == 0b01 ? ' '  :
                       arr[i] == 0b10 ? '\t' :
                       arr[i] == 0b11 ? '\n' :
                                        '\0' ;
            if (res) putchar(res);
        }
    }

    return 0;

}
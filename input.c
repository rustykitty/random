/**
 * Python style `input()` functions
 * 
 * Compiled to .o with c99 - c23, c++03 - c++20
 */

#ifndef RUSTYKITTY_INPUT_C

#define RUSTYKITTY_INPUT_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// just in case
#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_SIZE 16

char* finput(FILE* stream) {
    char buf[BUFFER_SIZE];
    size_t res_size; // indeterminate value
    char* res = NULL;
    while ( 1 ) {
        char* success = fgets(buf, BUFFER_SIZE, stream);
        if (!success) {
            return NULL; // caller will check for feof() / ferror()
        } 
        // append contents of buf onto res
        if (!res) {
            res = (char*) malloc(BUFFER_SIZE);
            res_size = BUFFER_SIZE;
        } else if (strlen(res) + strlen(buf) >= res_size) {
            res = (char*) realloc(res, res_size * 2);
        }
        strcat(res, buf);
        if (strchr(buf, '\n') || feof(stream)) {
            return (char*) realloc(res, strlen(res) + 1);
        }
    }
}

char* input() {
    return finput(stdin);
}

/* the functions below are the same as the functions above, with the added ability for a `prompt` param */

char* fpinput(FILE* stream, char* prompt) {
    if (fputs(prompt, stream) == EOF) return NULL;
    return finput(stream);
}

char* pinput(char* prompt) {
    return fpinput(stdin, prompt);
}

#undef BUFFER_SIZE

#ifdef __cplusplus
}
#endif

#endif
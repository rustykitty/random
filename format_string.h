#ifndef RUSTYKITTY_FORMAT_STRING_H
#define RUSTYKITTY_FORMAT_STRING_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>

char* rustykitty_format_string(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    va_list args2;
    va_copy(args2, args);
    int len = vsnprintf(NULL, 0, fmt, args);
    if (len < 0) return NULL;
    va_end(args);
    char* str = (char*)malloc(len + 1);
    if (str == NULL) return NULL;
    va_start(args2, fmt);
    vsnprintf(str, len + 1, fmt, args2);
    va_end(args2);
    return str;
}

#endif

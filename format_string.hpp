#ifndef RUSTYKITTY_FORMAT_STRING_HPP
#define RUSTYKITTY_FORMAT_STRING_HPP

#include <cstdarg>

#include <string>
#include <stdexcept>

#include "format_string.h"

namespace rustykitty {
    std::string format_string(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        va_list args2;
        va_copy(args2, args);
        int len = vsnprintf(NULL, 0, fmt, args);
        if (len < 0) throw std::runtime_error("error");
        va_end(args);
        char* str = (char*)malloc(len + 1);
        vsnprintf(str, len + 1, fmt, args2);
        va_end(args2);
        std::string res = str;
        free(str);
        return res;
    }
}

#endif

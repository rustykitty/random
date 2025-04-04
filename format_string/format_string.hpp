#ifndef RUSTYKITTY_FORMAT_STRING_HPP
#define RUSTYKITTY_FORMAT_STRING_HPP

#include <cstdarg>

#include <string>
#include <stdexcept>

#include "format_string.h"

namespace rustykitty {
    template <typename... Args>
    std::string format_string(const char* fmt, Args&&... args) {
        int len = snprintf(NULL, 0, fmt, args...);
        if (len < 0) throw std::runtime_error("error");
        char* str = (char*)malloc(len + 1);
        vsnprintf(str, len + 1, fmt, args...);
        std::string res = str;
        free(str);
        return res;
    }
}

#endif

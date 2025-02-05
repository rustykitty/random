#include <iostream>
#include <string>

#include "array.hpp"

using std::cout; 
using std::endl;
using std::string;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

const char* boolToString(bool b) {
    return b ? "true" : "false";
}

int main(int argc, char* argv[]) {
    rustykitty::array<string> args(argc);
    for (int i = 0; i < argc; ++i) {
        args[i] = argv[i];
    }
    for (auto arg : args) {
        cout << arg << "\n";
    }
    cout << std::flush;

    return 0;
}
#include "undo_redo.hpp"

#include <iostream>
#include <deque>

void print_container(std::deque<int> dq) {
    for (const int i : dq) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

int main() {
    UndoRedo<int> dq;

    dq.push(1);
    dq.push(2);
    std::cout << dq.undo();
    dq.push(3);
    std::cout << dq.undo();
    std::cout << dq.top();
    print_container(dq.get_container());

}
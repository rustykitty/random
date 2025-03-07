#pragma once

#ifndef RUSTYKITTY_UNDO_REDO_HPP
#define RUSTYKITTY_UNDO_REDO_HPP

#include <cstdio>
#include <deque>

// note for container_type: std::list<T> can be used too - may need to performance test both
template <typename T, typename container_type=std::deque<T> >
class UndoRedo {
private:
    container_type container;
    typename container_type::iterator pos;

public:
    void push(const T& x) {
        container.erase(pos, container.end());
        container.push_back(x);
        pos = container.end() - 1;
    }
    
    void push(T&& x) {
        container.erase(pos, container.end());
        container.push_back(x);
        pos = container.end() - 1;
    }

    template <class... Args>
    void emplace(Args&&... args) {
        container.push_back(T(args...));
    }

    T& top() const { // this is the top trust
        return *pos;
    }

    // !!! undefined behavior if can_undo is false!!!!
    T& undo() { // caller is expected to check can_undo
        return *(pos--);
    }

    // !!! undefined behavior if can_redo is false!!!!
    T& redo() { // caller is expected to check can_redo
        return *(pos++);
    }
     
    bool can_undo() { return !(container.empty()) && pos != container.begin(); };

    bool can_redo() { return !(container.empty()) && pos != container.end() - 1; };

    container_type get_container() { return container; }

};

#endif
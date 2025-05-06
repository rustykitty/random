#include <stdexcept>
#include "safe_pointer.hpp"

using rustykitty::safe_pointer;

template <class T>
template <class... Args>
safe_pointer<T>::safe_pointer(Args... args) : ptr(nullptr) {
    initialize(args...);
}

template <class T>
safe_pointer<T>::safe_pointer(safe_pointer&& other) : ptr(other.ptr) {
    other.ptr = nullptr;
}

template <class T>
template <class... Args>
void safe_pointer<T>::initialize(Args... args) {
    if (ptr) {
        throw std::runtime_error("Attempt to initialize an already initialized pointer; call destroy() to destroy before reinitializing");
    }
    void* p = ::operator new(sizeof(T));
    new (p) T(args...);
    ptr = static_cast<T*>(p);
}

template <class T>
void safe_pointer<T>::destroy() {
    if (!ptr) {
        throw std::runtime_error("Cannot destroy when pointer is not initialized; call initialize() to initialize");
    }
    ptr->~T();
    ::operator delete(ptr);
    ptr = nullptr;
}


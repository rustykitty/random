#pragma once

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>
#include <utility>
#include <sstream>

namespace rustykitty {
    /**
     * A fixed-length array class inspired by std::vector and the `length` attribute of Java arrays.
     */
    template <class T>
    class array {
    private:
        T* _data;
    public:
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef size_t size_type;
        typedef ptrdiff_t difference_t; 

        const size_type length;

        /**
         * Fill constructor.
         * 
         * All elements are default-initialized. T must have a default constructor for this to work.
         * 
         * @param length The length of the array.
         */
        explicit array(size_type length) noexcept : length(length) {
            _data = new T[length]{};
        }

        /**
         * Value fill constructor.
         * 
         * All elements are initialized to the @param val given.
         * 
         * @param length The length of the array.
         * @param val The value to fill the container with.
         */
        explicit array(size_type length, T& val) : array(length) {
            for (size_type i = 0; i < length; i++) {
                _data[i] = val;
            }
        }

        /**
         * Copy constructor.
         * 
         * @param other The array to copy.
         */
        array(const array<T>& other) noexcept : array(other.length){
            memcpy(_data, other._data, length * sizeof(T));
        }

        /**
         * Construct an array from a C-style array.
         * 
         * @param arr The C-style array
         * @param length The length of the array
         */
        explicit array(T* arr, size_type length) noexcept : array(length) {
            memcpy(_data, arr, length * sizeof(T));
        }

        /**
         * Initializer list constructor
         * 
         * @param list The initializer list
         */
        array(std::initializer_list<T> list) : array(list.size()) {
            std::copy(list.begin(), list.end(), _data);
        }

        /**
         * Range constructor
         * 
         * @param first The beginning of the range
         * @param last The iterator one past the end of the range
         */
        template<class InputIterator>
        array(InputIterator first, InputIterator last) : array(std::distance(first, last)) {
            std::copy(first, last, _data);
        }

        ~array() noexcept {
            delete[] _data;
        }

        /**
         * Get the size of the array.
         * Equivalent to `arr.length`.
         * @returns The size of the array
         */
        size_type size() const noexcept {
            return length;
        }

        /**
         * Get the size of the array.
         * Equivalent to `arr.length`.
         * @returns The size of the array
         */
        size_type max_size() const noexcept {
            return length;
        }

        /**
         * Whether the array is empty.
         * Equivalent to `arr.length == 0`.
         * 
         * @returns Whether the array is empty
         */
        bool empty() const noexcept { return length == 0; }

        /**
         * Get a reference to the element at the given index in the container.
         * @param index Index of the elemtn
         * 
         * @returns A reference to the element at the index
         * 
         * @note If index >= length, result is undefined behavior
         */
        reference operator[](size_type index) {
            return _data[index];
        }

        /**
         * Get a reference to the element at the given index in the container.
         * @param index Index of the elemtn
         * 
         * @returns A reference to the element at the index
         * 
         * @note If index >= length, result is undefined behavior
        */
        const_reference operator[](size_type index) const {
            return _data[index];
        }
        
        /**
         * Get a reference to the element at the given index in the container.
         * @param index Index of the elemtn
         * 
         * @returns A reference to the element at the index
         * 
         * @throws std::out_of_range When index >= length
        */
        reference at(size_type index) {
            if (index >= length) throw std::out_of_range("Index out of range");
            return _data[index];
        }

        /**
         * Get a reference to the element at the given index in the container.
         * @param index Index of the elemtn
         * 
         * @returns A reference to the element at the index
         * 
         * @throws std::out_of_range When index >= length
        */
        const_reference at(size_type index) const {
            if (index >= length) throw std::out_of_range("Index out of range");
            return _data[index];
        }

        /**
         * Get reference to the front of the array
         * 
         * @returns A reference to the front of the array. Equivalent to arr[0]
         */
        reference front() noexcept { return _data[0]; }


        /**
         * Get reference to the front of the array
         * 
         * @returns A reference to the front of the array. Equivalent to arr[0]
         */
        const_reference front() const noexcept { return _data[0]; }

        /**
         * Get reference to the back of the array
         * 
         * @returns A reference to the back of the array. Equivalent to arr[arr.length - 1]
         */
        reference back() noexcept { return _data[length - 1]; }

        /**
         * Get reference to the back of the array
         * 
         * @returns A reference to the back of the array. Equivalent to arr[arr.length - 1]
         */
        const_reference back() const noexcept { return _data[length - 1]; }

        /**
         * Get pointer to underlying C array
         * 
         * @returns A pointer to the underlying C array
         */
        pointer data() noexcept { return _data; }

        /**
         * Get pointer to underlying C array
         * 
         * @returns A pointer to the underlying C array
         */
        const_pointer data() const noexcept { return _data; }

        pointer begin() { return _data; } /// Return an iterator to beginning of array
        pointer end() { return _data + length; } /// Return an iterator past the end of array
        const_pointer begin() const { return _data; } /// Return an iterator to beginning of array
        const_pointer end() const { return _data + length; } /// Return an iterator past the end of array

        bool operator==(const array<T>& other) const noexcept {
            if (this == &other)
                return true;

            if (length != other.length)
                return false;

            for (int i = 0; i < length; i++) {
                if (_data[i] != other[i]) {
                    return false;
                }
            }
            return true;
        }

        class iterator : public std::iterator<std::random_access_iterator_tag, T> {
        private:
            T* p;
        public:
            iterator(T* p) : p(p) {}
            iterator(const iterator& other) : p(other.p) {}
            iterator& operator++() { p++; return *this; }
            iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }
            iterator& operator--() { p--; return *this; }
            iterator operator--(int) { iterator tmp(*this); operator--(); return tmp; }
            iterator& operator+=(difference_t n) { p += n; return *this; }
            iterator operator+(difference_t n) const { return iterator(p + n); }
            iterator& operator-=(difference_t n) { p -= n; return *this; }
            iterator operator-(difference_t n) const { return iterator(p - n); }
            difference_t operator-(const iterator& other) const { return p - other.p; }
            T& operator*() { return *p; }
            T* operator->() { return p; }
            T& operator[](difference_t n) { return p[n]; }
            bool operator==(const iterator& other) const { return p == other.p; }
            bool operator!=(const iterator& other) const { return p != other.p; }
            bool operator<(const iterator& other) const { return p < other.p; }
            bool operator>(const iterator& other) const { return p > other.p; }
        }
    };
}
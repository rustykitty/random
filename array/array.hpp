#pragma once

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>
#include <utility>
#include <sstream>
#include <iterator>
#include <memory>
#include <type_traits>

namespace rustykitty {
    /**
     * A fixed-length array class inspired by std::vector and the `length` attribute of Java arrays.
     */
    template <class T, class allocator_type=std::allocator<T> >
    class array {
    private:
        T* const _data;

        /**
         * Allocates unitialized memory.
         */
        T* allocate_array(size_t length) {
            return static_cast<T*>(::operator new(length * sizeof(T)));
        }

    public:
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
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
        explicit array(size_type length) noexcept : length(length), _data(new T[length]) { }

        /**
         * Value fill constructor.
         * 
         * All elements are initialized to the @param val given.
         * 
         * @param length The length of the array.
         * @param val The value to fill the container with.
         */
        explicit array(size_type length, T& val) : length(length), _data(allocate_array(length)) {
            std::fill(_data, _data + length, val);
        }

        /**
         * Copy constructor.
         * 
         * @param other The array to copy.
         */
        array(const array<T>& other) noexcept : _data(allocate_array(other.length)) {
            std::uninitialized_copy(other.begin(), other.end(), _data);
        }

        /**
         * Construct an array from a C-style array.
         * 
         * @param arr The C-style array
         * @param length The length of the array
         */
        explicit array(T* arr, size_type length) noexcept : _data(allocate_array(length)) {
            std::uninitialized_copy(_data, _data + length, arr);
        }

        /**
         * Initializer list constructor
         * 
         * @param list The initializer list
         */
        array(std::initializer_list<T> list) {
            allocate_array(list.size);
            std::uninitialized_copy(list.begin(), list.end(), _data);
        }

        /**
         * Range constructor
         * 
         * @param first The beginning of the range
         * @param last The iterator one past the end of the range
         */
        template<class InputIterator>
        array(InputIterator first, InputIterator last) _data(allocate_array(std::distance(first, last));) {
            std::uninitialized_copy(first, last, _data);
        }

        ~array() noexcept {
            if constexpr (!std::is_trivially_destructible_v<T>) {
                for (size_type i = 0; i < length; i++) {
                    _data[i].~T();
                }
            }
            ::operator delete(_data);
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

        iterator begin() { return _data; } 
        iterator end() { return _data + length; } 
        const_iterator cbegin() const { return _data; } 
        const_iterator cend() const { return _data + length; } 
        reverse_iterator rbegin() { return reverse_iterator(end()); } 
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
        const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

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
    };
}
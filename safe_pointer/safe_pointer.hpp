namespace rustykitty {

    /**
     * safer pointer to a single block of memory
     */
    template <class T>
    class safe_pointer {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_pointer = const pointer;
        using const_reference = const reference;
    protected:
        pointer ptr;
    public:
        safe_pointer() : ptr(nullptr) {};
        safe_pointer(safe_pointer&) = delete;
        safe_pointer(const safe_pointer&) = delete;
        safe_pointer(safe_pointer&&);
        template <class... Args>
        safe_pointer(Args...);
        ~safe_pointer() {
            if (ptr) destroy();
        }
        template <class... Args>
        void initialize(Args...);
        void destroy();
        reference operator*() {
            if (!ptr) {
                throw std::runtime_error("Attempt to dereference an unitialized pointer");
            }
            return *ptr;
        }
        const_reference operator*() const {
            if (!ptr) {
                throw std::runtime_error("Attempt to dereference an unitialized pointer");
            }
            return *ptr;
        }
        pointer operator->() {
            if (!ptr) {
                throw std::runtime_error("Attempt to dereference an unitialized pointer");
            }
            return ptr;
        }
        const_pointer operator->() const {
            if (!ptr) {
                throw std::runtime_error("Attempt to dereference an unitialized pointer");
            }
            return ptr;
        }
    };

}


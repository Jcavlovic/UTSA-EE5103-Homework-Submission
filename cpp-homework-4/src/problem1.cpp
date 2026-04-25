#include <iostream>
#include <cstring>
#include <utility>

class SimpleString {
public:
    /**
     * @brief Construct a SimpleString from a C-style string.
     * @param s null-terminated source string (defaults to empty string).
     */
    SimpleString(const char* s = "") {
        size_ = std::strlen(s);
        data_ = new char[size_ + 1];
        std::memcpy(data_, s, size_ + 1);
    }

    /**
     * @brief Deep-copy constructor.
     * @param other source object whose buffer is duplicated.
     */
    SimpleString(const SimpleString& other) : size_(other.size_) {
        data_ = new char[size_ + 1];
        std::memcpy(data_, other.data_, size_ + 1);
    }

    /**
     * @brief Copy-and-swap assignment operator.
     * @param rhs object copied by value (handles self-assignment naturally).
     * @return reference to this object.
     */
    SimpleString& operator=(SimpleString rhs) {
        swap(*this, rhs);
        return *this;
    }

    /**
     * @brief Destructor releases the owned buffer.
     */
    ~SimpleString() {
        delete[] data_;
    }

    /**
     * @brief Return the number of characters stored (excluding null terminator).
     */
    std::size_t size() const { return size_; }

    /**
     * @brief Mutable element access.
     * @param i zero-based character index (no bounds checking).
     */
    char& operator[](std::size_t i) { return data_[i]; }

    /**
     * @brief Read-only element access.
     */
    const char& operator[](std::size_t i) const { return data_[i]; }

    /**
     * @brief Equality compares full string contents.
     */
    friend bool operator==(const SimpleString& a, const SimpleString& b) {
        return a.size_ == b.size_ && std::memcmp(a.data_, b.data_, a.size_) == 0;
    }

    friend bool operator!=(const SimpleString& a, const SimpleString& b) {
        return !(a == b);
    }

    /**
     * @brief Stream insertion writes the underlying buffer.
     */
    friend std::ostream& operator<<(std::ostream& os, const SimpleString& s) {
        return os << s.data_;
    }

    /**
     * @brief Non-throwing swap used by the copy-and-swap assignment.
     */
    friend void swap(SimpleString& a, SimpleString& b) noexcept {
        using std::swap;
        swap(a.size_, b.size_);
        swap(a.data_, b.data_);
    }

private:
    char* data_;        ///< Owned heap-allocated, null-terminated buffer.
    std::size_t size_;  ///< Length of the string excluding the null terminator.
};

int main() {
    SimpleString a("hello");
    SimpleString b = a;          // copy construction
    SimpleString c("world");
    c = a;                       // copy assignment

    std::cout << "a = " << a << " (size=" << a.size() << ")\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";

    // Demonstrate independence after copy: mutating b does not affect a or c.
    b[0] = 'J';
    std::cout << "\nAfter b[0] = 'J':\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";

    std::cout << "\nComparisons:\n";
    std::cout << "a == c -> " << std::boolalpha << (a == c) << "\n";
    std::cout << "a != b -> " << (a != b) << "\n";

    return 0;
}

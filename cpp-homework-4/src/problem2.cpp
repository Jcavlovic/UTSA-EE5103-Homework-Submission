#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <cstddef>

class NumberList {
public:
    /**
     * @brief Construct an empty list.
     */
    NumberList() : data_(nullptr), size_(0) {}

    /**
     * @brief Construct from a brace-enclosed initializer list of ints.
     * @param init source values copied into the list.
     */
    NumberList(std::initializer_list<int> init)
        : data_(new int[init.size()]), size_(init.size()) {
        std::copy(init.begin(), init.end(), data_);
    }

    /**
     * @brief Deep-copy constructor.
     */
    NumberList(const NumberList& other)
        : data_(new int[other.size_]), size_(other.size_) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    /**
     * @brief Copy-assignment via copy-and-swap.
     */
    NumberList& operator=(NumberList rhs) {
        swap(*this, rhs);
        return *this;
    }

    /**
     * @brief Destructor releases the owned array.
     */
    ~NumberList() { delete[] data_; }

    /**
     * @brief Number of elements currently stored.
     */
    std::size_t size() const { return size_; }

    /**
     * @brief Mutable element access (no bounds checking).
     */
    int& operator[](std::size_t i) { return data_[i]; }

    /**
     * @brief Read-only element access.
     */
    const int& operator[](std::size_t i) const { return data_[i]; }

    /**
     * @brief Append another list in place.
     * @param rhs list whose elements are concatenated to this one.
     * @return reference to the modified list.
     */
    NumberList& operator+=(const NumberList& rhs) {
        std::size_t newSize = size_ + rhs.size_;
        int* buf = new int[newSize];
        std::copy(data_, data_ + size_, buf);
        std::copy(rhs.data_, rhs.data_ + rhs.size_, buf + size_);
        delete[] data_;
        data_ = buf;
        size_ = newSize;
        return *this;
    }

    /**
     * @brief Prefix increment - bumps every element by one.
     */
    NumberList& operator++() {
        for (std::size_t i = 0; i < size_; ++i) ++data_[i];
        return *this;
    }

    /**
     * @brief Postfix increment - returns the pre-increment snapshot.
     */
    NumberList operator++(int) {
        NumberList snapshot(*this);
        ++(*this);
        return snapshot;
    }

    /**
     * @brief Concatenation operator implemented via +=.
     */
    friend NumberList operator+(NumberList lhs, const NumberList& rhs) {
        lhs += rhs;
        return lhs;
    }

    /**
     * @brief Element-wise equality.
     */
    friend bool operator==(const NumberList& a, const NumberList& b) {
        if (a.size_ != b.size_) return false;
        return std::equal(a.data_, a.data_ + a.size_, b.data_);
    }

    /**
     * @brief Lexicographic less-than ordering.
     */
    friend bool operator<(const NumberList& a, const NumberList& b) {
        return std::lexicographical_compare(
            a.data_, a.data_ + a.size_,
            b.data_, b.data_ + b.size_);
    }

    /**
     * @brief Formatted output: "[1, 2, 3]".
     */
    friend std::ostream& operator<<(std::ostream& os, const NumberList& l) {
        os << '[';
        for (std::size_t i = 0; i < l.size_; ++i) {
            if (i) os << ", ";
            os << l.data_[i];
        }
        return os << ']';
    }

    /**
     * @brief Non-throwing swap used by copy-and-swap.
     */
    friend void swap(NumberList& a, NumberList& b) noexcept {
        using std::swap;
        swap(a.data_, b.data_);
        swap(a.size_, b.size_);
    }

private:
    int* data_;         ///< Owned heap buffer of size_ ints.
    std::size_t size_;  ///< Number of valid elements in data_.
};

int main() {
    NumberList a{1, 2, 3};
    NumberList b{4, 5};
    NumberList c{6};

    // Operator chaining: build a += (b + c).
    NumberList chained = a;
    chained += b + c;
    std::cout << "a            = " << a << '\n';
    std::cout << "b            = " << b << '\n';
    std::cout << "c            = " << c << '\n';
    std::cout << "a += (b + c) = " << chained << '\n';

    // Element access (const and non-const).
    chained[0] = 100;
    std::cout << "After chained[0]=100: " << chained << '\n';

    // Increment operators.
    NumberList pre = a;
    ++pre;
    std::cout << "++a -> " << pre << '\n';

    NumberList post = a;
    NumberList snap = post++;
    std::cout << "post++ snapshot = " << snap
              << ", post-increment value = " << post << '\n';

    // Comparisons.
    NumberList aCopy = a;
    std::cout << std::boolalpha;
    std::cout << "a == aCopy -> " << (a == aCopy) << '\n';
    std::cout << "a <  b     -> " << (a < b) << '\n';

    return 0;
}

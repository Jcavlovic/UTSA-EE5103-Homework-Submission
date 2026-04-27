#include <iostream>
#include <vector>
#include <utility>
#include <cstddef>

class SmartBuffer {
public:
    /**
     * @brief Construct a buffer of n default-initialized doubles.
     */
    explicit SmartBuffer(std::size_t n = 0)
        : data_(n ? new double[n]() : nullptr), size_(n) {
        std::cout << "  [ctor]    SmartBuffer(" << size_ << ")\n";
    }

    /**
     * @brief Deep-copy constructor (announces itself).
     */
    SmartBuffer(const SmartBuffer& other)
        : data_(other.size_ ? new double[other.size_] : nullptr),
          size_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
        std::cout << "  [copy]    SmartBuffer copied  (size=" << size_ << ")\n";
    }

    /**
     * @brief Move constructor - steals the source buffer.
     *
     * Marked noexcept so std::vector will prefer it over the copy
     * constructor when growing its internal storage.
     */
    SmartBuffer(SmartBuffer&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "  [move]    SmartBuffer moved   (size=" << size_ << ")\n";
    }

    /**
     * @brief Copy-assignment via copy-and-swap.
     */
    SmartBuffer& operator=(const SmartBuffer& other) {
        std::cout << "  [copy=]   SmartBuffer copy-assigned\n";
        if (this != &other) {
            SmartBuffer tmp(other);
            swap(*this, tmp);
        }
        return *this;
    }

    /**
     * @brief Move-assignment - releases the current buffer and steals other's.
     */
    SmartBuffer& operator=(SmartBuffer&& other) noexcept {
        std::cout << "  [move=]   SmartBuffer move-assigned\n";
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /**
     * @brief Destructor releases the owned buffer (if any).
     */
    ~SmartBuffer() {
        std::cout << "  [dtor]    SmartBuffer destroyed (size=" << size_ << ")\n";
        delete[] data_;
    }

    std::size_t size() const { return size_; }

    /**
     * @brief Non-throwing swap used by copy-assignment.
     */
    friend void swap(SmartBuffer& a, SmartBuffer& b) noexcept {
        using std::swap;
        swap(a.data_, b.data_);
        swap(a.size_, b.size_);
    }

private:
    double* data_;       ///< Owned heap array (nullptr after a move).
    std::size_t size_;   ///< Element count (0 after a move).
};

/**
 * @brief Factory that returns a SmartBuffer by value.
 *
 * Thanks to RVO/NRVO and move semantics, this should not perform a deep
 * copy of the buffer when used in main().
 */
SmartBuffer makeBuffer(std::size_t n) {
    SmartBuffer b(n);
    return b;
}

int main() {
    std::cout << "-- Returning SmartBuffer by value:\n";
    SmartBuffer fromFn = makeBuffer(4);
    std::cout << "  size = " << fromFn.size() << "\n\n";

    std::cout << "-- Pushing into std::vector (reserved capacity):\n";
    std::vector<SmartBuffer> bag;
    bag.reserve(3);
    bag.push_back(SmartBuffer(2));   // temp -> move into vector
    bag.push_back(SmartBuffer(3));
    bag.push_back(SmartBuffer(5));

    std::cout << "\n-- Forcing reallocation by exceeding reserved capacity:\n";
    bag.push_back(SmartBuffer(7));   // vector regrows: existing elements move

    std::cout << "\n-- Explicit std::move into a new SmartBuffer:\n";
    SmartBuffer src(10);
    SmartBuffer dst = std::move(src);
    std::cout << "  src.size() after move = " << src.size()
              << " (must be valid + destructible)\n";
    std::cout << "  dst.size() after move = " << dst.size() << "\n\n";

    std::cout << "-- End of main(); destructors run next:\n";
    return 0;
}

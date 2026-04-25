#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class LibraryItem {
public:
    /**
     * @brief Construct a library item with a title and unique ID.
     */
    LibraryItem(std::string title, int id) : title_(std::move(title)), id_(id) {}

    virtual ~LibraryItem() = default;

    /**
     * @brief Compute the late fee for a number of overdue days.
     * @param days how many days the item is overdue.
     */
    virtual double lateFee(int days) const = 0;

    /**
     * @brief Polymorphic copy - returns a heap-allocated duplicate.
     */
    virtual LibraryItem* clone() const = 0;

    /**
     * @brief Print derived-class specific details to a stream.
     */
    virtual void print(std::ostream& os) const {
        os << "LibraryItem[id=" << id_ << ", title=\"" << title_ << "\"]";
    }

    const std::string& title() const { return title_; }
    int id() const { return id_; }

    /**
     * @brief Stream insertion uses dynamic binding via print().
     */
    friend std::ostream& operator<<(std::ostream& os, const LibraryItem& item) {
        item.print(os);
        return os;
    }

protected:
    std::string title_;  ///< Display title.
    int id_;             ///< Unique identifier.
};

/**
 * @brief Book - charges a flat fee per overdue day.
 */
class Book : public LibraryItem {
public:
    /**
     * @param title book title.
     * @param id unique identifier.
     * @param feePerDay flat per-day overdue fee.
     */
    Book(std::string title, int id, double feePerDay)
        : LibraryItem(std::move(title), id), feePerDay_(feePerDay) {}

    /**
     * @brief Late fee = feePerDay * days (no cap).
     */
    double lateFee(int days) const override {
        return days <= 0 ? 0.0 : days * feePerDay_;
    }

    LibraryItem* clone() const override { return new Book(*this); }

    void print(std::ostream& os) const override {
        os << "Book   [id=" << id_ << ", title=\"" << title_
           << "\", fee/day=$" << feePerDay_ << "]";
    }

private:
    double feePerDay_;
};

/**
 * @brief DVD - higher per-day fee, capped at maxFee.
 */
class DVD : public LibraryItem {
public:
    /**
     * @param title DVD title.
     * @param id unique identifier.
     * @param feePerDay per-day overdue fee.
     * @param maxFee maximum total late fee.
     */
    DVD(std::string title, int id, double feePerDay, double maxFee)
        : LibraryItem(std::move(title), id),
          feePerDay_(feePerDay), maxFee_(maxFee) {}

    /**
     * @brief Late fee = min(feePerDay * days, maxFee).
     */
    double lateFee(int days) const override {
        if (days <= 0) return 0.0;
        double raw = days * feePerDay_;
        return raw < maxFee_ ? raw : maxFee_;
    }

    LibraryItem* clone() const override { return new DVD(*this); }

    void print(std::ostream& os) const override {
        os << "DVD    [id=" << id_ << ", title=\"" << title_
           << "\", fee/day=$" << feePerDay_ << ", cap=$" << maxFee_ << "]";
    }

private:
    double feePerDay_;
    double maxFee_;
};

int main() {
    std::vector<LibraryItem*> shelf;
    shelf.push_back(new Book("The C++ Programming Language", 1, 0.25));
    shelf.push_back(new Book("Effective Modern C++", 2, 0.30));
    shelf.push_back(new DVD ("Inception", 101, 1.00, 10.00));
    shelf.push_back(new DVD ("Interstellar", 102, 1.50, 12.00));

    const int overdueDays = 9;

    std::cout << "Shelf contents (" << overdueDays << " days overdue):\n";
    for (const LibraryItem* item : shelf) {
        std::cout << "  " << *item
                  << " -> late fee = $" << item->lateFee(overdueDays) << '\n';
    }

    // Demonstrate virtual copy construction via clone().
    LibraryItem* duplicate = shelf.front()->clone();
    std::cout << "\nCloned first item: " << *duplicate << '\n';
    delete duplicate;

    // Free the heap allocations to avoid leaks.
    for (LibraryItem* item : shelf) delete item;
    shelf.clear();

    return 0;
}

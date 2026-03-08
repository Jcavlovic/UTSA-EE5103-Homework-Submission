#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class InventoryItem {
private:
    string name_;
    int quantity_;
    double unit_price_;
    static int object_count_;

public:
    InventoryItem() 
        : name_("Unnamed"), quantity_(0), unit_price_(0.0) {
        ++object_count_;
    }

    InventoryItem(const string& name, int quantity, double price)
        : name_(name), 
          quantity_(quantity >= 0 ? quantity : 0),
          unit_price_(price >= 0.0 ? price : 0.0) {
        ++object_count_;
    }

    ~InventoryItem() {
        --object_count_;
    }

    const string& name() const {
        /**
        * @brief Observor method for object name.
        * 
        * @return string: name of object.
        */
        return name_;
    }

    int quantity() const {
        /**
        * @brief Observor method for object quantity.
        * 
        * @return int: object quantity.
        */
        return quantity_;
    }

    double price() const {
        /**
        * @brief Observor method for object price.
        * 
        * @return int: object price.
        */
        return unit_price_;
    }

    double totalValue() const {
        /**
        * @brief Observor method for objects total value.
        * 
        * @return int: total value of objects.
        */
        return quantity_ * unit_price_;
    }

    static int objectCount() {
        /**
        * @brief Method to hold total items.
        * 
        * @return int: total objects created.
        */
        return object_count_;
    }

    bool restock(int amount) {
        /**
        * @brief Method to add more objects for each object created.
        * 
        * @param[in] int: amount of restock.
        * 
        * @return bool: return turn if adding more items, else false.
        */
        if (amount <= 0) {
            return false;
        }
        quantity_ += amount;
        return true;
    }

    bool sell(int amount) {
        /**
        * @brief Method to sell item for object.
        * 
        * @param[in] int: total number of items to sell from object.
        * 
        * @return bool: True if selling, else false.
        */
        if (amount <= 0 || amount > quantity_) {
            return false;
        }
        quantity_ -= amount;
        return true;
    }
};

int InventoryItem::object_count_ = 0;

void printItem(const InventoryItem& item) {
    /**
    * @brief Helper method to print current stock of items in object.
    * 
    * @param[in] InventoryItem: item to display results
    * 
    */
    cout << fixed << setprecision(2);
    cout << "Item: " << item.name()
              << " | Qty: " << item.quantity()
              << " | Price: $" << item.price()
              << " | Total value: $" << item.totalValue() << endl;
}

int main() {
    cout << "Initial number of InventoryItem objects: " 
              << InventoryItem::objectCount() << endl;

    InventoryItem laptop("Gaming Laptop", 15, 1299.99);
    InventoryItem mouse("Wireless Mouse", 40, 24.50);

    cout << "After creating 3 items:\n";
    cout << "Current number of InventoryItem objects: " 
              << InventoryItem::objectCount() << endl;

    cout << "Initial stock: " << endl;
    printItem(laptop);
    printItem(mouse);
    cout << endl;

    cout << "Restocking attempts: " << endl;
    cout << "Restock laptop +20 → " 
              << (laptop.restock(20) ? "Success" : "Failed") << endl;
    cout << "Restock mouse +0  → " 
              << (mouse.restock(0) ? "Success" : "Failed") << endl;

    cout << "Selling attempts:\n";
    cout << "Sell 8 laptops   → " 
              << (laptop.sell(8) ? "Success" : "Failed") << endl;
    cout << "Sell 50 mice     → " 
              << (mouse.sell(50) ? "Success" : "Failed") << endl;

    cout << "Final stock status: " << endl;
    printItem(laptop);
    printItem(mouse);
    cout << endl;

    cout << "Final number of InventoryItem objects (before destruction): " 
              << InventoryItem::objectCount() << endl;

    return 0;
}
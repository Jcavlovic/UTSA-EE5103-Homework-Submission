#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <algorithm>


class TextCollection {
private:
    std::shared_ptr<std::vector<std::string>> words; ///< Shared collection of words

public:

    TextCollection() : words(std::make_shared<std::vector<std::string>>()) {}

    TextCollection(const std::string& filename)
    /**
     * @brief Constructs a TextCollection from a file.
     *
     * Reads whitespace-separated words from a file and stores them.
     *
     * @param[in] filename Name of the input file.
     */
        : words(std::make_shared<std::vector<std::string>>())
    {
        std::ifstream file(filename);
        std::string word;

        while (file >> word) {
            words->push_back(word);
        }
    }

    void addWord(const std::string& word) {
        /**
         * @brief Adds a word to the collection.
         *
         * @param[in] word The word to be added.
         */
        words->push_back(word);
    }

    void removeWord(const std::string& word) {
        /**
         * @brief Removes all occurrences of a word from the collection.
         *
         * @param[in] word The word to remove.
         */
        words->erase(
            std::remove(words->begin(), words->end(), word),
            words->end()
        );
    }

    void printAll() const {
        /**
         * @brief Prints all words in insertion order.
         */
        for (const auto& word : *words) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
};


int main() {
    TextCollection t1;

    t1.addWord("hello");
    t1.addWord("world");

    TextCollection t2 = t1;

    std::cout << "t1: ";
    t1.printAll();

    std::cout << "t2: ";
    t2.printAll();

    t2.addWord("shared");

    std::cout << "\nAfter modifying t2:\n";

    std::cout << "t1: ";
    t1.printAll();

    std::cout << "t2: ";
    t2.printAll();

    t1.removeWord("hello");

    std::cout << "\nAfter removing from t1:\n";

    std::cout << "t1: ";
    t1.printAll();

    std::cout << "t2: ";
    t2.printAll();

    return 0;
}
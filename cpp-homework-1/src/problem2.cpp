#include <iostream>
#include <string>

using namespace std;

string check_sort(string word, string sort_word) {
    /**
     * @brief Calculates alphabetical order of word versus sort_word.
     * 
     * @param[in] word The string to sort.
     * @param[in] sort_word The string to check against for sort position.
     * 
     * @return "Greater Than" if position is after sort_word else @returns "Less Than".
     */

    const string STR_LESS = "Less Than";
    const string STR_GREATER = "Greater Than";

    const int SORT = 0;

    int sort_results = word.compare(sort_word);

    return sort_results < SORT ? STR_LESS : STR_GREATER;
}

string string_len(string word) {
    /**
     * @brief Returns "Short" if @param word is less than 5 characters, "Medium" if less than 9 but greater than 4,
     *          "Long" if greater than 8.
     * 
     * @param[in] word The string check.
     * 
     * @return "Short", "Medium", "Long"
     */

    const int SHORT = 5;
    const int LONG = 9;

    const string STR_SHORT = "Short";
    const string STR_MEDIUM = "Medium";
    const string STR_LONG = "Long";

    int len = word.length();
    
    string word_len = len < SHORT ? STR_SHORT : (len < LONG) ? STR_MEDIUM : STR_LONG;
    
    return word_len;
}

int string_size(string word) {
        /**
     * @brief Returns the int size of @param word.
     * 
     * @param[in] word The string check.
     * 
     * @return int size of @param word.
     */
    return word.size();
}

int main() {

    const string SORT_WORD = "code";
    const string CHARACTERS = "Characters";
    
    string word;

    cout << "Enter a single word: ";
    cin  >> word;

    cout << "String Length: " << string_size(word) << " " + CHARACTERS << endl;
    cout << "String Size: " << string_len(word) << endl;
    cout << check_sort(word, SORT_WORD) << " " + SORT_WORD << endl;
}
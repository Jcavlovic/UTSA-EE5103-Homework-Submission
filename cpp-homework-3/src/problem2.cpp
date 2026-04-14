#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

string normalize(const string& word) {
    /**
     * @brief Normalizes a word by converting it to lowercase and removing punctuation.
     *
     * @param[in] word The original word.
     * @return Normalized word (lowercase, punctuation removed).
     */
    string result;

    transform(word.begin(), word.end(), back_inserter(result),
              [](unsigned char c) {
                  return ispunct(c) ? '\0' : tolower(c);
              });

    result.erase(remove(result.begin(), result.end(), '\0'), result.end());
    return result;
}

void buildIndex(const string& filename,
    /**
     * @brief Processes the file and builds a word-to-line-number index.
     *
     * @param[in] filename Name of the input text file.
     * @param[out] index Map storing words and the set of line numbers they appear on.
     */
                map<string, set<int>>& index) {
    ifstream file(filename);
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;

        stringstream ss(line);
        string word;

        while (ss >> word) {
            word = normalize(word);
            if (!word.empty()) {
                index[word].insert(lineNumber);
            }
        }
    }
}

void queryLoop(const map<string, set<int>>& index) {
    /**
     * @brief Allows repeated user queries for word lookups.
     *
     * @param[in] index Map containing word-to-line-number data.
     */
    string query;

    while (true) {
        cout << "Enter word to search: ";
    
        if (!(cin >> query )) {
            break;
        }

        query = normalize(query);

        auto it = index.find(query);

        if (it == index.end()) {
            cout << query << " does not exist in the file.\n";
        } else {
            cout << query << " occurs on lines: ";
            for (int line : it->second) {
                cout << line << " ";
            }
            cout << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: program <filename>\n";
        return 1;
    }

    map<string, set<int>> index;

    buildIndex(argv[1], index);
    queryLoop(index);

    return 0;
}
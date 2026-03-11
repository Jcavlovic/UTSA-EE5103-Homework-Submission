#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

string cleanWord(const string& word) {
    /**
    * @brief Helper function to reduce word to lowercase.
    * 
    * @param[in] list<string>::iterator current: iterator to current position.
    * 
    * @return string result: word in lowercase form.
    */
    string result;
    for (char ch : word) {
        if (isalnum(ch)) {
            result += tolower(ch);
        }
    }
    return result;
}

void printTopWords(const map<string, int>& freq, int n) {
    /**
    * @brief Helper function to determine most used words.
    * 
    * @param[in] map<string, int> freq: map used to hold words and count.
    * 
    */
    vector<pair<string, int>> wordCounts(freq.begin(), freq.end());

    sort(wordCounts.begin(), wordCounts.end(),
         [](const auto& a, const auto& b) {
             if (a.second != b.second) return a.second > b.second;
             return a.first < b.first;
         });

    cout << "\nTop " << n << " most frequent words:\n";
    
    int count = 0;
    for (const auto& [word, freq] : wordCounts) {
        if (word.empty()) continue;
        cout << freq << "\t" << word << "\n";
        if (++count >= n) break;
    }
    cout << "\n";
}

int main() {
    string filename;
    cout << "Enter the name of the text file to analyze: ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file \"" << filename << "\"\n";
        return 1;
    }

    map<string, int> wordFrequency;

    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        istringstream iss(line);
        string word;

        while (iss >> word) {
            string cleaned = cleanWord(word);
            if (!cleaned.empty()) {
                wordFrequency[cleaned]++;
            }
        }
    }

    file.close();

    cout << "\nFile \"" << filename << "\" processed.\n";
    cout << "Total unique words found: " << wordFrequency.size() << "\n";
    cout << "Total lines read: " << lineNumber << "\n\n";

    printTopWords(wordFrequency, 5);

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// helper to normalize words
string normalize(const string& word) {
    string result;
    transform(word.begin(), word.end(), back_inserter(result), [](unsigned char c) {
        return ispunct(c) ? '\0' : tolower(c);
    });

    // remove '\0' characters (punctuation removed)
    result.erase(remove(result.begin(), result.end(), '\0'), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: program <filename>\n";
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error opening file\n";
        return 1;
    }

    vector<string> words;
    string word;

    // read words
    while (file >> word) {
        words.push_back(word);
    }

    // normalize words
    transform(words.begin(), words.end(), words.begin(), normalize);

    // total words
    size_t totalWords = words.size();

    // sort
    sort(words.begin(), words.end());

    // remove duplicates
    auto last = unique(words.begin(), words.end());
    words.erase(last, words.end());

    // unique words
    size_t uniqueWords = words.size();

    // count words with length >= 6
    size_t countLong = count_if(words.begin(), words.end(), [](const string& w) {
        return w.length() >= 6;
    });

    // output
    cout << "Total words: " << totalWords << endl;
    cout << "Unique words: " << uniqueWords << endl;
    cout << "Words with length >= 6: " << countLong << endl;

    return 0;
}
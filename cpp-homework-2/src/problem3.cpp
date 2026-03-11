#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>

using namespace std;

bool parseLine(const string& line, vector<int>& values) {
    /**
    * @brief Helper function to determine if data is valid.
    * 
    * @param[in] string&: line to read
    * @param[in] vector<int>& values to store.
    * 
    * @return bool: True if data is valid, else False.
    */
    values.clear();
    std::istringstream iss(line);
    int number;
    bool hasValidData = false;

    while (iss >> number) {
        values.push_back(number);
        hasValidData = true;
    }

    std::string leftover;
    if (getline(iss >> ws, leftover) && !leftover.empty()) {

        return false;
    }

    return hasValidData;
}

double average(const vector<int>& values) {
    /**
    * @brief Helper fuction to get the average of the values.
    * 
    * @param[in] vector<int> : vector of ints.
    * 
    * @return double: average of ints in vector.
    */
    return accumulate(values.begin(), values.end(), 0) / values.size();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file '" << argv[1] << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;
    int validLines = 0;
    int totalIntegers = 0;

    while (getline(file, line)) {
        ++lineNumber;

        vector<int> values;
        if (!parseLine(line, values)) {
            if (!values.empty()) {

                cerr << "Warning: Line " << lineNumber 
                          << " contains invalid data — skipped" << endl;
            } else {

                cerr << "Warning: Line " << lineNumber 
                          << " is invalid (non-numeric) — skipped" << endl;
            }
            continue;
        }

        ++validLines;
        totalIntegers += values.size();

        double avg = average(values);

        cout << "Line " << lineNumber << ": "
                  << "count=" << values.size() << " "
                  << "avg= " << fixed << setprecision(2) << avg
                  << endl;
    }

    file.close();

    cout << "\nSummary:" << endl
              << "  Total lines processed: " << lineNumber << endl
              << "  Total valid lines:\t " << validLines << endl
              << "  Total integers read:\t " << totalIntegers << endl;

    return 0;
}
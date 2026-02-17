#include <iostream>
#include <vector>
#include <numeric>
#include <string>

using namespace std;

int calculate_sum(vector<int> nums) {
    /**
    * @brief Calculates the sum of the input vector.
    * 
    * @param[in] nums: vector of ints.

    * 
    * @return sum of numbers in vector.
    */
    return accumulate(nums.begin(), nums.end(), 0);
}

int calculate_average(vector<int> nums) {
    /**
    * @brief Calculates the average of the input vector.
    * 
    * @param[in] nums: vector of ints.

    * 
    * @return average of the ints in vector.
    */
    return accumulate(nums.begin(), nums.end(), 0) / nums.size();
}

bool is_numeric(string num) {
    /**
    * @brief Checks if string is a number.
    * 
    * @param[in] num: string to check.
    * 
    * @return true if num is number, else false.
    */
    for (auto c : num) {
        if(isalpha(c))
            return false;
    }
    return true;
}

string nums_to_list(vector<int> nums) { 
    /**
    * @brief Converts vector to a string of the list of ints in vector.
    * 
    * @param[in] nums: vector of ints.
    * 
    * @return string list of ints in vector.
    */
    string str_nums;

    for (auto num : nums) {
        str_nums += to_string(num) + " ";    
    }
    return str_nums;
}

void print_results(vector<int> nums) {
    /**
    * @brief Prints to console the results for problem 3.
    * 
    * @param[in] nums: vector of ints.
    * 
    */
    cout << "Numbers Entered: " << nums_to_list(nums) << endl;
    cout << "Sum of Numbers: " << calculate_sum(nums) << endl;
    cout << "Average of Numbers: " << calculate_average(nums) << endl << endl;
}

int main() {

    vector<int> nums;

    while (true) {

        static string QUIT = "-1";

        string num;

        cout << "Enter a number: ";
        cin >> num;
        
        if (num == QUIT)
            break;

        else if (is_numeric(num))
            nums.push_back(stoi(num));
     
        print_results(nums);
    }
}
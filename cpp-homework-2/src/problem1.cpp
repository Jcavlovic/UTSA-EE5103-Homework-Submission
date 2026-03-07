#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <iomanip>

using namespace std;

class Problem1 {
    public:

        vector<int> values;

        int minVal = 0;
        int maxVal = 0;
        int sum = 0;
        int count = 0;

        double avg = 0.0;


    int max_value(vector<int> nums) {
        /**
        * @brief Find the max value in vector and return
        *           its value
        *
        * @param[in] nums: vector of ints.
        * 
        * @return max value in vector.
        */
        int max = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > max)
                max = nums[i];
        }
        return max;
    }

    int min_value(vector<int> nums) {
        /**
        * @brief Find the max value in vector and return
        *           its value
        *
        * @param[in] nums: vector of ints.
        * 
        * @return max value in vector.
        */
        int min = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < min)
                min = nums[i];
        }
        return min;
    }

    bool is_valid(int value) {
        /**
        * @brief Compute is input from user is valid.
        * 
        * @param[in] int: value, current value.
        * 
        * @return bool: True if input is valid, else False.
        */
        if (value < 0 || value > 500) {
            return false;
        }
        return true;
    }

    double compute_average(int count, double sum) {
        /**
        * @brief Compute the average of the input vector.
        * 
        * @param[in] nums: vector of ints.

        * 
        * @return average of the ints in vector.
        */
        avg = sum / count;

        return avg;
    }

    void printSummary(int count, int minVal, int maxVal, double avg) {
            /**
     * @brief Prints to console a summary of valid inputs.
     * 
     * @param[in] int count: current count of valid inputs.
     * @param[in] int minVal: current min value of valid inputs.
     * @param[in] int maxVal: current max value of valid inputs.
     * @param[in] double avg: average of valid inputs.
     * 
     */
        cout << "Count: " << count << endl;
        cout << "Max Value: " << maxVal << endl;
        cout << "Min Value: " << minVal << endl;
        cout << fixed << setprecision(1) << "Average: " << avg << endl;
    }

    void updateStats(int value, int& count, int& minVal, int& maxVal, double &sum) {
            /**
     * @brief Updates the class member variables
     * 
     * @param[in] int value: current input value from user.
     * @param[in] int& count: current total of valid inputs.
     * @param[in] int& minVal: current min value of valid inputs.
     * @param[in] int& maxVal: current max value of valid inputs.
     * @param[in] double& sum: current sum of valid inputs.
     * 
     */
        this->count = count;
        this->minVal = minVal;
        this->maxVal = maxVal;
        this->sum = sum;
        this->avg = compute_average(count, sum);
    }

    int sum_of(vector<int> values){
        /**
        * @brief Returns the sum of the @param vector<int>
        * 
        * @param[in] vector: of temps.
        * 
        * @return The sum of the input vector.
        */

        int temp = accumulate(values.begin(), values.end(), 0);

        return temp;
    }

    void get_values() {
        /**
        * @brief Prompt the user for valid inputs to the microcontroller.
        * 
        * @return vector of ints of valid inputs.
        */

        string value;

        while (true) {
            try {
                cout << "Enter a value between 0 - 500: ";

                cin >> value;

                if (stoi(value) == -1) {
                    break;
                    }

                else if (is_valid(stoi(value))) {
                    this->count += 1;
                    this->values.push_back(stoi(value));
                    int temp_min = min_value(this->values);
                    int temp_max = max_value(this->values);
                    double temp_sum = sum_of(this->values);
                    this->updateStats(stoi(value), count, temp_min, temp_max, temp_sum);
                }

                else {
                    throw invalid_argument("Value must be between 0 and 500.");
                    continue;
                    }
                }

                catch (const invalid_argument& e) {
                    std:cerr << "ERROR: " << e.what() << endl;
                }

            }
    }
};

int main() {

    Problem1 p1;

    p1.get_values();

    p1.printSummary(p1.count, p1.minVal, p1.maxVal, p1.avg);
    
    return 0;
}
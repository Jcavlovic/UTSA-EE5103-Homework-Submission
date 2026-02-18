#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

void double_values(int nums[5]) {
    /**
    * @brief Doubles all the values in the input array.
    * 
    * @param[in] nums: array[5] of ints.
    */
    for (int i = 0; i < 5; i++) {
        nums[i] *= 2;
    }
}

void double_values(vector<int>* nums) {
    /**
    * @brief Doubles all the values in the input vector.
    * 
    * @param[in] nums: pointer to vector of ints.
    */
    for(auto &num : *nums) {
        num *= 2;
    }
}

string to_string(int nums[5]) {
    /**
    * @brief Converts array[5] of ints to string 
    *           with list of ints in array.
    *
    * @param[in] nums: array[5] of ints.
    * 
    * @return string list of ints in array.
    */
    string nums_list;
    for (int i = 0; i < 5; i++) {
        nums_list += to_string(nums[i]) + " ";
    }
    return nums_list;
}

string to_string(vector<int> nums) {
    /**
    * @brief Converts vector of ints into a string 
    *           list of the ints
    *
    * @param[in] nums: vector of ints.
    * 
    * @return string list of ints in vector.
    */
    string nums_list;
    for(auto num : nums) {
        nums_list += to_string(num) + " ";
    }
    return nums_list;
}

int main() {
    int nums_array[5];
    vector<int> nums_vector;

    for (int i = 0; i < 5; i++) {
        int temp;
        cout << "Enter a number " + to_string(i+1) + ": ";
        cin >> temp;
        nums_array[i] = temp;
        nums_vector.push_back(temp);
    }

    cout << "Array: " << to_string(nums_array) << endl;
    cout << "Vector: " << to_string(nums_vector) << endl;

    double_values(nums_array);
    double_values(&nums_vector);

    cout << "Doubled Array: " << to_string(nums_array) << endl;
    cout << "Doubled Vector: " << to_string(nums_vector) << endl;
}
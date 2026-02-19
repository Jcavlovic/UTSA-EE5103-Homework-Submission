#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

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

    char task;
    bool quit = false;
    vector<int> nums;


    while(!quit) {
        cout << "Selectable Task:\n\t1 - Enter new number\n\t2 - Display All Entered Numbers\n\t3 - Disply largest Number\n\tq - Quit\nTask: ";
        cin >> task;
        switch (task) {
            case '1': {
                int temp;
                cout << "Enter Number: ";
                cin >> temp;
                nums.push_back(temp);
                break;
            }
            case '2': {
                if (nums.size() == 0)
                    break;
                cout << "\nEntered Numbers: " << to_string(nums) << endl << endl;;
                break;
                }
            
            case '3': {
                if (nums.size() == 0)
                    break;
                cout << "\nMax Value: " << max_value(nums) << endl << endl;
                break;
                }

            case 'q':{
                quit = true;
                break;
                }
        }
    }
}
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int calculate_average(vector<int> temps) {
    /**
     * @brief Returns the average of the @param vector<int>
     * 
     * @param[in] vector of temps.
     * 
     * @return The average of the input vector.
     */

    int avg = accumulate(temps.begin(), temps.end(), 0) / temps.size();

    return avg;
}

int main() {

    int avg_temp;
    int i = 0;

    string climate;

    vector<int> temps;

    while(i < 3) {
        int temp;
        std::cout << "Enter Temperature " << i+1 << ": ";
        std::cin >> temp;

        temps.push_back(temp);
        i++;
    }

    avg_temp = calculate_average(temps);

    cout << "Average Temperature: " << avg_temp << " degrees" << endl;

    climate = avg_temp < 50 ? "Cold" : avg_temp < 80 ? "Moderate" : "Hot";

    cout << climate << " Climate" << endl;
}
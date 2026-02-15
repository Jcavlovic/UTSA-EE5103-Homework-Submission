#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

float calculate_average(vector<float> temps) {
    /**
     * @brief Returns the average of the @param vector<int>
     * 
     * @param[in] vector of temps.
     * 
     * @return The average of the input vector.
     */

    float avg = accumulate(temps.begin(), temps.end(), 0.0) / float(temps.size());

    return avg;
}

int main() {

    const int HOT = 80;
    const int COLD = 50;
    const string COLD_CLIMATE = "Cold Climate";
    const string MODERATE_CLIMATE = "Moderate Climate";
    const string HOT_CLIMATE = "Hot Climate";

    vector<float> temps;
    string climate;
    int i = 0;
    float avg_temp;

    while(i < 3) {
        float temp;
        std::cout << "Enter Temperature " << i+1 << ": ";
        std::cin >> temp;

        temps.push_back(temp);
        i++;
    }

    avg_temp = calculate_average(temps);

    cout << "Average Temperature: " << avg_temp << " degrees" << endl;

    climate = avg_temp < COLD ? COLD_CLIMATE : avg_temp < HOT ? MODERATE_CLIMATE : HOT_CLIMATE;

    cout << climate << endl;
}
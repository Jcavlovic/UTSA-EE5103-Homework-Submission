#include <iostream>
#include <list>
#include <string>

using namespace std;

void output(list<string> tasks, list<string>::iterator current) {
        /**
    * @brief Helper function to output data to console.
    * 
    * @param[in] list<string> tasks: list of strings of task.
    * @param[in] list<string>::iterator current: iterator to current position.
    * 
    */
    cout << "\nAfter erasing current task ('EmergencyStop'):" << endl;
    cout << "Current task: " << *current << endl;
    cout << "Task list: ";
    for (const auto& task : tasks) {
            cout << task << " ";
        }
    cout << endl;
}
int main() {

    list<string> tasks;

    tasks.push_back("SensorRead");
    tasks.push_back("MotorControl");
    tasks.push_back("TelemetrySend");

    list<string>::iterator current = tasks.begin();

    output(tasks, current);

    ++current;

    current = tasks.insert(current, "EmergencyStop");  

    output(tasks, current);

    current = tasks.erase(current);

    output(tasks, current);

    ++current;

    output(tasks, current);

    return 0;

    /* 
    * ------------------------------------------------------------------------
    *
    * Why list instead of vector?
    *  List provides constant-time insertion and removal anywhere
    *  in the container.
    *
    * What happens to iterators when inserting or erasing in a list?
    *  Iterators and references remain valid as long as the element they 
    *  refer to is not erased. Insertions and erasures
    *  at other positions do not change iterators to other elements.
    *
    * ------------------------------------------------------------------------
    */
}
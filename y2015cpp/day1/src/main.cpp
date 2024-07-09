// Solution for day 1 of Advent of Code 2015
// Take input from user in terminal to choose which task is performed

#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include "d1task1.hpp"
#include "d1task2.hpp"
using namespace std;

unique_ptr<string> inputpath(new string("../input"));

int main(){
    cout << "Advent of Code 2015:\n" << "Type (1) or (2) to execute task 1 or 2 of day 1." << "\n";
    int i_usr;
    cout << "Choose task: ";
    while(cin >> i_usr){
        if (cin.fail()){
            cin.clear(); // clear error state
            cout << "\nInvalid input!" <<"\n";
        }
        if (i_usr == 1){
            auto start{chrono::high_resolution_clock::now()}; // get start time
            int answer_floor = perfTaskOne(inputpath.get()); // perform task
            auto end{chrono::high_resolution_clock::now()};
            chrono::duration<double, milli> elapsed_time{end - start}; // calculate elapsed time
            cout << "Santa ends up on floor: " << answer_floor << "\n";
            cout << "Time: " << elapsed_time << "\n";
            return 0;
        }
        else if (i_usr == 2){
            auto start{chrono::high_resolution_clock::now()}; // get start time
            int answer_pos = perfTaskTwo(inputpath.get()); // perform task
            auto end{chrono::high_resolution_clock::now()};
            chrono::duration<double, milli> elapsed_time{end - start}; // calculate elapsed time
            cout << "Instruction for entering the basement is located at: " << answer_pos << "\n";
            cout << "Time: " << elapsed_time << "\n";
            return 0;
        }
    }
    if(!cin.eof()){
        cout << "Invalid input!";
    }
    cerr << "\n" << "No task was performed, something went wrong!" << "\n";
    return 1;
};
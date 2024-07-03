// Solution for day 1 of Advent of Code 2015
// Take input from user in terminal to choose which task is performed

#include <iostream>
#include <string>
#include <memory>
#include "Moves.hpp"
#include "d1task1.hpp"
#include "d1task2.hpp"
using namespace std;

unique_ptr<string> inputpath(new string("../input"));

int main(){
    bool input_err; // init error for user input

    cout << "Advent of Code 2015:\n" << "Type (1) or (2) to execute task 1 or 2 of day 1." << "\n";
    int i_usr;
    cout << "Choose task: ";
    while(cin >> i_usr){
        if (cin.fail()){
            cin.clear(); // clear error state
            cout << "\nInvalid input!" <<"\n";
        }
        if (i_usr == 1){
            int answer_floor = perfTaskOne(inputpath.get());
            cout << "Santa ends up on floor: " << answer_floor << "\n";
            return 0;
        }
        else if (i_usr == 2){
            int answer_pos = perfTaskTwo(inputpath.get());
            cout << "Instruction for entering the basement is located at: " << answer_pos << "\n";
            return 0;
        }
    }
    if(!cin.eof()){
        cout << "Invalid input!";
    }
    cerr << "\n" << "No task was performed, something went wrong!" << "\n";
    return 1;
};
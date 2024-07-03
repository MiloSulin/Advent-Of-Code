// Solution for day 1 of Advent of Code 2015
// Take input from user in terminal to choose which task is performed

#include <iostream>
#include <cassert>
#include <string>
#include <memory>
#include "ReadMoves.hpp"
#include "d1task1.hpp"
using namespace std;
#define assertm(exp, msg)

unique_ptr<string> inputpath(new string);
auto inputpath = "../input";

int main(){
    cout << "Advent of Code 2015:\n" << "Type (1) or (2) to execute task 1 or 2 of day 1." << "\n";
    int i_usr;
    cout << "Choose task:";
    cin >> i_usr;
    assertm(i_usr == 1 || i_usr == 2, "Invalid input!");
    if (i_usr == 1){
        int answer_floor = perfTaskOne(inputpath.get());
        cout << "Santa ends up on floor: " << answer_floor << "\n";
        return 0;
    }
    else if (i_usr == 2){
        cout << "Task 2 not yet implemented, come back later!" << "\n";
        return 0;
    }
    cerr << "No task was performed, something went wrong!";
    return 1;
};
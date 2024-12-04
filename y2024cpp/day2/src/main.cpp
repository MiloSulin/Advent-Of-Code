#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "../../../AdventOC.hpp"

using namespace std::chrono;
using std::cout, std::array, std::string;

void readInput(string filepath, char* w_start){
    std::fstream reader{filepath};
    if (!reader.is_open()){
        cout << "Shit broke!\n";
    }
    reader.read(w_start, 1024*1024);
    reader.close();
}


int main(){
    const auto start_t = high_resolution_clock::now();

    array<char, 128 * 1024> input;
    readInput("../input.txt", &input[0]);


        
    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Task 1 solution: " << "task1 placeholder" << '\n';
    cout << "Task 2 solution: " << "task2 placeholder" << '\n';
    cout << "Time taken: " << elapsed_time << std::endl;
    return 0;
}
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <format>
#include <cmath>
#include <array>
#include <vector>
#include "AdventOC.hpp"

using namespace std::chrono;
using std::cout, std::array, std::string;

/* 
For some reason my code always gives one too many for task 1 and two less for task 2.
 */

uint checkSafe(std::vector<int>& report, std::vector<size_t>& bad_ind){
    int delta_direction{0};
    uint is_ok{1}; // 1 or 0
    for (size_t i=0; i<report.size()-1; i++){
        int distance{report.at(i) - report.at(i+1)};
        int distance_abs{std::abs(distance)};
        int distance_dir{0};
        if (distance != 0){
            distance_dir = distance / distance_abs;
        }
        if (distance_abs < 1 || distance_abs > 3){
            is_ok = 0;
            bad_ind.push_back(i);
        } else if(delta_direction == 0 && distance != 0){
            delta_direction = distance_dir; // assign direction of level change to 1 or -1
        } else if (distance_dir != delta_direction){
            is_ok = 0;
            bad_ind.push_back(i);
        }
    }
    return is_ok;
}


int main(){
    const auto start_t = high_resolution_clock::now();

    array<char, 128 * 1024> input{};
    uint char_amount = advoc::readInput("../input.txt", &input[0], 128 * 1024);

    std::vector<string> lines = advoc::stringSplit(string{input.begin(), input.end()}, '\n');
    std::vector<std::vector<int>> num_lines;
    // convert split strings into int
    for (auto& line : lines){
        auto split_into_vec = advoc::stringSplit(line, ' '); // splits lines into individual numbers, still string
        std::vector<int> numbers{};
        for (auto& strnum : split_into_vec){
            numbers.push_back(std::stoi(strnum));
        }
        num_lines.push_back(numbers);
    }
    
    uint task1_sol{0};
    uint task2_sol{0};
    std::vector<size_t> bad_indices{};
    std::vector<int> new_report{};
    std::vector<int> new_report2{};
    for (auto& report : num_lines){
        bad_indices.clear();
        new_report.clear();
        new_report2.clear();
        uint is_ok1{0};
        is_ok1 = checkSafe(report, bad_indices); // check if level is safe
        task1_sol += is_ok1;
        
        size_t bad_amount{bad_indices.size()};
        uint is_ok2{0};
        // check if level can be saved
        if (bad_amount == report.size()-2){
            new_report.insert(new_report.end(), report.begin()+1, report.end());
            
            new_report2.insert(new_report2.end(), report.begin(), report.begin()+1);
            new_report2.insert(new_report2.end(), report.begin()+2, report.end());
            
            if (checkSafe(new_report, bad_indices) == 1 || checkSafe(new_report2, bad_indices) == 1){
                is_ok2 = 1;
            }
        } else if (bad_amount == 1){
            new_report.insert(new_report.end(), report.begin(), report.begin()+bad_indices.at(0));
            new_report.insert(new_report.end(), report.begin()+bad_indices.at(0)+1, report.end());

            new_report2.insert(new_report2.end(), report.begin(), report.begin()+bad_indices.at(0)+1);
            new_report2.insert(new_report2.end(), report.begin()+bad_indices.at(0)+2, report.end());

            if (checkSafe(new_report, bad_indices) == 1 || checkSafe(new_report2, bad_indices) == 1){
                is_ok2 = 1;
            }
        } else if (bad_amount == 2){
            size_t bad1{bad_indices.at(0)};
            size_t bad2{bad_indices.at(1)};
            if (bad2 - bad1 == 1){
                new_report.insert(new_report.end(), report.begin(), report.begin()+bad2);
                new_report.insert(new_report.end(), report.begin()+bad2+1, report.end());
                is_ok2 = checkSafe(new_report, bad_indices);
            }
        }
        task2_sol += (is_ok1 + is_ok2);
    }

    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << std::format("Task 1 solution: {}\n", task1_sol);
    cout << std::format("Task 2 solution: {}\n", task2_sol);
    cout << std::format("Time taken: {}", elapsed_time) << std::endl;
    return 0;
}
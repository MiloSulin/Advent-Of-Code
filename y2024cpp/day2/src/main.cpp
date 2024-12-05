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


int main(){
    const auto start_t = high_resolution_clock::now();

    array<char, 128 * 1024> input{};
    advoc::readInput("../input.txt", &input[0]);

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
    
    int task1_sol{0};

    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << std::format("Task 1 solution: {}\n", task1_sol);
    cout << std::format("Task 2 solution: {}\n", "task2placeholder");
    cout << std::format("Time taken: {}", elapsed_time) << std::endl;
    return 0;
}
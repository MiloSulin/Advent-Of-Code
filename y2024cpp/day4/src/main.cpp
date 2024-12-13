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
using std::cout;


int main(){
    const auto start_t = high_resolution_clock::now();

    std::array<char, 128 * 1024> input;
    uint read_chars = advoc::readInput("../input.txt", &input[0], 128*1024);

    // find row length
    size_t row_len{0};
    size_t row_amount{0};
    for (auto& c : input){
        row_len += 1;
        if (c == '\n'){
            break;
        }
    }
    row_amount = read_chars / row_len;
    if (row_len >= read_chars){
        std::cerr << std::format("Expected an input of matrix form! Was given a single line.");
    }
    std::vector<char> input_transpose{};
    input_transpose.reserve(row_amount*row_len);
    for (int i=0; i<row_len-1; i++){
        for (int j=0; j<row_amount; j++){
            input_transpose.push_back(input.at(i + j*row_len));
        }
        input_transpose.push_back('\n');
    }
    std::vector<char> input_diagonals{};
    input_diagonals.reserve(row_amount*row_len);
    

        
    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << std::format("Task 1 solution: {}\n", "task1placeholder");
    cout << std::format("Task 2 solution: {}\n", "task2placeholder");
    cout << std::format("Time taken: {}", elapsed_time) << std::endl;
    return 0;
}
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cstring>
#include <format>
#include <cmath>
#include <array>
#include <vector>
#include "AdventOC.hpp"

using namespace std::chrono;
using std::cout;

constexpr std::string allowed_symbols{"0123456789,"};

struct MultiPair{
    uint x{0};
    uint y{0};
};

struct FilterRange{
    uint start{0};
    uint end{0};
};


int main(){
    const auto start_t = high_resolution_clock::now();

    std::array<char, 128 * 1024> input;
    size_t char_amount = advoc::readInput("../input.txt", &input[0], 128*1024);

    uint task1_sol{0};
    uint task2_sol{0};

    std::array<MultiPair, 1024> valid_data{0};
    std::array<FilterRange, 128> filters{0};
    size_t data_counter{0};
    FilterRange* current_filter = &filters[0];
    size_t start_pos{0};
    size_t current_pos{0};
    uint8_t loop_success{0};
    for (size_t i=0; i<char_amount; i++){
        if ( std::strncmp(&input[i], "don't()", 7) == 0 && current_filter->start == 0 ){
            current_filter->start = data_counter;
            current_filter->end = valid_data.size();
        } else if ( std::strncmp(&input[i], "do()", 4) == 0 && current_filter->start != 0 ){
            current_filter->end = data_counter;
            current_filter += 1;
        } else if ( std::strncmp(&input[i], "mul(", 4) == 0 ){
            start_pos = i+4;
            current_pos = i+4;
            loop_success = 1;
            while (input.at(current_pos) != ')'){
                if (current_pos - start_pos > 7){
                    loop_success = 0;
                    break;
                } else if (allowed_symbols.contains( input.at(current_pos) )){
                    current_pos += 1;
                } else{
                    loop_success = 0;
                    break;
                }
            }
            if (loop_success == 1){
                std::vector<std::string> multiply_args = advoc::stringSplit(std::string{input.begin()+start_pos, input.begin()+current_pos}, ',');
                if (multiply_args.size() == 2){
                    valid_data.at(data_counter).x = std::stoi(multiply_args.at(0));
                    valid_data.at(data_counter).y = std::stoi(multiply_args.at(1));
                    data_counter += 1;
                }
            }
        }
    }

    current_filter = &filters[0];
    MultiPair* data_point = &valid_data[0];
    for (size_t i=0; i<data_counter+1; i++){
        // cout << std::format("[{}, {}]\n", data_point.x, data_point.y);
        task1_sol += data_point->x * data_point->y;
        if ( i < current_filter->start){
            task2_sol += data_point->x * data_point->y;
        } else if (i >= current_filter->end){
            task2_sol += data_point->x * data_point->y;
            current_filter += 1;
        }
        data_point += 1;
    }


    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << std::format("Task 1 solution: {}\n", task1_sol);
    cout << std::format("Task 2 solution: {}\n", task2_sol);
    cout << std::format("Time taken: {}", elapsed_time) << std::endl;
    return 0;
}
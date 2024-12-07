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

constexpr std::string allowed_symbols{"0123456789,)"};

struct multiPair{
    uint x{0};
    uint y{0};
};

int main(){
    const auto start_t = high_resolution_clock::now();

    std::array<char, 128 * 1024> input;
    size_t char_amount = advoc::readInput("../input.txt", &input[0], 128*1024);

    uint task1_sol{0};
    std::array<multiPair, 1024> valid_data{0};
    size_t data_counter{0};
    for (size_t i=0; i<char_amount; i++){
        if ( input.at(i) == 'm' && input.at(i+1) == 'u' && input.at(i+2) == 'l' && input.at(i+3) == '('){
            auto& data_point = valid_data.at(data_counter);
            size_t start_pos{i+4};
            size_t current_pos{i+4};
            while ( allowed_symbols.contains(input.at(current_pos)) ){
                if (input.at(current_pos) == ','){
                    cout << std::string{input.begin()+start_pos, input.begin()+current_pos} << '\n';
                    data_point.x = std::stoi(std::string{input.begin()+start_pos, input.begin()+current_pos});
                    start_pos = current_pos+1;
                } else if (input.at(current_pos) == ')' && current_pos-start_pos <=3){
                    cout << std::string{input.begin()+start_pos, input.begin()+current_pos} << '\n';
                    data_point.y = std::stoi(std::string{input.begin()+start_pos, input.begin()+current_pos});
                }
                current_pos +=1;
                if (data_point.x != 0 && data_point.y != 0){
                    data_counter += 1;
                } else{
                    data_point.x = 0;
                    data_point.y = 0;
                }
            }
        }
    }

    for (auto& data_point : valid_data){
        task1_sol += data_point.x * data_point.y;
    }

    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << std::format("Task 1 solution: {}\n", task1_sol);
    cout << std::format("Task 2 solution: {}\n", "task2placeholder");
    cout << std::format("Time taken: {}", elapsed_time) << std::endl;
    return 0;
}
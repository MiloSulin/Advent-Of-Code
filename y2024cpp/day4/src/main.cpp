#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <format>
#include <cmath>
#include <array>
#include <vector>
#include <cstring>
#include "../../../AdventOC.hpp"

using namespace std::chrono;
using std::cout;

std::vector<char> getDiagonals(std::array<char, 128*1024>& in_arr, size_t row_len, size_t col_len, uint8_t direction){
    if (direction != 1 && direction != 0){
        std::cerr << std::format("Direction of diagonals only takes 1 or 0 as argument! Was given {}\n", direction);
    }
    std::vector<char> diagonal_input{};
    diagonal_input.reserve(row_len * col_len);
    size_t line_length{1};
    size_t max_line_len{std::min(row_len-1, col_len)};
    size_t step_size{0};
    switch (direction){
        case 0:
            step_size = row_len+1;
            // Add diagonal lines that start on the first original line
            for (int i=row_len-2; i >= 0; i--){
                for (size_t j=0; j<line_length; j++){
                    diagonal_input.push_back(in_arr.at(i + j*step_size));
                }
                if (line_length < max_line_len){
                    line_length += 1;
                }
                diagonal_input.push_back('\n');
            }
            // Add diagonal lines that start on the first column (excluding the very first symbol)
            line_length -= 1;
            for (size_t i=1; i<max_line_len; i++){
                if (line_length < 1){
                    std::cerr << std::format("Something has gone very wrong!\n");
                }
                for (size_t j=0; j<line_length; j++){
                    diagonal_input.push_back(in_arr.at(i*row_len + j*step_size));
                }
                diagonal_input.push_back('\n');
                line_length -= 1;
            }
            break;
        case 1:
            step_size = row_len-1;
            // Add diagonal lines that start on the first original line
            for (size_t i=0; i<row_len-1; i++){
                for (size_t j=0; j<line_length; j++){
                    diagonal_input.push_back(in_arr.at(i + j*step_size));
                }
                if (line_length < max_line_len){
                    line_length += 1;
                }
                diagonal_input.push_back('\n');
            }
            // Add diagonal lines that start on the first column (excluding the very first symbol)
            line_length -= 1;
            for (size_t i=2; i<col_len+1; i++){
                if (line_length < 1){
                    std::cerr << std::format("Something has gone very wrong!\n");
                }
                for (size_t j=0; j<line_length; j++){
                    diagonal_input.push_back(in_arr.at(i*row_len -2 + j*step_size));
                }
                diagonal_input.push_back('\n');
                line_length -= 1;
            }
            break;
        default:
            std::cerr << "Shouldn't happen!\n";
            break;
    }
    return diagonal_input;
}

int main(){
    const auto start_t = high_resolution_clock::now();

    std::array<char, 128 * 1024> input{};
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
    /*cout << std::format("row length: {}\n", row_len);*/
    row_amount = read_chars / row_len;
    /*cout << std::format("row amount: {}\n", row_amount);*/
    if (row_len >= read_chars){
        std::cerr << std::format("Expected an input of matrix form! Was given a single line.");
    }
    std::vector<char> input_transpose{};
    input_transpose.reserve(row_amount*row_len);
    for (size_t i=0; i<row_len-1; i++){
        for (size_t j=0; j<row_amount; j++){
            input_transpose.push_back(input.at(i + j*row_len));
        }
        input_transpose.push_back('\n');
    }

    // Get the diagonal "lines" of the input
    std::vector<char> diagonal_input1 = getDiagonals(input, row_len, row_amount, 0);
    std::vector<char> diagonal_input2 = getDiagonals(input, row_len, row_amount, 1);
    
    // Search for every occurence of the word or its reverse
    size_t task1_sol{0};
    // calculate word on rows and columns
    char* arr_pos = &input[0];
    char* transpose_pos = &input_transpose[0];
    for (size_t i=0; i<read_chars; i++){
        if (std::strncmp(arr_pos, "XMAS", 4) == 0 || std::strncmp(arr_pos, "SAMX", 4) == 0 ){
            task1_sol += 1;
        }
        if (std::strncmp(transpose_pos, "XMAS", 4) == 0 || std::strncmp(transpose_pos, "SAMX", 4) == 0){
            task1_sol += 1;
        }
        transpose_pos += 1;
        arr_pos += 1;
    }
    // and now for diagonals
    char* diag1_pos = &diagonal_input1[0];
    char* diag2_pos = &diagonal_input2[0];
    for (size_t i=0; i<diagonal_input1.size(); i++){
        if (std::strncmp(diag1_pos, "XMAS", 4) == 0 || std::strncmp(diag1_pos, "SAMX", 4) == 0 ){
            task1_sol += 1;
        }
        if (std::strncmp(diag2_pos, "XMAS", 4) == 0 || std::strncmp(diag2_pos, "SAMX", 4) == 0 ){
            task1_sol += 1;
        }
        diag1_pos += 1;
        diag2_pos += 1;
    }
    
    // check for cross words
    size_t task2_sol{0};
    uint current_loc{0};
    char cross_diag1[4] = {' ', 'A', ' '};
    char cross_diag2[4] = {' ', 'A', ' '};
    bool diag1_istrue{false};
    bool diag2_istrue{false};
    for (size_t i=1; i<row_amount-1; i++){
        for (size_t j=1; j<row_len-2; j++){
            current_loc = i*row_len +j;
            if (input[current_loc] == 'A'){
                cross_diag1[0] = input[ (i-1)*row_len + (j-1) ];
                cross_diag1[2] = input[ (i+1)*row_len + (j+1) ];
                cross_diag2[0] = input[ (i-1)*row_len + (j+1) ];
                cross_diag2[2] = input[ (i+1)*row_len + (j-1) ];
                if (std::strncmp(&cross_diag1[0], "MAS", 3) == 0 || std::strncmp(&cross_diag1[0], "SAM", 3) == 0 ){
                    diag1_istrue = true;
                } else{
                    diag1_istrue = false;
                }
                if (std::strncmp(&cross_diag2[0], "MAS", 3) == 0 || std::strncmp(&cross_diag2[0], "SAM", 3) == 0 ){
                    diag2_istrue = true;
                } else{
                    diag2_istrue = false;
                }
                // final check
                if (diag1_istrue && diag2_istrue){
                    task2_sol += 1;
                }
            }
        }
    }
    
    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << std::format("Task 1 solution: {}\n", task1_sol);
    cout << std::format("Task 2 solution: {}\n", task2_sol);
    cout << std::format("Time taken: {}", elapsed_time) << std::endl;
    return 0;
}

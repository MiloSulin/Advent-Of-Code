
#include <string>
#include <array>
#include <iostream>
#include "Instruction.hpp"

Instruction::Instruction(std::string Action, std::array<int, 4> start_end_p) {
    if(Action == "on"){
        action = '>';
    } else if(Action == "off"){
        action = '<';
    } else if(Action == "toggle"){
        action = '^';
    } else{
        std::cerr << "Instruction: Invalid input for action!\n";
    }
    x = start_end_p[2] - start_end_p[0] +1;
    y = start_end_p[3] - start_end_p[1] +1;
    start_point = (start_end_p[1] - 1) * 1024 + start_end_p[0];
};
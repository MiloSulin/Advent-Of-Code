#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <string>
#include <array>

struct Instruction{
    Instruction(std::string , std::array<int, 4>);
    // type of action to perform, can be: '<' turn off, '>' turn on, '^' toggle
    char action;
    // starting coordinate
    int start_point;
    // dimensions of the area in x and y directions
    int x;
    int y;
};

#endif
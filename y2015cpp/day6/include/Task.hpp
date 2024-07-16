#ifndef __TASK_H__
#define __TASK_H__

#include <vector>
#include <array>
#include "Instruction.hpp"

struct Results{
    int task1;
    int task2;
};

void turnOn(bool& );
void turnOff(bool& );
void toggle(bool& );

void turnUp(int& );
void turnDown(int& );
void turnUpTwo(int& );

Results performTasks(std::vector<Instruction>* );

#endif
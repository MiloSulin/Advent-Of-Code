#ifndef __TASK_H__
#define __TASK_H__

#include <vector>
#include <array>
#include "Instruction.hpp"
struct Results{
    int task1;
    int task2;
};

Results performTasks(std::vector<Instruction>* );

#endif
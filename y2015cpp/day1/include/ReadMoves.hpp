#ifndef __READ_INPUT_H__
#define __READ_INPUT_H__
// reads input and saves as struct

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Moves
{
    // includes the amount of up and down movements read from input
    int upwards;
    int downwards;
};

void readInput(string* inputpath, Moves* moves);

#endif
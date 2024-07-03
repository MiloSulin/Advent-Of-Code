#include "d1task1.hpp"

// Perform task one of puzzle, calculate which floor Santa ends up on
int perfTaskOne(string* inputpath){
    Moves* moves1(new Moves{}); // allocate mem for Moves struct to save upwards and downwards moves
    readInput(inputpath, moves1);
    int end_floor = moves1->upwards -moves1->downwards; // calculate final floor by subtracting downwards movements from upwards ones
    delete moves1; // free mem
    return end_floor;
};
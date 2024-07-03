#include "d1task1.hpp"

// Perform task one of puzzle, calculate which floor Santa ends up on
int perfTaskOne(string* inputpath){
    Moves* moves1(new Moves{}); // allocate mem for Moves struct to save upwards and downwards moves
    
    ifstream input_stream(*inputpath, ios::binary); // create input stream from /path/to/input
    if (!input_stream.is_open())
        cerr << "Failed to open!" << "\n"; // throw error if something goes wrong when opening file
    else{
        char* current_char = new char(); // allocate memory for char that is read from file
        //
        while(input_stream.get(*current_char)){ // read first/next character from file and terminate loop when end of file is reached
            if (*current_char == '('){ // if current_char is '(' go up one floor
                moves1->upwards += 1;
            }
            else if (*current_char == ')'){ // if current_char is ')' go down one floor
                moves1->downwards += 1;
            }
        }
        delete current_char; // free memory
    };

    int end_floor = moves1->upwards - moves1->downwards; // calculate final floor by subtracting downwards movements from upwards ones
    delete moves1; // free mem
    return end_floor;
};
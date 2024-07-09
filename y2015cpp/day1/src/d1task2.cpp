#include "d1task2.hpp"

// Perform task 2 of first puzzle, find location of instruction that tells Santa to enter basemen (floor -1)
int perfTaskTwo(string* inputpath){
    int santa_loc = 0; // track location
    int pos = 0;
    ifstream input_stream(*inputpath, ios::binary | ios::ate); // create input stream from /path/to/input
    if (!input_stream.is_open())
        cerr << "Failed to open!" << "\n"; // throw error if something goes wrong when opening file
    else{
        int size = input_stream.tellg();
        char instructions[size]; // allocate memory for chars
        input_stream.seekg(0);
        input_stream.read(instructions, size);
        input_stream.close();
        int i = 0;
        while(santa_loc > -1){ // iterate through instructions until basement is entered
            if (instructions[i] == '('){ // if current_char is '(' go up one floor
                santa_loc++;
            }
            else if (instructions[i] == ')'){ // if current_char is ')' go down one floor
                santa_loc--;
            }
            i++;
        }
        pos = i;
    };
    return pos;
}
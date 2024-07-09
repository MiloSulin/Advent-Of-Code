#include "d1task1.hpp"

// Perform task one of puzzle, calculate which floor Santa ends up on
int perfTaskOne(string* inputpath){
    int santa_loc = 0;
    
    ifstream input_stream(*inputpath, ios::binary | ios::ate); // create input stream from /path/to/input
    if (!input_stream.is_open())
        cerr << "Failed to open!" << "\n"; // throw error if something goes wrong when opening file
    else{
        int size = input_stream.tellg();
        char instructions[size]; // initialise array for read chars
        input_stream.seekg(0);
        input_stream.read(reinterpret_cast<char*>(instructions), size);
        input_stream.close();
        for (int i=0; i < size; i++){ // iterate through instructions
            if (instructions[i] == '('){ // if current_char is '(' go up one floor
                santa_loc++;
            }
            else if (instructions[i] == ')'){ // if current_char is ')' go down one floor
                santa_loc--;
            }
        }
    };
    return santa_loc;
};
#include "d1task1.hpp"

// Perform task one of puzzle, calculate which floor Santa ends up on
int perfTaskOne(string* inputpath){
    int santa_loc = 0;
    
    ifstream input_stream(*inputpath, ios::binary); // create input stream from /path/to/input
    if (!input_stream.is_open())
        cerr << "Failed to open!" << "\n"; // throw error if something goes wrong when opening file
    else{
        char* current_char = new char(); // allocate memory for char that is read from file
        //
        while(input_stream.get(*current_char)){ // read first/next character from file and terminate loop when end of file is reached
            if (*current_char == '('){ // if current_char is '(' go up one floor
                santa_loc++;
            }
            else if (*current_char == ')'){ // if current_char is ')' go down one floor
                santa_loc--;
            }
        }
        delete current_char; // free memory
    };

    return santa_loc;
};
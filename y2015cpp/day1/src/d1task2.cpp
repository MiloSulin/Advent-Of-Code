#include "d1task2.hpp"

// Perform task 2 of first puzzle, find location of instruction that tells Santa to enter basemen (floor -1)
int perfTaskTwo(string* inputpath){
    Moves* moves2(new Moves{}); // initialise moves struct
    
    ifstream input_stream(*inputpath, ios::binary); // create input stream from /path/to/input
    if (!input_stream.is_open())
        cerr << "Failed to open!" << "\n"; // throw error if something goes wrong when opening file
    else{
        char* current_char = new char(); // allocate memory for char that is read from file
        //
        while(moves2->santa_loc > -1 && input_stream.get(*current_char)){ // read first/next character from file and terminate loop when end of file is reached or if Santa enter the basement
            if (*current_char == '('){ // if current_char is '(' go up one floor
                moves2->santa_loc += 1;
            }
            else if (*current_char == ')'){ // if current_char is ')' go down one floor
                moves2->santa_loc -= 1;
            }
        }
        if(input_stream.eof())
            cout << "Luettiin loppuun." << "\n";
        delete current_char; // free memory
    };
    delete moves2; // free mem
    int base_pos = input_stream.tellg();
    return base_pos;
}
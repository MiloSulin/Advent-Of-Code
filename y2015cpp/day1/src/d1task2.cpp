#include "d1task2.hpp"

// Perform task 2 of first puzzle, find location of instruction that tells Santa to enter basemen (floor -1)
int perfTaskTwo(string* inputpath){
    int santa_loc = 0;

    ifstream input_stream(*inputpath, ios::binary); // create input stream from /path/to/input
    if (!input_stream.is_open())
        cerr << "Failed to open!" << "\n"; // throw error if something goes wrong when opening file
    else{
        char* current_char = new char(); // allocate memory for char that is read from file
        //
        while(santa_loc > -1 && input_stream.get(*current_char)){ // read first/next character from file and terminate loop when end of file is reached or if Santa enter the basement
            if (*current_char == '('){ // if current_char is '(' go up one floor
                santa_loc++;
            }
            else if (*current_char == ')'){ // if current_char is ')' go down one floor
                santa_loc--;
            }
        }
        if(input_stream.eof())
            cout << "Luettiin loppuun." << "\n";
        delete current_char; // free memory
    };
    int base_pos = input_stream.tellg();
    return base_pos;
}
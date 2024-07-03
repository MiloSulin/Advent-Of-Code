#include "ReadMoves.hpp"
using namespace std;

// read given input be it txt or ASCII
void readInput(string* inputpath, Moves* moves){
    ifstream input_stream(*inputpath, ios::binary); // create input stream from /path/to/input
    if (!input_stream.is_open())
        cerr << "Failed to open!" << "\n"; // throw error if something goes wrong when opening file
    else{
        char* current_char = new char(); // allocate memory for char that is read from file
        //
        while(!input_stream.eof()){ // terminate loop when end of file is reached
            input_stream.get(*current_char); // read first/next character from file
            if ('(' & ~*current_char == 0) // if current_char is '(' go up one floor
                moves->upwards += 1;
            else if (')' & ~*current_char == 0) // if current_char is ')' go down one floor
                moves->downwards += 1;
        }
        delete current_char; // free memory
    };
};
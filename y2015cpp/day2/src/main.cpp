// solution for puzzle of day 2

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <chrono>
#include "Present.hpp"
using namespace std;

const string infile = "../input.txt";

int main(){
    auto start_t = chrono::high_resolution_clock::now();
    int total_paper = 0;
    int total_ribbon = 0;
    // read input file
    ifstream instr(infile, ios::binary); // init input stream
    if (!instr.is_open()){
        cout << "Error: File couldn't be opened!" << '\n';
        return 1;
    }
    int* line{new int[3]};
    char xnl; // check that the next char is 'x' or 'nl' and skip
    while(!instr.eof()){
        for (int i=0; i<3; ++i){
            instr >> line[i];
            xnl = instr.peek(); // check that the next char is 'x' or 'nl' and skip
            if (xnl == 'x' || xnl == '\n' || xnl == '\0'){
                instr.get(xnl);
            }
        }
        if(!instr.eof()){
            unique_ptr<Present> new_present{new Present{line[0], line[1], line[2]}};
            total_paper += new_present->wrapPaperAmount();
            total_ribbon += new_present->ribbonAmount();
        }
    }
    auto end_t = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed_time{end_t - start_t};
    cout << "Total wrapping paper amount: " << total_paper << " sqft\n";
    cout << "Total ribbon amount: " << total_ribbon << " ft\n";
    cout << "Elapsed time: " << elapsed_time << '\n';
    return 0;
}
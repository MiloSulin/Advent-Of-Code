#include <iostream>
#include <unordered_map>
#include <fstream>
#include <array>
#include <string>
#include <exception>
#include <chrono>
#include <vector>
#include <cmath>
#include <unordered_set>
#include "Instruction.hpp"

using namespace std::chrono;
using std::cout, std::unordered_map, std::fstream, std::array, std::string, std::vector, std::unordered_set;


array<char, 1024*1024> input;

void readInput(string filepath){ 
    fstream reader{filepath};
    if(!reader.is_open()){
        throw std::runtime_error("Something wen't wrong when opening input file!") ;
    }
    reader.read(&input[0], 1024*1024);
    reader.close();
}


int main(){
    const auto start_t = high_resolution_clock::now();

    readInput("../input.txt");
    char* inptr = &input[0];
    vector<string> temp{};
    vector<Instruction*> instructions{};
    while((*inptr) != '\0'){
        string instruct{};
        while((*inptr) != ' ' && (*inptr) != '\n'){
            instruct += *inptr;
            inptr++;
        }
        temp.push_back(instruct);
        if(*inptr == '\n'){
            instructions.push_back(new Instruction{temp});
            temp.clear();
        }
        inptr++;
    }
    for (int i=0; i<15; ++i){
        cout << *(instructions[i]) <<'\n';
    }
    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};

    cout << "Time taken: " << elapsed_time << std::endl;
    return 0;
}
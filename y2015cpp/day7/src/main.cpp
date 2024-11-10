#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <exception>
#include <chrono>
#include <vector>
#include <cmath>
#include "Circuit.hpp"

using namespace std::chrono;
using std::cout, std::unordered_map, std::fstream, std::array, std::string, std::vector, std::unordered_set;



void readInput(string filepath, char* write_start){ 
    fstream reader{filepath};
    if(!reader.is_open()){
        throw std::runtime_error("Something went wrong when opening input file!") ;
    }
    reader.read(write_start, 1024*1024);
    reader.close();
}

vector<Instruction*> buildInstructions(char* pointer_to_input){
    vector<string> temp{};
    vector<Instruction*> instructions{};
    while((*pointer_to_input) != '\0'){
        string instruct{};
        while((*pointer_to_input) != ' ' && (*pointer_to_input) != '\n'){
            instruct += *pointer_to_input;
            pointer_to_input++;
        }
        temp.push_back(instruct);
        if(*pointer_to_input == '\n'){
            instructions.push_back(new Instruction{temp});
            temp.clear();
        }
        pointer_to_input++;
    }
    return instructions;
}

int main(){
    const auto start_t = high_resolution_clock::now();

    array<char, 1024 * 1024> input;
    readInput("../input.txt", &input[0]);
    
    char* inptr = &input[0];
    auto instructions = buildInstructions(inptr);
    Circuit bobbys_circuit = Circuit(instructions);
    cout << "Result for task 1: " << bobbys_circuit.returnWire("a") << "\n";

    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};

    cout << "Time taken: " << elapsed_time << std::endl;
    return 0;
}
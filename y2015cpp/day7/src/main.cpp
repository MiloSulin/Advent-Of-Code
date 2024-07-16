#include <iostream>
#include <unordered_map>
#include <fstream>
#include <array>
#include <string>
#include <exception>
#include <chrono>
using namespace std::chrono;
using std::cout, std::unordered_map, std::fstream, std::array, std::string;

array<char, 1024*1024> input;

void readInput(string filepath){
    fstream reader{filepath};
    if(!reader.is_open()){
        throw std::runtime_error("Something wen't wrong when opening input file!") ;
    }
    reader.read(&input[0], 1024*1024);
    reader.close();
}

struct Actions {
    "AND" : & ;
    "OR" : | ;
    "NOT" : ~ ;
    "RSHIFT" : >> ;
    "LSHIFT" : << ;
    "->" : assign ;
}

int main(){
    const auto start_t = high_resolution_clock::now();

    readInput("../input.txt");
    while ()

    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Time taken: " << elapsed_time << std::endl;
    return 0;
}
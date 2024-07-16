/* 
READ LIGHTING INSTRUCTIONS
TASK 1: How many std::begin(lights) are on?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <chrono>
#include <algorithm>
#include "Instruction.hpp"
#include "Task.hpp"

using namespace std::chrono;
using std::cout, std::cerr, std::string, std::array, std::vector, std::fstream;

constexpr string allowed_actions = "on off toggle";


vector<Instruction> readInput(const string& filepath){
    // read file into fstream
    fstream reader(filepath);
    if(!reader.is_open()){
        cerr << "File couldn't be opened!\n";
    }
    // init containers
    vector<Instruction> input;
    string action;
    int start1;
    int start2;
    int end1;
    int end2;
    // trash bins for unwanted parts of input
    char trashbin1;
    string trashbin2;
    char trashbin3;

    int file_pos{0};

    while(reader >> action >> action){
        if(!allowed_actions.contains(action)){
            reader.seekg(file_pos);
            reader >> action >> start1 >> trashbin1 >> start2 >> trashbin2 >> end1 >> trashbin3 >> end2;
        } else{
            reader >> start1 >> trashbin1 >> start2 >> trashbin2 >> end1 >> trashbin3 >> end2;
        }
        array<int, 4> start_end_p{start1, start2, end1, end2};
        input.push_back(Instruction{action, start_end_p});
        file_pos = reader.tellg();
    }
    
    return input;
}




int main(){
    auto start_t = high_resolution_clock::now();
        
    auto input = readInput("../input.txt");
    auto [lights1, lights2] = performTasks(&input);

    auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};

    cout << "Lights in task 1: " << lights1 << '\n';
    cout << "Light instensity in task 2: " << lights2 << '\n';
    cout << "Time taken: " << elapsed_time << std::endl;
    
    return 0;
}
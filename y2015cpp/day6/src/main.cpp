/* 
READ LIGHTING INSTRUCTIONS
TASK 1: How many lights are on?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <stdexcept>
#include <valarray>
#include <chrono>

using namespace std::chrono;
using std::cout, std::cerr, std::string, std::array, std::vector, std::fstream, std::valarray;

constexpr string allowed_actions = "on off toggle";

valarray<bool> lights_on(true, 1000*1000);
valarray<bool> lights_off(false, 1000*1000);


struct Instruction{
    Instruction(string action, array<int, 4> start_end_p);
    // type of action to perform, can be: '<' turn off, '>' turn on, '^' toggle
    char action;
    // starting coordinate
    size_t start_point;
    // dimensions of the area in x and y directions
    uint64_t x;
    uint64_t y;
};
Instruction::Instruction(string Action, array<int, 4> start_end_p) {
    if(Action == "on"){
        action = '>';
    } else if(Action == "off"){
        action = '<';
    } else if(Action == "toggle"){
        action = '^';
    } else{
        cerr << "Instruction: Invalid input for action!\n";
    }
    x = start_end_p[2] - start_end_p[0];
    y = start_end_p[3] - start_end_p[1];
    start_point = (start_end_p[1] - 1) * 1000 + start_end_p[0];
};

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
    int test=0;
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
    const auto start_t = high_resolution_clock::now();
    int light_count{0};
    auto input = readInput("../input.txt");
    valarray<bool> lights(false, 1000*1000);
    for (auto& e : input){
        std::gslice slice(e.start_point, {e.y, e.x}, {1000, 1});
        if(e.action == '>'){
            lights[slice] |= lights_on[slice];
        } else if(e.action == '<'){
            lights[slice] &= lights_off[slice];
        } else if(e.action == '^'){
            lights[slice] ^= lights_on[slice];
        }
    }
    for (auto& e : lights){
        cout << e;
    }
    // valarray<bool> test(5*5);
    // std::gslice slice(2, {3, 3}, {5, 1});
    // test[slice] |= lights_on[slice];
    // for(int i=0; i<25; ++i){
    //     cout << test[i] << ' ';
    //     if(i+1 % 5 == 0){
    //         cout << '\n';
    //     }
    // }
    // cout << '\n';

    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Lights in task 1: " << light_count << '\n';
    cout << "Time taken: " << elapsed_time << std::endl;
    
    return 0;
}
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
#include <span>
#include <chrono>
#include <algorithm>

using namespace std::chrono;
using std::cout, std::cerr, std::string, std::array, std::vector, std::fstream;

constexpr string allowed_actions = "on off toggle";


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
    x = start_end_p[2] - start_end_p[0] +1;
    y = start_end_p[3] - start_end_p[1] +1;
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

void turnOn(bool& n){
    n |= true;
}
void turnOff(bool& n){
    n &= false;
}
void toggle(bool& n){
    n ^= true;
}

void turnUp(int& n){
    n++;
}
void turnDown(int& n){
    if(n!=0){
        n--;
    }
}
void turnUpTwo(int& n){
    n += 2;
}

struct Results{
    int task1;
    int task2;
};

Results performTasks(vector<Instruction>* input){
    int light_count{0};
    array<bool, 1000*1000> lights{false};
    array<int, 1000*1000> lights2{0};
    for (auto e : *input){
        if(e.action == '>'){
            for(int i=0; i<e.y; ++i){
                std::for_each(lights.begin()+e.start_point+(i*1000), lights.begin()+e.x+e.start_point+(i*1000), turnOn);
                std::for_each(lights2.begin()+e.start_point+(i*1000), lights2.begin()+e.x+e.start_point+(i*1000), turnUp);
            }
        }else if(e.action == '<'){
            for(int i=0; i<e.y; ++i){
                std::for_each(lights.begin()+e.start_point+(i*1000), lights.begin()+e.x+e.start_point+(i*1000), turnOff);
                std::for_each(lights2.begin()+e.start_point+(i*1000), lights2.begin()+e.x+e.start_point+(i*1000), turnDown);
            }
        }else if(e.action == '^'){
            for(int i=0; i<e.y; ++i){
                std::for_each(lights.begin()+e.start_point+(i*1000), lights.begin()+e.x+e.start_point+(i*1000), toggle);
                std::for_each(lights2.begin()+e.start_point+(i*1000), lights2.begin()+e.x+e.start_point+(i*1000), turnUpTwo);
            }
        }
    }

    for(auto e : lights){
        if(e){
            light_count++;
        }
    }
    int intensity_sum{0};
    for(int j=0; j<lights2.size(); j+=4){
        intensity_sum += lights2[j];
        intensity_sum += lights2[j+1];
        intensity_sum += lights2[j+2];
        intensity_sum += lights2[j+3];
    }

    return {light_count, intensity_sum};
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
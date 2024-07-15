/* 
READ LIGHTING INSTRUCTIONS
TASK 1: How many lights are on?
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>

using std::cout, std::cerr, std::string, std::array, std::vector, std::fstream, std::stringstream;

constexpr string number_digits = "0123456789";
constexpr string allowed_actions = "on off toggle";

struct Instruction{
    Instruction(string action, array<int, 4> start_end_p);
    // type of action to perform, can be: '<' turn off, '>' turn on, '^' toggle
    char action;
    // starting coordinate
    int start_point;
    // dimensions of the area in x and y directions
    int x;
    int y;
};
Instruction::Instruction(string Action, array<int, 4> start_end_p) {
    if(Action == "on"){
        action = '>';
    } else if(Action == "off"){
        action = '<';
    } else if(Action == "toggle"){
        action = '^';
    } else{
        cerr << "Invalid input of action in Instruction!\n";
    }
    x = {start_end_p[2] - start_end_p[0]};
    y = {start_end_p[3] - start_end_p[1]};
    start_point = (start_end_p[0] * 1000) + start_end_p[1];
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
    auto input = readInput("../input.txt");
    for (int i=0; i<20; ++i){
        cout << input[i].action << '\n';
        cout << input[i].start_point << '\n';
        cout << input[i].x << '\n';
        cout << input[i].y << '\n';
    }
    cout << std::endl;
    return 0;
}
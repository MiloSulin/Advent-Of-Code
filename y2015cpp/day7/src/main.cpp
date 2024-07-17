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

using namespace std::chrono;
using std::cout, std::unordered_map, std::fstream, std::array, std::string, std::vector, std::unordered_set;

array<char, 1024*1024> input;
constexpr string number_digits = "0123456789";

void readInput(string filepath){
    fstream reader{filepath};
    if(!reader.is_open()){
        throw std::runtime_error("Something wen't wrong when opening input file!") ;
    }
    reader.read(&input[0], 1024*1024);
    reader.close();
}

unordered_set<string> Actions = {"AND", "OR", "NOT", "RSHIFT", "LSHIFT"};

struct Instruction {
    Instruction(vector<string>);
    string input1{};
    string input2{};
    string Action{};
    int value{};
    string output;
};
Instruction::Instruction(vector<string> input){
    bool assign{false};
    for (auto& e : input){
        if(assign == true){
            output = e;
        }else if(number_digits.contains(e[0])){
            int magnitude = e.length() -1;
            for (auto& c : e){
                value += (c - '0') * std::pow(10, magnitude);
                magnitude--;
            } 
        }else if(Actions.contains(e)){
            Action = e;
        }else if(e == "->"){
            assign = true;
        }else if(Action.empty()){
            input1 = e;
        }else if(!Action.empty()){
            input2 = e;
        }
    }
};

std::ostream &operator<<(std::ostream &stream, const Instruction &out_instr){
    stream << out_instr.input1 << ' ';
    stream << out_instr.Action << ' ';
    stream << out_instr.input2 << ' ';
    stream << out_instr.value << ' ';
    stream << "-> ";
    stream << out_instr.output;
    return stream;
};



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
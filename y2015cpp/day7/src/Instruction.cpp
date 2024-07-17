#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_set>
#include "Instruction.hpp"

using std::cout, std::string, std::vector, std::unordered_set;

const string Actions = "ANDORNOTRSHIFTLSHIFT";
constexpr string number_digits = "0123456789";

Instruction::Instruction(vector<string> input){
    bool assign{false};
    for (auto &e : input){
        if (assign == true){
            output = e;
        }
        else if (number_digits.contains(e[0])){
            int magnitude = e.length() - 1;
            for (auto &c : e){
                value += (c - '0') * std::pow(10, magnitude);
                magnitude--;
            }
        }
        else if (Actions.contains(e)){
            Action = e;
        }
        else if (e == "->"){
            assign = true;
        }
        else if (Action.empty()){
            input1 = e;
        }
        else if (!Action.empty()){
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
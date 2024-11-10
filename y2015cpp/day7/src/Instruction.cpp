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
    act = Action::IASSIGN;
    bool assign{false};
    for (auto &e : input){
        if (assign == true){
            output = e;
        }
        else if (number_digits.contains(e[0])){
            value = 0;
            int magnitude = e.length() - 1;
            for (auto &c : e){
                value += (c - '0') * std::pow(10, magnitude);
                magnitude--;
            }
        }
        else if (Actions.contains(e)){
            if (e == "AND") {
                act = Action::IAND;
            } else if (e == "OR") {
                act = Action::IOR;
            } else if (e == "NOT") {
                act = Action::INOT;
            } else if (e == "RSHIFT") {
                act = Action::IRSHIFT;
            } else if (e == "LSHIFT") {
                act = Action::ILSHIFT;
            }
        }
        else if (e == "->"){
            assign = true;
        }
        else if (act == Action::IASSIGN){
            input1 = e;
        }
        else if (act != Action::IASSIGN){
            input2 = e;
        }
    }
};

std::ostream &operator<<(std::ostream &stream, const Instruction &out_instr){
    stream << out_instr.input1 << ' ';
    
    switch (out_instr.act) {
        case Instruction::Action::IAND : cout << "AND "; break;
        case Instruction::Action::IOR : cout << "OR "; break;
        case Instruction::Action::INOT : cout << "NOT "; break;
        case Instruction::Action::IRSHIFT : cout << "RSHIFT "; break;
        case Instruction::Action::ILSHIFT : cout << "LSHIFT "; break;
        case Instruction::Action::IASSIGN : cout << "ASSIGN "; break;
    }
    
    stream << out_instr.input2 << ' ';
    stream << out_instr.value << ' ';
    stream << "-> ";
    stream << out_instr.output;
    return stream;
};
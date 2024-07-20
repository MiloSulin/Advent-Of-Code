#include <iostream>
#include <unordered_map>
#include <string>
#include <exception>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include "Circuit.hpp"

using std::cout, std::string, std::vector, std::unordered_set, std::unordered_map;

int perfAnd(int in1, int in2){
    return in1 & in2;
};

int perfOr(int in1, int in2){
    return in1 | in2;
};

int perfNot(int input){
    return ~input;
};

int perfRshift(int input, int value){
    return input >> value;
};

int perfLshift(int input, int value){
    return input << value;
};

unordered_map<string, actionptr> actionFunctions{
    {"AND", &perfAnd},
    {"OR" , &perfOr},
    {"NOT", &perfNot},
    {"RSHIFT", &perfRshift},
    {"LSHIFT", &perfLshift},
};

Circuit::Circuit(vector<Instruction*> in_vector){
    for (const auto& e : in_vector){
        if(e->input1.empty() && e->input2.empty()){
            wires.insert({e->output, e->value});
            new_connections.push_back(*e);
        }
    }
};

auto predicate = [&new_connections](const Instruction& instr) -> bool {return std::find(new_connections.begin(), new_connectons.end(), instr.output) != new_connections.end();};

Circuit::updateWires(vector<Instruction*> in_vector){
    in_vector.erase(std::remove_if(in_vector.begin(), in_vector.end(), predicate), in_vector.end());
    new_connections.clear();
}

Circuit::readInstruction(vector<Instruction*> in_vector){
    for (const auto& e : in_vector){
        int output_value{0};
        if(!e->input1.empty() && wires.contains(e->input1) && e->input2.empty()){
            if(e->value != -1){
                output_value = (actionFunctions[e->Action])(e->input1, e->value);
            } else{
                output_value = (actionFunctions[e->Action])(e->input1);
            }
            new_connections.push_back(*e);
        }else if(wires.contains(e->input1) && wires.contains(e->input2)){
            output_value = (actionFunctions[e->Action])(e->input1, e->input2);
            new_connections.push_back(*e);
        }
        wires.insert({e->output, output_value});
    }
}
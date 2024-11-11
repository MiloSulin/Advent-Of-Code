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


int Circuit::performAction(Instruction* instr) {
    int return_value{};
    string def_input = (instr->input1.empty() ? instr->input2 : instr->input1);
    int in1 = wires[def_input];
    int in2{};
    if (instr->value != -1) {
        in2 = instr->value;
    } else if (!instr->input1.empty() && !instr->input2.empty()) {
        in2 = wires[instr->input2];
    }
    switch (instr->act) {
        case Instruction::Action::IAND : return_value = in1 & in2; break;
        case Instruction::Action::IOR : return_value = in1 | in2; break;
        case Instruction::Action::INOT : return_value = ~in1; break;
        case Instruction::Action::IRSHIFT : return_value = (in1 >> in2); break;
        case Instruction::Action::ILSHIFT : return_value = (in1 << in2); break;
        case Instruction::Action::IASSIGN : return_value = in1; break;
        default: cout << "This shouldn't happen!\n"; cout << *instr << "\n"; break;
    }
    return return_value;
}

Circuit::Circuit(vector<Instruction*> &in_vector){
    for (const auto& e : in_vector){ // initialises the circuit by adding the first wires
        if(e->input1.empty() && e->input2.empty()){
            wires.insert({e->output, e->value});
            new_connections.push_back(e);
            sorted_gates.push_back(e);
        }
    }
    updateWires(&in_vector);
    // perform main loop logic until instruction list is empty
    while (!in_vector.empty()) {
        readInstruction(&in_vector);
        updateWires(&in_vector);
    }
};

void Circuit::secondLoop() {
    wires.clear();
    for (const auto& e : sorted_gates){
        int output_value{};
        if (e->output == "b"){
            wires.insert({"b", 3176});
        } else if (e->input1.empty() && e->input2.empty()){
            wires.insert({e->output, e->value});
        } else {
            output_value = performAction(e);
            wires.insert({e->output, output_value});
        }
    }
}

void Circuit::updateWires(vector<Instruction*>* in_vector){
    auto predicate = [to_remove=&new_connections](Instruction* instr) -> bool {return std::find(to_remove->begin(), to_remove->end(), instr) != to_remove->end();};
    in_vector->erase(std::remove_if(in_vector->begin(), in_vector->end(), predicate), in_vector->end());
    new_connections.clear();
}

void Circuit::readInstruction(vector<Instruction*>* in_vector){
    for (const auto& e : *in_vector){
        int output_value{0};
        if ( (wires.contains(e->input1) && e->input2.empty()) || 
            (wires.contains(e->input2) && e->input1.empty()) ||
            (wires.contains(e->input1) && wires.contains(e->input2)) ) {
            output_value = performAction(e);
            new_connections.push_back(e);
            sorted_gates.push_back(e);
            wires.insert({e->output, output_value});
        } 
    }
}

int Circuit::returnWire(string query) {
    return wires[query];
}
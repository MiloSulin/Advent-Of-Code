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


Circuit::Circuit(vector<Instruction*> in_vector){
    for (const auto& e : in_vector){
        if(e->input1.empty() && e->input2.empty()){
            wires.insert({e->output, e->value});
        }
    }
    for (const auto& [key, value] : wires){
        cout << key << ' ' << value << '\n';
    }
};
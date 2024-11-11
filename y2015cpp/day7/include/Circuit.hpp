#include <iostream>
#include <unordered_map>
#include <string>
#include <exception>
#include <vector>
#include <cmath>
#include <unordered_set>
#include "Instruction.hpp"

using std::cout, std::string, std::vector, std::unordered_set, std::unordered_map;
using actionptr = int (*)();


class Circuit{
    public: Circuit(vector<Instruction*>&); // initialises the circuit
    void readInstruction(vector<Instruction*>*);
    void updateWires(vector<Instruction*>*);
    void secondLoop();
    int returnWire(string); // returns the value of the wire given as argument
    int performAction(Instruction*);
    private:
        unordered_map<string, int> wires;
        vector<Instruction*> new_connections;
        vector<Instruction*> sorted_gates;
};
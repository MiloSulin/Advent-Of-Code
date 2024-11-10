#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_set>

using std::cout, std::unordered_map, std::string, std::vector, std::unordered_set;


struct Instruction{
    Instruction(vector<string>);
    string input1{};
    string input2{};
    enum struct Action {
        IAND,
        IOR,
        INOT,
        IRSHIFT,
        ILSHIFT,
        IASSIGN
    };
    Action act;
    int value{-1};
    string output;
};
std::ostream &operator<<(std::ostream&, const Instruction&);
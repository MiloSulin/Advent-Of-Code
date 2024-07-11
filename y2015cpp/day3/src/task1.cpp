#include <unordered_map>
#include <unordered_set>
#include "task1.hpp"
using namespace std;
using dir_func = void (*)();

// indexes for row and column
int row = 0;
int col = 0;

int shouses = 1; // total houses visited at least once by santa

class Moves{
    public:
        static void moveUp(){
            row++;
        }
        static void moveDown(){
            row--;
        }
        static void moveLeft(){
            col--;
        }
        static void moveRight(){
            col++;
        }
};

unordered_map<char, dir_func> directions{
    {'^', &Moves::moveUp},
    {'v', &Moves::moveDown},
    {'<', &Moves::moveLeft},
    {'>', &Moves::moveRight}
};

int perfTaskOne(char* instructions, size_t size){
    unordered_map<int, unordered_set<int>>* rows = new unordered_map<int, unordered_set<int>>{}; // container for data on rows

    unordered_set<int> first_row = {0}; // add first point (house) that is visited
    (*rows).emplace(row, first_row);

    for (int i=0; i<size; ++i){
        (directions[instructions[i]])(); // execute move
        if(!(*rows).contains(row)){ // if row hasn't yet been visited, create set for row and add point
            unordered_set<int> new_row = {col};
            (*rows).insert({row, new_row});
            shouses++;
        }else { // if row already exists add point to set
            if((*rows)[row].insert(col).second)
                shouses++;
        }
    }

    return shouses;
}
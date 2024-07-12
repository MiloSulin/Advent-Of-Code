#include <unordered_map>
#include <unordered_set>
#include "task2.hpp"
using namespace std;
using dir_func = void (*)();

// indexes for row and column
int santa_row = 0;
int santa_col = 0;

int robo_row = 0;
int robo_col = 0;


class SantaMoves{
    public:
        static void moveUp(){
            santa_row++;
        }
        static void moveDown(){
            santa_row--;
        }
        static void moveLeft(){
            santa_col--;
        }
        static void moveRight(){
            santa_col++;
        }
};

unordered_map<char, dir_func> santa_directions{
    {'^', &SantaMoves::moveUp},
    {'v', &SantaMoves::moveDown},
    {'<', &SantaMoves::moveLeft},
    {'>', &SantaMoves::moveRight}
};

class RoboMoves{
    public:
        static void moveUp(){
            robo_row++;
        }
        static void moveDown(){
            robo_row--;
        }
        static void moveLeft(){
            robo_col--;
        }
        static void moveRight(){
            robo_col++;
        }
};

unordered_map<char, dir_func> robo_directions{
    {'^', &RoboMoves::moveUp},
    {'v', &RoboMoves::moveDown},
    {'<', &RoboMoves::moveLeft},
    {'>', &RoboMoves::moveRight}
};


void perfTaskTwo(char* instructions, size_t size, int* srhouses){
    unordered_map<int, unordered_set<int>>* rows = new unordered_map<int, unordered_set<int>>{}; // container for data on rows

    unordered_set<int> first_row = {0}; // add first point (house) that is visited
    (*rows).emplace(santa_row, first_row);

    for (int i=1; i<size+1; ++i){
        if (i % 2 != 0){
            (santa_directions[instructions[i-1]])(); // execute move
            if(!(*rows).contains(santa_row)){ // if row hasn't yet been visited, create set for row and add point
                unordered_set<int> new_row = {santa_col};
                (*rows).insert({santa_row, new_row});
                (*srhouses)++;
            }else { // if row already exists add point to set
                if((*rows)[santa_row].insert(santa_col).second)
                    (*srhouses)++;
            }
        }else {
            (robo_directions[instructions[i-1]])(); // execute move
            if(!(*rows).contains(robo_row)){ // if row hasn't yet been visited, create set for row and add point
                unordered_set<int> new_row = {robo_col};
                (*rows).insert({robo_row, new_row});
                (*srhouses)++;
            }else { // if row already exists add point to set
                if((*rows)[robo_row].insert(robo_col).second)
                    (*srhouses)++;
            }
        }
    }
}
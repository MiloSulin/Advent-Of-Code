// solution for day 3
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
using namespace std;
using dir_func = void (*)();

char input[] = "../input.txt";


// indexes for row and column
int* row = new int{};
int* col = new int{};

int* houses = new int{}; // total houses visited at least once

class Moves{
    public:
        static void moveUp(){
            (*row)++;
        }
        static void moveDown(){
            (*row)--;
        }
        static void moveLeft(){
            (*col)--;
        }
        static void moveRight(){
            (*col)++;
        }
};

unordered_map<char, dir_func> directions{
    {'^', &Moves::moveUp},
    {'v', &Moves::moveDown},
    {'<', &Moves::moveLeft},
    {'>', &Moves::moveRight}
};

int main(){
    auto start_t = chrono::high_resolution_clock::now();
    unordered_map<int, unordered_set<int>*> rows; // container for data on rows

    unordered_set<int>* first_row = new unordered_set<int>{}; // add first point (house) that is visited
    rows[0] =  first_row;
    rows[0]->insert(0);

    ifstream in_strm(input, ios::binary | ios::ate); // begin reading file
    if (!in_strm.is_open()){
        cerr << "Failed to open!" << '\n';
        return 1;
    }
    size_t size = in_strm.tellg();
    in_strm.seekg(0);
    char* instructions = new char[size];
    in_strm.read(instructions, size*sizeof(char));
    in_strm.close();

    for (int i=0; i<size; ++i){
        (directions[instructions[i]])(); // execute move
        if(!rows.contains(*row)){ // if row hasn't yet been visited, create set for row and add point
            unordered_set<int>* new_row = new unordered_set<int>{};
            new_row->insert(*col);
            rows[*row] = new_row;
        }else { // if row already exists add point to set
            rows[*row]->insert(*col);
        }
    }
    for (const auto e : rows){
        *houses += e.second->size(); // check size of row (unique points visited on that row) and add to total houses visited
    }
    auto end_t = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed_time{end_t - start_t};
    cout << "Total houses visited at least once: " << *houses << '\n';
    cout << "Time elapsed: " << elapsed_time << '\n';
    return 0;
}
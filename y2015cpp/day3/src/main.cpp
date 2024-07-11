// solution for day 3
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include "task1.hpp"
#include "task2.hpp"
using namespace std;
using dir_func = void (*)();

char input[] = "../input.txt";


int main(){
    auto start_t = chrono::high_resolution_clock::now();

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

    int houses1 = perfTaskOne(instructions, size);
    int houses2 = perfTaskTwo(instructions, size);

    auto end_t = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed_time{end_t - start_t};
    cout << "Total houses visited at least once during first year: " << houses1 << '\n';
    cout << "Total houses visited at least once during second year: " << houses2 << '\n';
    cout << "Time elapsed: " << elapsed_time << '\n';
    return 0;
}
// solution for day 3
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <thread>
#include "task1.hpp"
#include "task2.hpp"
using namespace std;
using dir_func = void (*)();

char input[] = "../input.txt";

int* shouses = new int{1};
int* srhouses = new int{1};

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

    jthread task1(perfTaskOne, instructions, size, shouses);
    jthread task2(perfTaskTwo, instructions, size, srhouses);

    task1.join();
    task2.join();

    auto end_t = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed_time{end_t - start_t};
    cout << "Houses visited on first year: " << *shouses << '\n';
    cout << "Houses visited on second year: " << *srhouses << '\n';
    cout << "Time elapsed: " << elapsed_time << '\n';
    return 0;
}
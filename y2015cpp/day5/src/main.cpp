/* 
RULES:
1. Must contain three vowels
2. Must contain one instance of a letter appearing twice in a row: "aa", "dd", "gg" etc.
3. Cannot contain "ab", "cd", "pq", "xy" even if they are part of the other requirements

Task 1: How many strings (lines) fulfill these requirements?
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <valarray>
#include <vector>
#include <array>
#include <chrono>
#include <thread>
using namespace std::chrono;
using std::cout, std::valarray, std::array, std::ifstream, std::stringstream, std::string, std::vector;

vector<valarray<char>> readInput(const string& filepath){
    ifstream reader(filepath); // read file into fstream
    
    vector<valarray<char>> input;

    char temp[32]; // char array for line hoping that it's smaller than 32 chars
    int line_length{};

    while(reader.getline(&temp[0], 32)){ // read line
        if (line_length == 0){
            line_length = reader.gcount(); // record how many chars were read and assume all lines are the same
        }
        
        valarray<char> line(line_length); // init valarray for line, should be faster to compare to rules using bitwise operators
        for (int i=0; i<line_length; ++i){ // from char array to valarray
            line[i] = temp[i];
        }
        input.push_back(line); // insert read line into input vector
    }
    return input;
}

int perfTaskOne(vector<valarray<char>>){
    int nice{}; // amount of nice strings
    return 1;
}


int main(){
    const auto start_t = high_resolution_clock::now();
    // read input
    auto input = readInput("../input.txt");
    const auto end_t = high_resolution_clock::now();

    for (const auto& e : input[0]){
        cout << e;
    }
    cout << '\n';

    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Time taken: " << elapsed_time << '\n';
    return 0;
}
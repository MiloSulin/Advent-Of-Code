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

    while(reader.getline(&temp[0], 32)){ // read line
        int amount_extracted = reader.gcount(); // record how many chars were read
        valarray<char> line(amount_extracted); // init valarray for line, should be faster to compare to rules using bitwise operators
        int over_four = amount_extracted % 4;
        int i=0;
        for (; i<amount_extracted-over_four; i+=4){ // from char array to valarray
            line[i] = temp[i];
            line[i+1] = temp[i+1];
            line[i+2] = temp[i+2];
            line[i+3] = temp[i+3];
        }
        for (; i<amount_extracted; ++i){ // insert leftovers too
            line[i] = temp[i];
        }
        input.push_back(line); // insert read line into input vector
    }
    return input;
}


int main(){
    const auto start_t = high_resolution_clock::now();
    // read input
    auto input = readInput("../input.txt");

    const auto cpu_count = std::thread::hardware_concurrency();
    cout << cpu_count << '\n';
    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Time taken: " << elapsed_time << '\n';
    return 0;
}
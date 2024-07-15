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

const string forbid1 = "ab";
const string forbid2 = "cd";
const string forbid3 = "pq";
const string forbid4 = "xy";

const string vowels = "aeiou";
const string alphabet = "abcdefghijklmnopqrstuvwxyz";

vector<array<char, 32>> readInput(const string& filepath){
    ifstream reader(filepath); // read file into fstream
    
    vector<array<char, 32>> input;

    array<char, 32> line; // char array for line hoping that it's smaller than 32 chars

    while(reader.getline(&line[0], 32)){ // read line
        input.push_back(line); // insert read line into input vector
    }
    return input;
}


int perfTaskOne(vector<array<char, 32>>* input){
    int nice{0};
    //solve part 1
    for (auto& line : *input){
        bool double_letter{false}; // contains double letter
        bool contains_forbid{false}; // contains forbid
        int vowel_count{0}; // contains three vowels
        
        string test{""};
        char* last_seen = NULL;
        for (auto& e : line){
            if(!alphabet.contains(e)){
                break;
            }

            test += e;

            if (vowels.contains(e)){
                vowel_count++;
            }

            if(last_seen != NULL && *last_seen == e){
                double_letter = true;
            }
            last_seen = &e;
        }

        if(test.contains(forbid1) | test.contains(forbid2) | test.contains(forbid3) | test.contains(forbid4)){
            contains_forbid = true;
        }
        
        if(double_letter && vowel_count >= 3 && !contains_forbid){
            nice++;
        }
    }
    return nice;
}

/* 
RULES:
1. Must contain three vowels
2. Must contain one instance of a letter appearing twice in a row: "aa", "dd", "gg" etc.
3. Cannot contain "ab", "cd", "pq", "xy" even if they are part of the other requirements

Task 1: How many strings (lines) fulfill these requirements?
 */

int main(){
    const auto start_t = high_resolution_clock::now();
    // read input
    auto* input = new vector<array<char, 32>>{readInput("../input.txt")};
    // perform task 1
    int nice1 = perfTaskOne(input);
    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Nice strings: " << nice1 << '\n';
    cout << "Time taken: " << elapsed_time << '\n';
    return 0;
}
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

valarray<char> forbid1 = {'a', 'b'};
valarray<char> forbid2 = {'c', 'd'};
valarray<char> forbid3 = {'p', 'q'};
valarray<char> forbid4 = {'x', 'y'};

const string vowels = "aeiou";

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
    auto input = readInput("../input.txt");
    int nice{0};
    //solve part 1
    for (const auto& line : input){
        bool double_letter{false}; // contains double letter
        bool contains_forbid{false}; // contains forbid
        int vowel_count{0}; // contains three vowels
        for (int i=0; i<line.size()-1; ++i){
            // check each char pair against forbidden sequences and return min element from result
            // this will give the respective bool check value 0 if no forbidden sequence was found
            bool f1_check = (valarray<bool>(line[std::slice(i,2,1)] == forbid1)).min();
            bool f2_check = (valarray<bool>(line[std::slice(i,2,1)] == forbid2)).min();
            bool f3_check = (valarray<bool>(line[std::slice(i,2,1)] == forbid3)).min();
            bool f4_check = (valarray<bool>(line[std::slice(i,2,1)] == forbid4)).min();

            if (f1_check | f2_check | f3_check | f4_check){
                contains_forbid = true;
                break;
            }

            if(line[i] == line[i+1]){
                double_letter = true;
            }
        }
        valarray<bool> vowel_arr = (line == valarray<char>(vowels[0], line.size()));
        vowel_arr |= (line == valarray<char>(vowels[1], line.size()));
        vowel_arr |= (line == valarray<char>(vowels[2], line.size()));
        vowel_arr |= (line == valarray<char>(vowels[3], line.size()));
        vowel_arr |= (line == valarray<char>(vowels[4], line.size()));
        for (const auto& vow : valarray<bool>(vowel_arr[vowel_arr == true])){
            vowel_count++;
        }
        if(double_letter && vowel_count >= 3 && !contains_forbid){
            nice++;
        }
    }
    
    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Nice strings: " << nice << '\n';
    cout << "Time taken: " << elapsed_time << '\n';
    return 0;
}
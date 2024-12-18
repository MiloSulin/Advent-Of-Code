#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <chrono>
#include "md5.h"
using std::string, std::cout, std::array, std::stringstream, std::milli;

constexpr string key = {"yzbqklnj"};

struct Results{
    int task1;
    int task2;
};


Results searchForZeroes(){
    int task1{};
    bool solved1 = false;
    bool solved2 = false;
    int trial = 0;
    while(!solved2){
        trial++;
        stringstream buf;
        buf << key << trial;
        string input = buf.str();
        MD5* hasher = new MD5{input};
        auto output = hasher->hexdigest();
        for (int i=0; i<6; ++i){
            if(output[i] != '0')
                break;
            else if(i == 4 && !solved1){
                task1 = trial;
                solved1 = true;
            }else if(i == 5 && !solved2){
                solved2 = true;
            }
        }
        delete hasher;
    }

    return {task1, trial};
}



int main(){
    const auto start_t = std::chrono::high_resolution_clock::now();
    auto [task1, task2] = searchForZeroes();
    const auto end_t = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, milli> elapsed_time{end_t - start_t};
    cout << "Solution to task 1: " << task1 << '\n';
    cout << "Solution to task 2: " << task2 << '\n';
    cout << "Elapsed time: " << elapsed_time << std::endl;
    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <string>
#include <mutex>
#include <cmath>
using namespace std::chrono;
using std::cout, std::array, std::ifstream, std::string, std::vector;

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

struct Results{
    // struct that contains the results for both tasks
    int task1;
    int task2;
};

void taskOneRules(vector<array<char, 32>>* lines, std::atomic<int>* nice){
    int nice_own{0};
    for (auto& line : *lines){
        bool double_letter{false}; // contains double letter
        bool contains_forbid{false}; // contains forbid
        int vowel_count{0}; // contains three vowels
        
        string test{""};
        char* last_seen = nullptr; // pointer to char that preceded the current one
        for (auto& e : line){
            if(!alphabet.contains(e)){
                break;
            }

            test += e;

            if (vowels.contains(e)){
                vowel_count++;
            }

            if(last_seen != nullptr && *last_seen == e){
                double_letter = true;
            }
            last_seen = &e;
        }

        if(test.contains(forbid1) | test.contains(forbid2) | test.contains(forbid3) | test.contains(forbid4)){
            contains_forbid = true;
        }
        
        if(double_letter && vowel_count >= 3 && !contains_forbid){
            nice_own++;
        }
    }
    *nice += nice_own;
}


void taskTwoRules(vector<array<char, 32>>* lines, std::atomic<int>* nice){
    int nice_own{0};
    for (auto& line : *lines){
        bool repeat_letter{false}; // contains repeating letter
        bool repeat_pair{false}; // contains repeating pair
        
        char* one_back = nullptr; // char preceding current one
        char* two_back = nullptr; // char two places behind current one

        // string full_string{""}; // string to use for checking if string has repeating pair
        // for (auto& e : line){
        //     if(!alphabet.contains(e)){ // incoming char array has empty places, stop reading line once we run out of real symbols
        //         break;
        //     }
        //     full_string += e;
        // }

        int line_pos{0}; // index of current char
        uint64_t line_length{line.size()};
        for (auto& e : line){
            if(!alphabet.contains(e)){ // incoming char array has empty places, stop reading line once we run out of real symbols
                break;
            }

            string test{""}; // construct pair to look for in the rest of the string
            if (line_pos >= 1 && !repeat_pair){
                test += *one_back;
                test += e;
                string sub_str = string(line.begin() +line_pos+1, line.begin() +line_length);
                if ( sub_str.contains(test) ) // check if rest of string contains the current pair
                    repeat_pair = true;
            }

            if(two_back != nullptr && one_back != nullptr && *two_back == e){
                repeat_letter = true;
            }
            two_back = one_back;
            one_back = &e;

            line_pos++;
        }
        if(repeat_letter & repeat_pair){
            nice_own++;
        }
    }
    *nice += nice_own;
}

Results perfTasks(vector<array<char, 32>>* input){
    int line_count = input->size();
    std::atomic<int>* nice1 = new std::atomic<int>{0};
    std::atomic<int>* nice2 = new std::atomic<int>{0};

    int process_count = (std::thread::hardware_concurrency() / 2 +2);
    int lines_per_thread = 2* std::floor(line_count / (process_count-2));
    int left_over = line_count % lines_per_thread;
    std::jthread* thread_pool[process_count];
    int thread_count{0};
    int i{0};

    //solve tasks
    for(; i<lines_per_thread*(process_count-2) / 2; i+=lines_per_thread){
        vector<array<char, 32>>* chunk = new vector<array<char, 32>>((*input).begin() +i, (*input).begin() +i +lines_per_thread);
        thread_pool[thread_count] = new std::jthread(taskOneRules, chunk, nice1);
        thread_pool[thread_count+1] = new std::jthread(taskTwoRules, chunk, nice2);
        thread_count+=2;
    }
    vector<array<char, 32>>* last_chunk = new vector<array<char, 32>>((*input).begin() +i, (*input).begin() +line_count);
    thread_pool[process_count-2] = new std::jthread(taskOneRules, last_chunk, nice1);
    thread_pool[process_count-1] = new std::jthread(taskTwoRules, last_chunk, nice2);

    for(int j=0; j<process_count; j+=2){
        thread_pool[j]->join();
        thread_pool[j+1]->join();
    }

    return {*nice1, *nice2};
}

/* 
TASK 1 RULES:
1. Must contain three vowels
2. Must contain one instance of a letter appearing twice in a row: "aa", "dd", "gg" etc.
3. Cannot contain "ab", "cd", "pq", "xy" even if they are part of the other requirements

TASK 2 RULES:
1. Must contain the appearance of a pair of symbols twice. For example "xy" in "axycxy", cannot overlap like in "aaa" for "aa"
2. Must contain a letter that repeats with one other letter in between: "a" in "baxab"
 */

int main(){
    auto start_t = high_resolution_clock::now();
    // read input
    auto* input = new vector<array<char, 32>>{readInput("../input.txt")};
    // perform task 1 and 2
    auto [nice1, nice2] = perfTasks(input);
    auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};

    cout << "Nice strings in task 1: " << nice1 << '\n';
    cout << "Nice strings in task 2: " << nice2 << '\n';
    cout << "Time taken: " << elapsed_time << '\n';
    input->clear();
    return 0;
}
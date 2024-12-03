#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cmath>
#include <array>
#include <vector>

using namespace std::chrono;
using std::cout, std::array, std::string;

void readInput(string filepath, char* w_start){
    std::fstream reader{filepath};
    if (!reader.is_open()){
        cout << "Shit broke!\n";
    }
    reader.read(w_start, 1024*1024);
    reader.close();
}

struct LocationLists {
    std::vector<int> list1;
    std::vector<int> list2;
};

LocationLists interpretInput(array<char, 128*1024> input){
    int new_lines{0};
    char* line_finder = &input[0];
    while ( (*line_finder) != '\0'){
        if ( (*line_finder) == '\n'){
            new_lines += 1;
        }
        line_finder += 1;
    }

    std::vector<int> list1(new_lines);
    std::vector<int> list2(new_lines);
    int case_switch{0};

    char* input_ptr = &input[0];
    int index{0};
    int distance{0};
    while (*input_ptr != '\0'){
        if (*input_ptr == '\n'){
            switch (case_switch){
                case 0:
                    break;
                case 1:
                    list2[index] = distance;
                    distance = 0;
                    case_switch = 0;
                    index += 1;
                    break;
                default:
                    break;
            }
        } else if(*input_ptr == ' '){
            switch (case_switch){
                case 0:
                    list1[index] = distance;
                    distance = 0;
                    case_switch = 1;
                    break;
                case 1:
                    break;
                default:
                    break;
            }
        } else{
            int ctonumber = (*input_ptr) -'0';
            distance = distance*10 +ctonumber;
        }
        input_ptr += 1;
    }

    return LocationLists{list1, list2};
}


int main(){
    const auto start_t = high_resolution_clock::now();

    array<char, 128 * 1024> input;
    readInput("../input.txt", &input[0]);

    auto [dist1, dist2] = interpretInput(input);
    std::sort(dist1.begin(), dist1.end());
    std::sort(dist2.begin(), dist2.end());

    // Task 1
    int total_distance{0};
    // Task 2
    int total_similarity{0};
    int left_coef{0};
    int j{0};
    int current_number = dist1[0];
    for (int i=0; i < dist1.size(); i++){
        // Task 1 solution
        total_distance += std::abs(dist1[i] -dist2[i]);
        // Task 2 solution
        if (dist1[i] != current_number){
            int right_coef{0};
            while (dist2[j] <= current_number){
                if (dist2[j] == current_number){
                    right_coef += 1;
                }
                j += 1;
            }
            total_similarity += (current_number*right_coef)*left_coef;
            left_coef = 0;
            current_number = dist1[i];
        }
        left_coef += 1;
    }

    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Task 1 solution: " << total_distance << '\n';
    cout << "Task 2 solution: " << total_similarity << '\n';
    cout << "Time taken: " << elapsed_time << std::endl;
    return 0;
}
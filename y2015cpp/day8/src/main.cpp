#include <iostream>
#include <fstream>
#include <chrono>
#include <array>
#include <string>

using namespace std::chrono;
using std::cout, std::array, std::fstream, std::string;

void readInput(string filepath, char* w_start){
    fstream reader{filepath};
    if (!reader.is_open()){
        cout << "Shit broke!\n";
    }
    reader.read(w_start, 1024*1024);
    reader.close();
}

int main(){
    const auto start_t = high_resolution_clock::now();
    
    array<char, 1024*1024> input;
    readInput("../input.txt", &input[0]);
    auto in_ptr = &input[0];

    int total_str_ltr{0};
    int new_encoding{0};
    int chars_in_mem{0};

    while (*in_ptr != '\0'){
        switch (*in_ptr){
            case '\n' :
                    in_ptr++;
                    break;
            case '\\' :
                    switch (*(++in_ptr)){
                        case 'x' :
                                in_ptr += 3;
                                total_str_ltr += 4;
                                new_encoding += 5;
                                break;
                        case '\"' :
                                in_ptr++;
                                total_str_ltr += 2;
                                new_encoding += 4;
                                break;
                        case '\\' :
                                in_ptr++;
                                total_str_ltr += 2;
                                new_encoding += 4;
                                break;
                        default :
                                cout << "Shouldn't happen!\n";
                                break;
                    }
                    chars_in_mem++;
                    break;
            case ' ' :
                    in_ptr++;
                    break;
            case '\"' :
                    total_str_ltr++;
                    new_encoding += 3;
                    in_ptr++;
                    break;
            default :
                    total_str_ltr++;
                    chars_in_mem++;
                    new_encoding++;
                    in_ptr++;
                    break;
        }
    }
    cout << "Result for task 1: " << total_str_ltr - chars_in_mem << '\n';
    cout << "Result for task 2: " << new_encoding - total_str_ltr << '\n';

    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Time taken: " << elapsed_time << std::endl;
}
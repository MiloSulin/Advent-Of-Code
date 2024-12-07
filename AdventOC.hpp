#ifndef __ADVENT_OF_CODE_H__
#define __ADVENT_OF_CODE_H__

#include <iostream>
#include <fstream>
#include <format>
#include <string>
#include <vector>

namespace advoc{

    void readInput(std::string filepath, char* w_start, uint bufsize){
    std::fstream reader{filepath};
    if (!reader.is_open()){
        std::cerr << "Shit broke!\n";
    }
    reader.read(w_start, bufsize);
    reader.close();
    }


    std::vector<std::string> stringSplit(std::string str_arg, char split_by, int skip_all=1){
    /*
    Splits given string into parts based on argument and returns a vector containing the new strings.
    ARGUMENTS:
    std::string str_arg - String to be split
    char split_by - Character denoting the split point
    int skip_all - Skip all consecutive split chars as well as spaces, 1 (true) by default, if 0 (false) then only first split char is used
    RETURNS:
    std::vector<std::string> - Vector containing the new strings
        */
    std::vector<std::string> new_strings{};

    // check if skip_all argument is allowed (is 1 or 0)
    if (skip_all != 1 && skip_all != 0){
        std::cerr << "Given argument for parameter 'skip_all' was not allowed!\n";
        std::cerr << std::format("Allowed arguments are: 1 or 0. Argument was {}.\n", skip_all);
        return new_strings;
    }

    size_t original_len{str_arg.size()};
    size_t start_pos{0};
    bool new_word{true};
    for (size_t i=0; i<original_len; i++){
        // When encountering a split char or end of the string add new split string to return container
        if ( (str_arg.at(i) == split_by) && (i != start_pos) ){
            new_strings.push_back(str_arg.substr(start_pos, i - start_pos));
            new_word = false;
            continue;
        } else if ( (str_arg.at(i) == '\0') && (new_word == true) ){
            new_strings.push_back(str_arg.substr(start_pos, i - start_pos));
            new_word = false;
            continue;
        } else if ( (i == original_len-1) && (new_word == true) ){
            new_strings.push_back(str_arg.substr(start_pos));
            new_word = false;
            continue;
        } else if ( (i == original_len-1) && (str_arg.at(i) != split_by && str_arg.at(i) != '\0') ){
            new_strings.push_back(str_arg.substr(i));
            continue;
        }

        // Check if skipping all split symbols and spaces. If so, keep going until new word starts
        if ( (new_word == false) && (str_arg.at(i) == split_by || str_arg.at(i) == ' ') ){
            switch (skip_all){
                case 1:
                    continue;
                    break;
                case 0:
                    new_word = true;
                    start_pos = i;
                    break;
                default:
                    // shouldn't happen
                    break;
            }
        } else if ( (new_word == false) && (str_arg.at(i) != split_by || str_arg.at(i) != ' ') && (str_arg.at(i) != '\0')){
            new_word = true;
            start_pos = i; // set starting pos for new string
        }
    }

    return new_strings;
    }
}

#endif
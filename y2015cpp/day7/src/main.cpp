#include <iostream>
#include <unordered_map>
#include <fstream>
#include <array>
#include <string>
#include <exception>

using std::cout, std::unordered_map, std::fstream, std::array, std::string;

array<char, 1024*1024> input;

void readInput(string filepath){
    fstream reader{filepath};
    if(!reader.is_open()){
        throw std::runtime_error("Something wen't wrong when opening input file!") ;
    }
    reader.read(&input[0], 1024*1024);
    reader.close();
}


int main(){
    readInput("../input.txt");
    for (int i=0; i<100; ++i){
        cout << input[i];
    }
    cout << '\n';
    return 0;
}
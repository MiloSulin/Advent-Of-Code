#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <chrono>
#include <array>
#include <cmath>

using namespace std::chrono;
using std::cout, std::fstream, std::unordered_set, std::string, std::array;

/* 
Task 1: Find the shortest path that visits each location once.
As the input includes distances for all pairings of locations the data represents a fully connected, undirected, weighted graph.
Each vertex is a location and each edge is weighted by the distance of the vertices it connects. Task is to find the combination of edges
that connects all vertices to a chain with the least total weight.
 */

void readInput(string filepath, char* w_start){
    fstream reader{filepath};
    if (!reader.is_open()){
        cout << "Shit broke!\n";
    }
    reader.read(w_start);
    reader.close();
}

struct Edge{
    string v1;
    string v2;
    int distance;
}

void interpretInput(*char in_ptr, )

int main(){
    const auto start_t = high_resolution_clock::now();

    array<char, 1024> input;
    array<Edge, 100> graph;
    readInput("../input.txt", &input[0]);



    const auto end_t = high_resolution_clock::now();
    duration<double, std::milli> elapsed_time{end_t - start_t};
    cout << "Time taken: " << elapsed_time << std::endl;
}
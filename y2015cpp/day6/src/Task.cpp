#include <vector>
#include <algorithm>
#include <execution>
#include "Task.hpp"
#include "Instruction.hpp"

void turnOn(bool& n){
    n |= true;
}
void turnOff(bool& n){
    n &= false;
}
void toggle(bool& n){
    n ^= true;
}

void turnUp(int& n){
    n++;
}
void turnDown(int& n){
    if(n != 0) n--;
}
void turnUpTwo(int& n){
    n+=2;
}

Results performTasks(std::vector<Instruction>* input){
    int light_count{0};
    int intensity_sum{0};
    bool lights[1000*1000] = {false};
    int lights2[1000*1000] = {0};
    for (auto e : *input){
        bool* light_start = &(lights[e.start_point]);
        int* light2_start = &(lights2[e.start_point]);
        for(int i=0; i<e.y; ++i){
            if(e.action == '>'){
                std::for_each(std::execution::par_unseq, light_start, light_start + e.x, turnOn);
                std::for_each(std::execution::par_unseq, light2_start, light2_start + e.x, turnUp);
            }else if(e.action == '<'){
                std::for_each(std::execution::par_unseq, light_start, light_start + e.x, turnOff);
                std::for_each(std::execution::par_unseq, light2_start, light2_start + e.x, turnDown);
            }else if(e.action == '^'){
                std::for_each(std::execution::par_unseq, light_start, light_start + e.x, toggle);
                std::for_each(std::execution::par_unseq, light2_start, light2_start + e.x, turnUpTwo);
            }
            light_start += 1000;
            light2_start += 1000;
        }
    }
    bool* light_start{&lights[0]};
    int* light2_start{&lights2[0]};
    for(int l=0; l<1000*1000; ++l){
        if(*(light_start+l)){
            light_count++;
        }
        intensity_sum += *(light2_start +l);
    }

    return {light_count, intensity_sum};
}
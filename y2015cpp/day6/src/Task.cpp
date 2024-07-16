#include <vector>
#include "Task.hpp"
#include "Instruction.hpp"

Results performTasks(std::vector<Instruction>* input){
    int light_count{0};
    int intensity_sum{0};
    bool lights[1024*1024] = {false};
    int lights2[1024*1024] = {0};
    for (auto e : *input){
        bool* light_start = &(lights[e.start_point]);
        int* light2_start = &(lights2[e.start_point]);
        if(e.action == '>'){
            for(int i=0; i<e.y; ++i){
                for (int k=0; k<e.x; ++k){
                    ( *(light2_start +(i*1024) +k) )++;
                    *( (light_start +(i*1024) +k) ) |= true;
                }
            }
        }else if(e.action == '<'){
            for(int i=0; i<e.y; ++i){
                for (int k=0; k<e.x; ++k){
                    if(*(light2_start +(i*1024) +k) != 0) ( *(light2_start +(i*1024) +k) )--;
                    *( (light_start +(i*1024) +k) ) &= false;
                }
            }
        }else if(e.action == '^'){
            for(int i=0; i<e.y; ++i){
                for (int k=0; k<e.x; ++k){
                    ( *(light2_start +(i*1024) +k) ) += 2;
                    *( (light_start +(i*1024) +k) ) ^= true;
                }
            }
        }
    }
    bool* light_start{&lights[0]};
    int* light2_start{&lights2[0]};
    for(int l=0; l<1024*1024; ++l){
        if(*(light_start+l)){
            light_count++;
        }
        intensity_sum += *(light2_start +l);
    }

    return {light_count, intensity_sum};
}
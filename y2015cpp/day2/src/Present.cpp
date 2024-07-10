#include "Present.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

Present::Present(int l, int w, int h) : length{l}, width{w}, height{h} {
    // sides
    Present::side1 = l * w;
    Present::side2 = w * h;
    Present::side3 = l * h;
};

int Present::wrapPaperAmount(){
    int total_paper = 2*(side1 +side2 +side3);
    // add extra paper based on smallest side
    int smallest_side = min({side1, side2, side3});
    total_paper += smallest_side;
    // return result
    return total_paper;
};

int Present::ribbonAmount(){
    int total_ribbon = length * width * height;
    int half_perimeter = length + width + height -max({length, width, height}); 
    total_ribbon += 2*half_perimeter;
    // return result
    return total_ribbon;
};
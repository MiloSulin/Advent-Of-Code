#########################################################
# Build instructions for AOC day1 in C++
#########################################################

set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.5.0)
project(AOC15_d1 VERSION 0.2.0 LANGUAGES CXX)

add_executable(AOC15_d1 src/d1task1.cpp src/d1task2.cpp src/main.cpp)

target_include_directories(AOC15_d1 
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)
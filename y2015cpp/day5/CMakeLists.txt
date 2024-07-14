#########################################################
# Build instructions for AOC day2 in C++
#########################################################
set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.5.0)
project(AOC15_d5 VERSION 0.1.0 LANGUAGES CXX)

add_executable(AOC15_d5 src/main.cpp)

target_include_directories( AOC15_d5
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

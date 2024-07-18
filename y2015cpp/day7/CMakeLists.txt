#########################################################
# Build instructions for AOC day7 in C++
#########################################################

set(CMAKE_CXX_STANDARD 23)


set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

cmake_minimum_required(VERSION 3.5.0)
project(AOC15_d7 VERSION 0.1.0 LANGUAGES CXX)

add_executable(AOC15_d7 src/Instruction.cpp src/Circuit.cpp src/main.cpp)

target_include_directories( AOC15_d7
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

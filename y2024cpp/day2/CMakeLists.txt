#########################################################
# Build instructions for AOC day9 in C++
#########################################################

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

cmake_minimum_required(VERSION 3.5.0)
project(AOC15_d9 VERSION 0.1.0 LANGUAGES CXX)

add_executable(AOC15_d9 src/main.cpp)

target_include_directories( AOC15_d9
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

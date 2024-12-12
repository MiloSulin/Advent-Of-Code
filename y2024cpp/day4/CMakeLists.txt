#########################################################
# Build instructions for AOC day4 year 2024 in C++
#########################################################

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

cmake_minimum_required(VERSION 3.5.0)
project(AOC24_d4 VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories( ${PROJECT_NAME} PRIVATE
    ~/Ohjelmointi/Omat/Advent-Of-Code
    ${PROJECT_SOURCE_DIR}/include
)
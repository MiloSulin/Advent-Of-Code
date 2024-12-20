#########################################################
# Build instructions for AOC day4 year 2024 in C++
#########################################################

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.5.0)
project(AOC24_d4 VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories( ${PROJECT_NAME} PRIVATE
    ~/Ohjelmointi/Omat/Advent-Of-Code
    ${PROJECT_SOURCE_DIR}/include
)

file(CREATE_LINK
  "${CMAKE_BINARY_DIR}/compile_commands.json"
  "${CMAKE_SOURCE_DIR}/compile_commands.json"
  SYMBOLIC
)

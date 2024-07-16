#########################################################
# Build instructions for AOC day2 in C++
#########################################################

set(CMAKE_CXX_STANDARD 23)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

cmake_minimum_required(VERSION 3.5.0)
project(AOC15_d2 VERSION 0.1.0 LANGUAGES CXX)

add_executable(AOC15_d2 src/Present.cpp src/main.cpp)

target_include_directories( AOC15_d2 
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)
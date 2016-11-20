cmake_minimum_required(VERSION 3.6)
project(Algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES longest_common_subsequence_v3.cpp)
add_executable(Algorithms ${SOURCE_FILES})
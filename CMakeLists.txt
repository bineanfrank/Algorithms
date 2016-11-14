cmake_minimum_required(VERSION 3.6)
project(Algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES closest_point_pair_2d.cpp)
add_executable(Algorithms ${SOURCE_FILES})
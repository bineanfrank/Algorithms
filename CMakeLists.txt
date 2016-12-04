cmake_minimum_required(VERSION 3.6)
project(Algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES max_m_sub_sum.cpp)
add_executable(Algorithms ${SOURCE_FILES})
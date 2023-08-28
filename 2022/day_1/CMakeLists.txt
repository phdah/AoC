cmake_minimum_required(VERSION 3.10)

project(CalorieCounting)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

add_executable(main_cpp calorie_counting.cpp)

cmake_minimum_required(VERSION 3.10)

project(RockPaperScissor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Release does optimization, i.e, sets -O2
#set(CMAKE_BUILD_TYPE Release)
# Debug allows for debugging, i.e., sets -g
set(CMAKE_BUILD_TYPE Debug)

add_executable(main_cpp rock_paper_scissors.cpp game.cpp)

cmake_minimum_required(VERSION 3.9)
project(TuringMachine__)

set(CMAKE_CXX_STANDARD 11)

add_executable(TuringMachine__ main.cpp main.h Command.h Input.cpp Parser.cpp Process.cpp Output.cpp Utility.cpp)
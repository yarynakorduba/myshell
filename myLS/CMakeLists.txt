cmake_minimum_required(VERSION 3.6)
project(myLS)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ../sh_tools.cpp ../sh_tools.h)
add_executable(myLS ${SOURCE_FILES})
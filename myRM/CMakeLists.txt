cmake_minimum_required(VERSION 3.6)
project(mrm)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(mrm ${SOURCE_FILES})

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND cp ${PROJECT_NAME} .. 
) 
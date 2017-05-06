cmake_minimum_required(VERSION 3.6)
project(mcp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(mcp ${SOURCE_FILES})

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND cp ${PROJECT_NAME} .. 
)
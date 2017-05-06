cmake_minimum_required(VERSION 3.6)
project(mls)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ../sh_tools.cpp ../sh_tools.h)
add_executable(mls ${SOURCE_FILES})

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND cp ${PROJECT_NAME} .. 
) 

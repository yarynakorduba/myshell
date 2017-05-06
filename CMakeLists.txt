cmake_minimum_required(VERSION 3.6)
project(myShell)

set(CMAKE_CXX_STANDARD 11)

include_directories(".")

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCE_FILES sh_main.cpp sh_tools.cpp sh_tools.h )
add_executable(myShell ${SOURCE_FILES})

# УВАГА
# Раз вже це один проект -- додаємо до одного проекту субдиректорії.
add_subdirectory( myCP )
add_subdirectory( myLS )
add_subdirectory( myRM )
add_subdirectory( myMV )
add_subdirectory( mymkdir )

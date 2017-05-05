cmake_minimum_required(VERSION 3.6)
project(myRV)

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
set(Boost_INCLUDE_DIR /usr/local/include)
set(Boost_LIBRARY_DIR /usr/local/include/boost)
set(Boost_LIBRARIES boost_filesystem boost_system)
#find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(myRV main.cpp)
target_link_libraries(myRV ${Boost_LIBRARIES} )
cmake_minimum_required(VERSION 3.6)
project(mrv)

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)

# УВАГА: Так робити -- халтура! Слід користуватися 
# find_package, передаючи йому підказки з командного рядка,
# якщо шлях нестандартний. Наприклад, в мене буст НЕ ТАМ живе.
# Але залишаю як є поки.
set(Boost_INCLUDE_DIR /usr/local/include)
set(Boost_LIBRARY_DIR /usr/local/include/boost)
set(Boost_LIBRARIES boost_filesystem boost_system)
#find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(mrv main.cpp  ../sh_tools.cpp ../sh_tools.h)
target_link_libraries(mrv ${Boost_LIBRARIES} )

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND cp ${PROJECT_NAME} .. 
) 
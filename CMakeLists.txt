cmake_minimum_required(VERSION 3.5.1)
project(nibbler-main)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES
        main.cpp
        Snake.cpp Snake.hpp
        Display.cpp Display.hpp
        NCurses.cpp NCurses.hpp)
add_executable(nibbler-main ${SOURCE_FILES})
target_link_libraries(nibbler-main ${CURSES_LIBRARIES})
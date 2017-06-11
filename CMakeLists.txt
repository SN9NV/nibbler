cmake_minimum_required(VERSION 3.7)
project(nibbler-main)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Snake.cpp Snake.hpp Display.cpp Display.hpp NCurses.cpp NCurses.hpp)
add_executable(untitled ${SOURCE_FILES})
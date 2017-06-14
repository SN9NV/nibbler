cmake_minimum_required(VERSION 3.5.1)
project(nibbler-main)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED SDL2)

include_directories(${CURSES_INCLUDE_DIR} #[[${SDL2_INCLUDE_DIRS}]])
link_directories(#[[${SDL2_LIBRARY_DIRS}]])

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES
        main.cpp
        Snake.cpp Snake.hpp
        Display.cpp Display.hpp
        NCurses.cpp NCurses.hpp
#		SDL2.cpp SDL2.hpp
)

add_executable(nibbler-main ${SOURCE_FILES})
target_link_libraries(nibbler-main ${CURSES_LIBRARIES} #[[${SDL2_LIBRARIES}]])
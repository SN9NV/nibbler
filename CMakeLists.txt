#[[cmake_minimum_required(VERSION 3.5.1)
project(nibbler-main)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED SDL2)]]

#include_directories(${CURSES_INCLUDE_DIR} #[[${SDL2_INCLUDE_DIRS}]])
#link_directories(#[[${SDL2_LIBRARY_DIRS}]])

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

#[[set(SOURCE_FILES
        main.cpp
        Snake.cpp Snake.hpp
        Display.cpp Display.hpp
        NCurses.cpp NCurses.hpp
#		SDL2.cpp SDL2.hpp
)
]]
#add_executable(nibbler-main ${SOURCE_FILES})
#target_link_libraries(nibbler-main ${CURSES_LIBRARIES} #[[${SDL2_LIBRARIES}]])
CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)
PROJECT(nibbler-main)

SET(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE(Curses REQUIRED)

FIND_PACKAGE(SDL2)
IF (NOT SDL2_FOUND)
    MESSAGE(STATUS "+++ Installing SDL2")
    IF (APPLE)
        EXECUTE_PROCESS(COMMAND brew install sdl2)
    ENDIF()
ENDIF()
MESSAGE(STATUS "+++ SDL2 READY")

INCLUDE_DIRECTORIES(${CURSES_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})
LINK_DIRECTORIES(${SDL2_LIBRARY_DIRS})

SET(NCURSES_SOURCE_FILES Display.cpp NCurses.cpp Snake.cpp)
ADD_LIBRARY(libCurses SHARED ${NCURSES_SOURCE_FILES})
SET_TARGET_PROPERTIES(libCurses PROPERTIES PREFIX "" SUFFIX ".so")
TARGET_LINK_LIBRARIES(libCurses ${CURSES_LIBRARIES})

SET(SDL2_SOURCE_FILES SDL2.cpp Display.cpp Snake.cpp)
ADD_LIBRARY(libSdl2 SHARED ${SDL2_SOURCE_FILES})
SET_TARGET_PROPERTIES(libSdl2 PROPERTIES PREFIX "" SUFFIX ".so")
TARGET_LINK_LIBRARIES(libSdl2 ${SDL2_LIBRARIES})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
SET(SOURCE_FILES main.cpp Display.cpp Snake.cpp)
ADD_EXECUTABLE(nibbler-main ${SOURCE_FILES})
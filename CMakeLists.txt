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

SET(NCURSES_SOURCE_FILES
        nibbler.cpp     nibbler.hpp
        Point.cpp       Point.hpp
        Snake.cpp       Snake.hpp
        Display.cpp     Display.hpp
        NCurses.cpp     NCurses.hpp
)
ADD_LIBRARY(libCurses SHARED ${NCURSES_SOURCE_FILES})
SET_TARGET_PROPERTIES(libCurses PROPERTIES PREFIX "" SUFFIX ".so")
TARGET_LINK_LIBRARIES(libCurses ${CURSES_LIBRARIES})

SET(NCURSES2_SOURCE_FILES
        nibbler.cpp     nibbler.hpp
        Point.cpp       Point.hpp
        Snake.cpp       Snake.hpp
        Display.cpp     Display.hpp
        NCurses2.cpp    NCurses.hpp
)
ADD_LIBRARY(libCurses2 SHARED ${NCURSES2_SOURCE_FILES})
SET_TARGET_PROPERTIES(libCurses2 PROPERTIES PREFIX "" SUFFIX ".so")
TARGET_LINK_LIBRARIES(libCurses2 ${CURSES_LIBRARIES})

SET(SDL2_SOURCE_FILES
		nibbler.cpp		nibbler.hpp
		Point.cpp		Point.hpp
		Snake.cpp		Snake.hpp
		Display.cpp		Display.hpp
		SDL2.cpp		SDL2.hpp
)
ADD_LIBRARY(libSdl2 SHARED ${SDL2_SOURCE_FILES})
SET_TARGET_PROPERTIES(libSdl2 PROPERTIES PREFIX "" SUFFIX ".so")
TARGET_LINK_LIBRARIES(libSdl2 ${SDL2_LIBRARIES})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
SET(SOURCE_FILES
		main.cpp
		nibbler.cpp		nibbler.hpp
		Display.cpp		Display.hpp
		Point.cpp		Point.hpp
		Snake.cpp		Snake.hpp
)
ADD_EXECUTABLE(nibbler-main ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(nibbler-main ${CURSES_LIBRARIES})
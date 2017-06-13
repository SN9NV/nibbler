cmake_minimum_required(VERSION 3.5.1)
project(nibbler-main)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)


if(UNIX)
	if (APPLE)
		set(SDL2_INCLUDES $ENV{HOME}/.brew/include/SDL2)
		set(SDL2_LIBRARIES -L/$ENV{HOME}/.brew/lib -lSDL2)
	else()
	endif()
endif()

include_directories(${CURSES_INCLUDE_DIR} ${SDL2_INCLUDES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL2_INCLUDES} -Wall -Wextra -Werror -D_THREAD_SAFE")

set(SOURCE_FILES
        main.cpp
        Snake.cpp Snake.hpp
        Display.cpp Display.hpp
        #NCurses.cpp NCurses.hpp
		SDL2.cpp SDL2.hpp
)
add_executable(nibbler-main ${SOURCE_FILES})
target_link_libraries(nibbler-main ${CURSES_LIBRARIES} ${SDL2_LIBRARIES})
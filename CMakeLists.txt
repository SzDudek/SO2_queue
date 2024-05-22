cmake_minimum_required(VERSION 3.22)
project(SO2_queue)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(SO2_queue main.cpp
        Structures/Coordinates.cpp
        Structures/Coordinates.h
        Structures/Station.h
        Structures/Client.cpp
        Structures/Client.h
        Structures/Station.cpp
)

target_link_libraries(SO2_queue ${CURSES_LIBRARIES})
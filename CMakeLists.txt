cmake_minimum_required(VERSION 3.18)

project(Stalker_Roguelike)

set(CMAKE_CURRENT_SOURCE_DIR source/)

set(SOURCES sources/main.cpp
            sources/level.cpp
            sources/figth.cpp
            sources/trade.cpp
            sources/dialog.cpp)

set(HEADERS sources/level.h
            sources/figth.h
            sources/trade.h
            sources/dialog.h)

add_executable(roguelike ${SOURCES} ${HEADERS})
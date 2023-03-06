cmake_minimum_required(VERSION 3.18)

project(Stalker_Roguelike)

set(CMAKE_CURRENT_SOURCE_DIR source/)

set(SOURCES sources/draw.cpp
            sources/figth.cpp
            sources/trade.cpp)

set(HEADERS sources/draw.h
            sources/figth.h
            sources/trade.h)

add_executable(stalker ${SOURCES} ${HEADERS})
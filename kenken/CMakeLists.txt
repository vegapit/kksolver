cmake_minimum_required(VERSION 3.10)

project(kenken)

add_library(
    kenken
    STATIC
    block.cpp
    kenken.cpp
)

target_include_directories(
    kenken
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
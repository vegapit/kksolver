cmake_minimum_required(VERSION 3.10)

project(kenken C)

add_library(
    kenken
    STATIC
    kenken.c
    vector.c
    block.c
)

target_include_directories(
    kenken
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
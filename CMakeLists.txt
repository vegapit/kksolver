cmake_minimum_required(VERSION 3.10)

project(kksolver C)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(kenken)

add_executable(
    kksolver
    main.c
)

target_link_libraries(
    kksolver
    kenken
)

target_include_directories(
    kksolver
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/kenken/include
)


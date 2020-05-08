cmake_minimum_required(VERSION 2.8.9)
project(sudoku)

include_directories(include)
link_directories(lib)
file(GLOB SOURCES src/*)

add_compile_options(-Wall -Wshadow)

add_executable(a.out main.cpp ${SOURCES})
target_link_libraries(a.out graphics SDL SDL_ttf)
cmake_minimum_required(VERSION 3.23)
project(LAB4SEM2 C)

set(CMAKE_C_STANDARD 99)

add_executable(LAB4SEM2 main.c functions.c header.h)

target_link_libraries(LAB4SEM2 winmm)
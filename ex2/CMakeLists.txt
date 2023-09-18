cmake_minimum_required(VERSION 3.22)
project(sort_lines)
set(CMAKE_C_STANDARD 11)

add_executable(sort_lines main.c sort_bus_lines.c test_bus_lines.c)

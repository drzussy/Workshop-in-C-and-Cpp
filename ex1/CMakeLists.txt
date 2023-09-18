cmake_minimum_required(VERSION 3.16)
project(EX1)
set(CMAKE_C_STANDARD 11)


add_executable(EX1test cipher.c tests.c)
add_executable(EX1 main.c cipher.c tests.c)

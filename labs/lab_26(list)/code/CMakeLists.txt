cmake_minimum_required(VERSION 3.10)
project(code C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(code
        lis.c
        lis.h
        main.c)

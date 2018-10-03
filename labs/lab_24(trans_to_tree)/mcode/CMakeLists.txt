cmake_minimum_required(VERSION 3.10)
project(mcode C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(mcode
        lexer.c
        lexer.h
        main.c
        transform.c
        transform.h
        tree.c
        tree.h)

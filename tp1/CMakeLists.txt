cmake_minimum_required(VERSION 3.21)
project(tp1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(avl)

add_executable(tp1
        avl/avl.c
        avl/avl.h
        avl/test_avl.c
        abr.c
        abr.h
        file.c
        file.h
        pile.c
        pile.h
        test_abr.c
        test_file.c)

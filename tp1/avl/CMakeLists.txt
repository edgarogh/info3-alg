cmake_minimum_required(VERSION 3.21)
project(avl C)

set(CMAKE_C_STANDARD 99)

add_executable(avl avl.c avl.h)

add_executable(test_avl test_avl.c avl.c)

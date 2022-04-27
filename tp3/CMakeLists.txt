cmake_minimum_required(VERSION 3.16)
project(info3-alg-tp3)

add_executable(test_graphe test_graphe.c graphe.c io_graphe.c)

add_executable(tests_tp3 tests.cc graphe.c io_graphe.c)
target_link_libraries(tests_tp3 gtest gtest_main pthread)

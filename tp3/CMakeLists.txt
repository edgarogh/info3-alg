add_executable(test_graphe test_graphe.c graphe.c io_graphe.c)

add_executable(tests_tp3 tests.cc graphe.c io_graphe.c)
target_link_libraries(tests_tp3 gtest gtest_main pthread)
coverage(tests_tp3)

add_executable(test_abr test_abr.c file.c pile.c abr.c)

add_executable(test_avl test_avl.c avl.c avl.h)

add_executable(tests_tp1 tests.cc file.c pile.c abr.c)
target_link_libraries(tests_tp1 gtest gtest_main pthread)
coverage(tests_tp1)

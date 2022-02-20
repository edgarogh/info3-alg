add_executable(test_abr test_abr.c file.c pile.c abr.c)

add_executable(tests tests.cc file.c pile.c abr.c)
target_link_libraries(tests gtest gtest_main pthread)

add_executable(a234 a234_main.c a234.c lire_affichage.c ajout_cle.c)

add_executable(arbre2dot arbre2dot.c a234.c lire_affichage.c ajout_cle.c)

add_executable(tests_tp2 tests.cc a234.c lire_affichage.c ajout_cle.c)
target_link_libraries(tests_tp2 gtest gtest_main pthread)
coverage(tests_tp2)

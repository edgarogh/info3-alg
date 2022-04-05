#include <gtest/gtest.h>
extern "C" {
#include "a234.h"
}

#define load_arbre(name)                                                         \
    Arbre234 name() { return lire_arbre((char*)"data/" #name); }

load_arbre(arbre1) load_arbre(arbre3)

TEST(a234, affichage_cles_tries_nr) {
    Arbre234 a = arbre3();
    testing::internal::CaptureStdout();
    Affichage_Cles_Triees_NonRecursive(a);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "30;50;80;");
}
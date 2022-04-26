#include <gtest/gtest.h>
extern "C" {
#include "a234.h"
}

#define load_arbre(name)                                                       \
    Arbre234 name() { return lire_arbre((char *)"data/" #name); }

load_arbre(arbre1) load_arbre(arbre3) load_arbre(arbre16)

    TEST(a234, cle_min) {
    EXPECT_EQ(CleMin(arbre1()), 50);
    EXPECT_EQ(CleMin(arbre3()), 30);
    EXPECT_EQ(CleMin(arbre16()), 10);
}

TEST(a234, cle_max) {
    EXPECT_EQ(CleMax(arbre1()), 50);
    EXPECT_EQ(CleMax(arbre3()), 80);
    EXPECT_EQ(CleMax(arbre16()), 375);
}

TEST(a234, analyse) {
    Arbre234 a = arbre16();
    int f = 0, n2 = 0, n3 = 0, n4 = 0;
    AnalyseStructureArbre(a, &f, &n2, &n3, &n4);
    EXPECT_EQ(f, 20);
    EXPECT_EQ(n2, 2);
    EXPECT_EQ(n3, 1);
    EXPECT_EQ(n4, 5);
}

TEST(a234, affichage_cles_tries_r) {
    Arbre234 a = arbre3();
    testing::internal::CaptureStdout();
    Affichage_Cles_Triees_Recursive(a);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "30;50;80;");
}

TEST(a234, affichage_cles_tries_nr) {
    Arbre234 a = arbre3();
    testing::internal::CaptureStdout();
    Affichage_Cles_Triees_NonRecursive(a);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "30;50;80;\n");
}
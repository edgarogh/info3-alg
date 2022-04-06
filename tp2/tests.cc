#include <gtest/gtest.h>
extern "C" {
#include "a234.h"
}

#define load_arbre(name)                                                       \
    Arbre234 name() { return lire_arbre((char *)"data/" #name); }

load_arbre(arbre1) load_arbre(arbre3) load_arbre(arbre5) load_arbre(arbre16)

    TEST(a234, NombreCles) {
    EXPECT_EQ(NombreCles(nullptr), 0);
    EXPECT_EQ(NombreCles(arbre1()), 1);
    EXPECT_EQ(NombreCles(arbre3()), 3);
    EXPECT_EQ(NombreCles(arbre16()), 19);
}

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

TEST(a234, RechercherCle) {
    Arbre234 a1 = arbre1();
    Arbre234 a3 = arbre3();
    Arbre234 a16 = arbre16();

    EXPECT_EQ(RechercherCle(nullptr, 0), nullptr);

    EXPECT_EQ(RechercherCle(a1, 50), a1);
    EXPECT_EQ(RechercherCle(a1, 0), nullptr);

    EXPECT_EQ(RechercherCle(a3, 30), a3);
    EXPECT_EQ(RechercherCle(a3, 50), a3);
    EXPECT_EQ(RechercherCle(a3, 80), a3);

    EXPECT_EQ(RechercherCle(a16, 50), a16);
    EXPECT_EQ(RechercherCle(a16, 5), nullptr);
    EXPECT_NE(RechercherCle(a16, 82), nullptr);
    EXPECT_EQ(RechercherCle(a16, 83), nullptr);
    EXPECT_NE(RechercherCle(a16, 290), nullptr);
    EXPECT_EQ(RechercherCle(a16, 291), nullptr);
    EXPECT_NE(RechercherCle(a16, 350), nullptr);
    EXPECT_EQ(RechercherCle(a16, 360), nullptr);
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

TEST(a234, noeud_max) {
    EXPECT_EQ(noeud_max(nullptr), nullptr);

    Arbre234 a3 = arbre3();
    EXPECT_EQ(noeud_max(a3), a3);

    Arbre234 nMax = noeud_max(arbre16());
    int *c = nMax->cles;
    ASSERT_NE(nMax, nullptr);
    EXPECT_TRUE(c[0] == 350 && c[1] == 370 && c[2] == 375);
}

TEST(a234, Afficher_Cles_Largeur) {
    testing::internal::CaptureStdout();
    Afficher_Cles_Largeur(nullptr);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");

    testing::internal::CaptureStdout();
    Afficher_Cles_Largeur(arbre3());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "30;50;80;");

    testing::internal::CaptureStdout();
    Afficher_Cles_Largeur(arbre5());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "50;10;20;30;80;");
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

TEST(a234, Detruire_Cle) {
    FAIL(); // TODO
}

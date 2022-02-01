#include <gtest/gtest.h>
extern "C" {
    #include "abr.h"
    #include "pile.h"
    #include "file.h"
}

////////////
// pile.c //
////////////

TEST(pile, pile_vide_pile_pleine) {
    ppile_t pile = creer_pile();
    ASSERT_TRUE(pile_vide(pile));
    ASSERT_FALSE(pile_pleine(pile));

    // Remplissage
    for (size_t i = 0; i < MAX_PILE_SIZE; i++) {
        // La valeur n'importe pas
        empiler(pile, NULL);
        ASSERT_FALSE(pile_vide(pile));
    }

    ASSERT_TRUE(pile_pleine(pile));
    detruire_pile(pile);
}

TEST(pile, depiler_empiler) {
    noeud_t val = {
        .cle = 12,
    };

    ppile_t pile = creer_pile();
    ASSERT_EQ(depiler(pile), nullptr);
    ASSERT_TRUE(empiler(pile, &val));
    ASSERT_EQ(depiler(pile)->cle, val.cle);
    ASSERT_EQ(depiler(pile), nullptr);

    // Remplissage
    for (size_t i = 0; i < MAX_PILE_SIZE; i++) {
        ASSERT_TRUE(empiler(pile, nullptr));
    }
    
    ASSERT_FALSE(empiler(pile, nullptr));
    detruire_pile(pile);
}

TEST(pile, imprimer_pile) {
    noeud_t n1 = { .cle = 1 };
    noeud_t n2 = { .cle = 2 };

    ppile_t pile = creer_pile();
    empiler(pile, &n1);
    empiler(pile, &n1);
    empiler(pile, &n2);
    testing::internal::CaptureStdout();
    imprimer_pile(pile);
    ASSERT_EQ(testing::internal::GetCapturedStdout(), "2,1,1");
    detruire_pile(pile);
}

////////////
// file.c //
////////////

TEST(file, file_vide_file_pleine) {
    pfile_t file = creer_file();
    FAIL(); // TODO
    detruire_file(file);
}

TEST(file, defiler_enfiler) {
    pfile_t file = creer_file();
    FAIL(); // TODO
    detruire_file(file);
}

///////////
// abr.c //
///////////

// Cette macro défini une fonction pour charger le fichier passé en argument
#define load_abr(name) Arbre_t name() { return lire_arbre((char*) #name); }

load_abr(arbre1)
load_abr(arbre2)
load_abr(arbre3)
load_abr(arbre4)

TEST(abr, hauteur_arbre_r) {
    EXPECT_EQ(hauteur_arbre_r(arbre1()), 4);
    EXPECT_EQ(hauteur_arbre_r(arbre2()), 4);
    EXPECT_EQ(hauteur_arbre_r(arbre3()), 2);
    EXPECT_EQ(hauteur_arbre_r(arbre4()), 6);
}

TEST(abr, hauteur_arbre_nr) {
    EXPECT_EQ(hauteur_arbre_nr(arbre1()), 4);
    EXPECT_EQ(hauteur_arbre_nr(arbre2()), 4);
    EXPECT_EQ(hauteur_arbre_nr(arbre3()), 2);
    EXPECT_EQ(hauteur_arbre_nr(arbre4()), 6);
}

TEST(abr, parcourir_arbre_largeur) {
    FAIL(); // TODO
    testing::internal::CaptureStdout();
    parcourir_arbre_largeur(arbre1());
    ASSERT_EQ(testing::internal::GetCapturedStdout(), "4,2,6,1,3,5,8,10,9,15");
}

TEST(abr, afficher_nombre_noeuds_par_niveau) {
    FAIL(); // TODO
}

TEST(abr, nombre_cles_arbre_r) {
    EXPECT_EQ(nombre_cles_arbre_r(arbre1()), 10);
    EXPECT_EQ(nombre_cles_arbre_r(arbre2()), 8);
    EXPECT_EQ(nombre_cles_arbre_r(arbre3()), 7);
    EXPECT_EQ(nombre_cles_arbre_r(arbre4()), 9);
}

TEST(abr, trouver_cle_min) {
    EXPECT_EQ(trouver_cle_min(arbre1()), 1);
    EXPECT_EQ(trouver_cle_min(arbre2()), 2);
    EXPECT_EQ(trouver_cle_min(arbre3()), 2);
    EXPECT_EQ(trouver_cle_min(arbre4()), 1);

    ASSERT_EXIT(trouver_cle_min(NULL), testing::ExitedWithCode(1), "Panic:");
}

TEST(abr, imprimer_liste_cle_triee_r) {
    testing::internal::CaptureStdout();
    imprimer_liste_cle_triee_r(arbre1());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1;2;3;4;5;6;8;9;10;15;");

    testing::internal::CaptureStdout();
    imprimer_liste_cle_triee_r(arbre4());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1;3;4;5;6;7;8;9;12;");
}

TEST(abr, imprimer_liste_cle_triee_nr) {
    FAIL(); // TODO
}

TEST(abr, arbre_plein) {
    FAIL(); // TODO
}

TEST(abr, arbre_parfait) {
    FAIL(); // TODO
}

TEST(abr, rechercher_cle_sup_arbre) {
    FAIL(); // TODO
}

TEST(abr, rechercher_cle_inf_arbre) {
    FAIL(); // TODO
}

TEST(abr, detruire_cle_arbre) {
    FAIL(); // TODO
}

TEST(abr, intersection_deux_arbres) {
    FAIL(); // TODO
}

TEST(abr, union_deux_arbres) {
    FAIL(); // TODO
}

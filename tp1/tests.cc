#include <gtest/gtest.h>
extern "C" {
#include "abr.h"
#include "file.h"
#include "pile.h"
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
    noeud_t n1 = {.cle = 1};
    noeud_t n2 = {.cle = 2};

    ppile_t pile = creer_pile();
    empiler(pile, &n1);
    empiler(pile, &n1);
    empiler(pile, &n2);
    testing::internal::CaptureStdout();
    imprimer_pile(pile);
    ASSERT_EQ(testing::internal::GetCapturedStdout(), "2;1;1");
    detruire_pile(pile);
}

////////////
// file.c //
////////////

TEST(file, file_vide_file_pleine) {
    pfile_t file = creer_file();
    ASSERT_TRUE(file_vide(file));

    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pnoeud_t n = (pnoeud_t)malloc(sizeof(noeud_t));
        n->cle = i;
        enfiler(file, n);
    }

    ASSERT_TRUE(file_pleine(file));
    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pnoeud_t n = defiler(file);
        if (i < 31)
            assert(n->cle == i);
        else
            assert(n == NULL);
    }

    ASSERT_TRUE(file_vide(file));

    detruire_file(file);
}

TEST(file, defiler_enfiler) {
    pfile_t file = creer_file();

    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pnoeud_t n = (pnoeud_t)malloc(sizeof(noeud_t));
        n->cle = i;
        enfiler(file, n);
        pnoeud_t x = defiler(file);
        assert(x == n);
    }

    ASSERT_EQ(defiler(file), nullptr);

    detruire_file(file);
}

///////////
// abr.c //
///////////

// Cette macro défini une fonction pour charger le fichier passé en argument
#define load_abr(name)                                                         \
    Arbre_t name() { return lire_arbre((char *)#name); }

load_abr(arbre1) load_abr(arbre2) load_abr(arbre3) load_abr(arbre4)

TEST(abr, hauteur_arbre_r) {
    EXPECT_EQ(hauteur_arbre_r(arbre1()), 5);
    EXPECT_EQ(hauteur_arbre_r(arbre2()), 5);
    EXPECT_EQ(hauteur_arbre_r(arbre3()), 3);
    EXPECT_EQ(hauteur_arbre_r(arbre4()), 9);
}

TEST(abr, hauteur_arbre_nr) {
    EXPECT_EQ(hauteur_arbre_nr(arbre1()), 5);
    EXPECT_EQ(hauteur_arbre_nr(arbre2()), 5);
    EXPECT_EQ(hauteur_arbre_nr(arbre3()), 3);
    EXPECT_EQ(hauteur_arbre_nr(arbre4()), 9);
}

TEST(abr, parcourir_arbre_largeur) {
    testing::internal::CaptureStdout();
    parcourir_arbre_largeur(arbre1());
    ASSERT_EQ(testing::internal::GetCapturedStdout(), "4;2;6;1;3;5;8;10;9;15;");
}

TEST(abr, afficher_nombre_noeuds_par_niveau) {
    testing::internal::CaptureStdout();
    afficher_nombre_noeuds_par_niveau(arbre1());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "0:1;1:2;2:4;3:1;4:2");
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
    testing::internal::CaptureStdout();
    imprimer_liste_cle_triee_nr(arbre1());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1;2;3;4;5;6;8;9;10;15");

    testing::internal::CaptureStdout();
    imprimer_liste_cle_triee_nr(arbre4());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1;3;4;5;6;7;8;9;12");
}

TEST(abr, arbre_plein) {
    EXPECT_EQ(arbre_plein(arbre1()), true);
    EXPECT_EQ(arbre_plein(arbre2()), false);
    EXPECT_EQ(arbre_plein(arbre3()), true);
    EXPECT_EQ(arbre_plein(arbre4()), false);
}

TEST(abr, arbre_parfait) {
    EXPECT_EQ(arbre_parfait(arbre1()), false);
    EXPECT_EQ(arbre_parfait(arbre2()), false);
    EXPECT_EQ(arbre_parfait(arbre3()), true);
    EXPECT_EQ(arbre_parfait(arbre4()), false);
}

TEST(abr, rechercher_cle_sup_arbre) {
    EXPECT_EQ(rechercher_cle_sup_arbre(arbre1(), 20), nullptr);
    EXPECT_EQ(rechercher_cle_sup_arbre(arbre1(), 14)->cle, 15);
    EXPECT_EQ(rechercher_cle_sup_arbre(arbre1(), 5)->cle, 6);
    EXPECT_EQ(rechercher_cle_sup_arbre(arbre1(), 1)->cle, 2);
}

TEST(abr, rechercher_cle_inf_arbre) {
    EXPECT_EQ(rechercher_cle_inf_arbre(arbre1(), 0), nullptr);
    EXPECT_EQ(rechercher_cle_inf_arbre(arbre1(), 2)->cle, 1);
    EXPECT_EQ(rechercher_cle_inf_arbre(arbre1(), 20)->cle, 15);
}

TEST(abr, detruire_cle_arbre) {
    Arbre_t a1_sans_3 = detruire_cle_arbre(arbre1(), 3);
    EXPECT_EQ(a1_sans_3->fgauche->fdroite, nullptr);

    Arbre_t a1_sans_racine = detruire_cle_arbre(arbre1(), 4);
    EXPECT_EQ(a1_sans_racine->cle, 2);
    EXPECT_EQ(a1_sans_racine->fgauche->cle, 1);
    EXPECT_EQ(a1_sans_racine->fdroite->cle, 3);
    EXPECT_EQ(a1_sans_racine->fdroite->fgauche, nullptr);
    EXPECT_EQ(a1_sans_racine->fdroite->fdroite->cle, 6);
}

TEST(abr, intersection_deux_arbres) {
    Arbre_t inter = intersection_deux_arbres(arbre1(), arbre2());
    EXPECT_EQ(inter->cle, 2);
}

TEST(abr, union_deux_arbres) {
    FAIL(); // TODO
}

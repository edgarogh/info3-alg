#include <gtest/gtest.h>
extern "C" {
#include "file.h"
#include "graphe.h"
}

#define load_graphe(name)                                                      \
    pgraphe_t name() {                                                         \
        pgraphe_t graph;                                                       \
        lire_graphe((char *)"data/" #name, &graph);                            \
        return graph;                                                          \
    }

load_graphe(gr0);
load_graphe(gr1);
load_graphe(gr2);
load_graphe(gr3);
load_graphe(gr4);
load_graphe(gr5);
load_graphe(gr6);
load_graphe(gr_complet);
load_graphe(gr_complet_presque);
load_graphe(gr_couleurs);
load_graphe(gr_planning);
load_graphe(gr_regulier_1);
load_graphe(gr_regulier_2);
load_graphe(gr_sched1);
load_graphe(gr_sched2);

TEST(graph, afficher_graphe_largeur) {
    testing::internal::CaptureStdout();
    afficher_graphe_largeur(gr0(), 0);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "0; 5; 2; 8; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_largeur(gr1(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1; 3; 2; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_largeur(gr2(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1; 3; 2; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_largeur(gr3(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "1; 5; 4; 3; 2; 7; 6; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_largeur(gr3(), 8);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "8; 9; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_largeur(gr3(), 10);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "10; 13; 12; 11; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_largeur(gr4(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1; 6; 2; 5; 3; 4; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_largeur(gr_couleurs(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "1; 7; 6; 5; 3; 2; 12; 11; 10; 9; \n");
}

TEST(graph, afficher_graphe_profondeur) {
    testing::internal::CaptureStdout();
    afficher_graphe_profondeur(gr0(), 0);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "0; 5; 2; 8; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_profondeur(gr1(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1; 3; 2; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_profondeur(gr2(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1; 3; 2; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_profondeur(gr3(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "1; 5; 4; 3; 2; 7; 6; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_profondeur(gr3(), 8);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "8; 9; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_profondeur(gr3(), 10);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "10; 13; 12; 11; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_profondeur(gr4(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1; 6; 2; 5; 3; 4; \n");

    testing::internal::CaptureStdout();
    afficher_graphe_profondeur(gr_couleurs(), 1);
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "1; 7; 3; 12; 9; 5; 11; 10; 2; 6; \n");
}

TEST(graph, dijkstra) {
    pgraphe_t g = gr2();
    algo_dijkstra(g, 1);
    psommet_t depart = chercher_sommet(g, 1);
    psommet_t arrive = chercher_sommet(g, 2);
    psommet_t etape = chercher_sommet(g, 3);
    ASSERT_EQ(arrive->predecesseur, etape);
    ASSERT_EQ(etape->predecesseur, depart);
}

TEST(graph, degre_sortant_sommet) {
    pgraphe_t g = gr3();
    psommet_t s8 = chercher_sommet(g, 8);
    psommet_t s9 = chercher_sommet(g, 9);

    EXPECT_EQ(degre_sortant_sommet(g, s8), 1);
    EXPECT_EQ(degre_sortant_sommet(g, s9), 0);

    psommet_t s1 = chercher_sommet(g, 1);

    EXPECT_EQ(degre_sortant_sommet(g, s1), 4);
}

TEST(graph, degre_entrant_sommet) {
    pgraphe_t g = gr3();
    psommet_t s8 = chercher_sommet(g, 8);
    psommet_t s9 = chercher_sommet(g, 9);

    EXPECT_EQ(degre_entrant_sommet(g, s8), 0);
    EXPECT_EQ(degre_entrant_sommet(g, s9), 1);
}

TEST(props, independant) {}

TEST(props, complet) {
    EXPECT_TRUE(complet(gr_complet()));
    EXPECT_FALSE(complet(gr_complet_presque()));
}

TEST(props, regulier) {
    EXPECT_TRUE(regulier(gr_regulier_1()));
    EXPECT_TRUE(regulier(gr_regulier_2()));
    EXPECT_TRUE(regulier(gr_complet()));
    EXPECT_FALSE(regulier(gr_complet_presque()));
    EXPECT_FALSE(regulier(gr0()));
    EXPECT_FALSE(regulier(gr1()));
    EXPECT_FALSE(regulier(gr_planning()));
}

TEST(chemin, chemin_new) {
    pgraphe_t g1 = gr1();

    int gr1_13212_p[] = {1, 3, 2, 1, 2};
    chemin_t gr1_13212 = chemin_new(g1, 5, gr1_13212_p);

    EXPECT_EQ(gr1_13212.len, 4);
    EXPECT_EQ(gr1_13212.arcs[2]->dest, gr1_13212.start);
}

TEST(chemin, chemin_sommet) {
    pgraphe_t g1 = gr1();

    int gr1_13212_p[] = {1, 3, 2, 1, 2};
    chemin_t gr1_13212 = chemin_new(g1, 5, gr1_13212_p);

    EXPECT_EQ(chemin_sommet(gr1_13212, 0), gr1_13212.start);
    EXPECT_EQ(chemin_sommet(gr1_13212, 1), chercher_sommet(g1, 3));
    EXPECT_EQ(chemin_sommet(gr1_13212, 2), chercher_sommet(g1, 2));
    EXPECT_EQ(chemin_sommet(gr1_13212, 3), chercher_sommet(g1, 1));
    EXPECT_EQ(chemin_sommet(gr1_13212, 4), chercher_sommet(g1, 2));
}

TEST(props, elementaire) {
    pgraphe_t g1 = gr1();
    int gr1_1321_p[] = {1, 3, 2, 1};

    chemin_t gr1_1321 = chemin_new(g1, 4, gr1_1321_p);
    EXPECT_FALSE(elementaire(g1, gr1_1321));

    chemin_t gr1_132 = chemin_new(g1, 3, gr1_1321_p);
    EXPECT_TRUE(elementaire(g1, gr1_132));

    chemin_t gr1_13 = chemin_new(g1, 2, gr1_1321_p);
    EXPECT_TRUE(elementaire(g1, gr1_13));

    int gr1_3213_p[] = {3, 2, 1, 3};
    chemin_t gr1_3213 = chemin_new(g1, 4, gr1_3213_p);
    EXPECT_FALSE(elementaire(g1, gr1_3213));
}

TEST(props, simple) {}

TEST(props, eulerien) {}

TEST(props, hamiltonien) {}

TEST(props, graphe_eulerien) {
    EXPECT_TRUE(graphe_eulerien(gr1()));
    EXPECT_TRUE(graphe_eulerien(gr5()));
}

TEST(props, graphe_hamiltonien) {
    EXPECT_FALSE(graphe_hamiltonien(gr1()));
    // FIXME: EXPECT_TRUE(graphe_hamiltonien(gr5()));
    EXPECT_FALSE(graphe_hamiltonien(gr6()));
}

TEST(props, distance) { ASSERT_EQ(distance(gr2(), 1, 2), 7); }

TEST(props, excentricite) {
    pgraphe_t g5 = gr5();

    EXPECT_EQ(excentricite(g5, 3), 3);
    EXPECT_EQ(excentricite(g5, 1), 2);
}

TEST(props, diametre) {
    EXPECT_EQ(diametre(gr6()), 3);
    EXPECT_EQ(diametre(gr4()), 5);
}

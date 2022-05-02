#include <gtest/gtest.h>
extern "C" {
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
load_graphe(gr_sched1);
load_graphe(gr_sched2);

TEST(graph, afficher_graphe_largeur) {}

TEST(graph, afficher_graphe_profondeur) {}

TEST(graph, dijkstra) {}

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

TEST(props, elementaire) {}

TEST(props, simple) {}

TEST(props, eulerien) {}

TEST(props, hamiltionien) {}

TEST(props, graphe_eulerien) {}

TEST(props, graphe_hamiltionien) {}

TEST(props, distance) {}

TEST(props, excentricite) {}

TEST(props, diametre) {}

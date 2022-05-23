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
load_graphe(gr_couleurs);
load_graphe(gr_planning);
load_graphe(gr_sched1);
load_graphe(gr_sched2);

TEST(graph, afficher_graphe_largeur) {}

TEST(graph, afficher_graphe_profondeur) {}

TEST(graph, dijkstra) {
    pgraphe_t g = gr2();
    algo_dijkstra(g, 1);
    psommet_t depart = chercher_sommet(g, 1);
    psommet_t arrive = chercher_sommet(g, 2);
    psommet_t etape = chercher_sommet(g, 3);
    ASSERT_EQ(arrive->predecesseur, etape);
    ASSERT_EQ(etape->predecesseur, depart);
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

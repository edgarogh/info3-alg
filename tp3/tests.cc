#include <gtest/gtest.h>
extern "C" {
#include "graphe.h"
}

#define load_graphe(name)                                                      \
    Arbre234 name() { return lire_graphe((char *)"data/" #name); }

TEST(graph, afficher_graphe_largeur) {}

TEST(graph, afficher_graphe_profondeur) {}

TEST(graph, dijkstra) {}

TEST(props, elementaire) {}

TEST(props, simple) {}

TEST(props, eulerien) {}

TEST(props, hamiltionien) {}

TEST(props, graphe_eulerien) {}

TEST(props, graphe_hamiltionien) {}

TEST(props, distance) {}

TEST(props, excentricite) {}

TEST(props, diametre) {}

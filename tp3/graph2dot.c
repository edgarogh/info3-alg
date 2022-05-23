#include "graphe.h"
#include <stdio.h>

void print_graph(int discriminant, pgraphe_t g) {
    for (psommet_t s = g; s; s = s->sommet_suivant) {
        int label = s->label;
        printf("\"%d_%d\" [label=\"%d\"]; ", discriminant, label, label);

        for (parc_t a = s->liste_arcs; a; a = a->arc_suivant) {
            int label2 = a->dest->label;
            int weight = a->poids;
            printf("\"%d_%d\" -> \"%d_%d\" [label=\"%d\"]; ", discriminant,
                   label, discriminant, label2, weight);
        }
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "Warning: no file given\n");
    }

    printf("digraph graphes {\n  node[shape=record];\n");
    for (size_t i = 1; i < argc; i++) {
        pgraphe_t graphe;
        lire_graphe(argv[i], &graphe);

        printf("  subgraph cluster_%s { label=\"%s\"; ", argv[i], argv[i]);

        print_graph(i, graphe);
        printf("}\n");
    }
    printf("}\n");
}

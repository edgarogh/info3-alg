#include "a234.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *print_node(size_t discriminant, Arbre234 a) {
    if (!a || a->t == 0)
        return NULL;

    int *cles = a->cles;
    Arbre234 *fils = a->fils;

    char *name = malloc(64);
    sprintf(name, "\"%zu_%p\"", discriminant, a);

    switch (a->t) {
    case 2:
        printf("%s [label=\"{{%d}|{<p0>|<p1>}}\"]; ", name, cles[0]);
        break;
    case 3:
        printf("%s [label=\"{{%d|%d}|{<p0>|<p1>|<p2>}}\"]; ", name, cles[0],
               cles[1]);
        break;
    case 4:
        printf("%s [label=\"{{%d|%d|%d}|{<p0>|<p1>|<p2>|<p3>}}\"]; ", name,
               cles[0], cles[1], cles[2]);
        break;
    }

    for (int i = 0; i < a->t; i++) {
        char *child_name = print_node(discriminant, fils[i]);
        if (child_name) {
            printf("%s:p%d -> %s; ", name, i, child_name);
            free(child_name);
        }
    }

    return name;
}

int main(int argc, char **argv) {
    printf("digraph arbres {\n  node[shape=record];\n");
    for (size_t i = 1; i < argc; i++) {
        Arbre234 arbre = lire_arbre(argv[i]);

        printf("  subgraph cluster_%s { label=\"%s\"; ", argv[i], argv[i]);

        free(print_node(i, arbre));
        printf("}\n");
    }
    printf("}\n");
}

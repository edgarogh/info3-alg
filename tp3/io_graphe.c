#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

void lire_graphe(char *file_name, pgraphe_t *g) {
    psommet_t p = NULL; /* premier sommet du graphe */
    psommet_t l = NULL; /* dernier sommet du graphe */
    FILE *f;
    int nb_sommets;
    int i;
    psommet_t c;
    int origine, destination, distance;

    f = fopen(file_name, "r");
    if (f == NULL) {
        fprintf(stderr, "Le fichier %s n'existe pas\n", file_name);
        exit(-1);
    }

    fscanf(f, "%d", &nb_sommets);

    for (i = 0; i < nb_sommets; i++) {
        c = (psommet_t)malloc(sizeof(sommet_t));
        c->sommet_suivant = NULL;
        c->couleur = 0;

        if (fscanf(f, "%d", &c->label) == EOF) {
            fprintf(stderr, "erreur dans le contenu du fichier label %d\n",
                    c->label);
            exit(-1);
        }

        if (chercher_sommet(p, c->label) != NULL) {
            fprintf(stderr, "erreur label deja dans le graphe %d\n", c->label);
            exit(-1);
        }

        if (p == NULL) {
            p = c;
            l = c;
        } else {
            l->sommet_suivant = c;
            l = c;
        }
    }

    while (fscanf(f, "%d %d %d", &origine, &destination, &distance) != EOF) {
        psommet_t o, d;

        o = chercher_sommet(p, origine);
        if (o == NULL) {
            fprintf(stderr, "erreur noeud origine %d\n", origine);
            exit(-1);
        }
        d = chercher_sommet(p, destination);
        if (d == NULL) {
            fprintf(stderr, "erreur sommet destination %d\n", destination);
            exit(-1);
        }

        ajouter_arc(o, d, distance);
    }

    *g = p;
}

void ecrire_graphe(psommet_t g) {
    psommet_t p = g;
    parc_t arc;

    while (p != NULL) {
        printf("Sommet %d: ", p->label);
        arc = p->liste_arcs;
        while (arc != NULL) {
            printf(" (%d %d) ", arc->dest->label, arc->poids);
            arc = arc->arc_suivant;
        }
        printf("\n");
        p = p->sommet_suivant;
    }

    return;
}

void ecrire_graphe_colorie(psommet_t g) {
    psommet_t p = g;

    while (p != NULL) {
        printf("Sommet %d: couleur %d\n", p->label, p->couleur);
        p = p->sommet_suivant;
    }
    return;
}

static parc_t trouver_arc(psommet_t source, int dest_label) {
    for (parc_t a = source->liste_arcs; a; a = a->arc_suivant) {
        if (a->dest->label == dest_label)
            return a;
    }

    fprintf(stderr, "Arc introuvable (%d → %d)\n", source->label, dest_label);
    exit(1);
}

chemin_t chemin_new(pgraphe_t g, size_t len, const int *labels) {
    assert(len >= 2);

    psommet_t prev_vertex = chercher_sommet(g, labels[0]);

    chemin_t self = {
        .len = len - 1,
        .start = prev_vertex,
        .arcs = malloc(sizeof(parc_t) * len),
    };

    for (size_t i = 1; i < len; i++) {
        parc_t arc = trouver_arc(prev_vertex, labels[i]);
        self.arcs[i - 1] = arc;
        prev_vertex = arc->dest;
    }

    return self;
}

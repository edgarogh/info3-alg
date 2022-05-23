/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "graphe.h"

psommet_t chercher_sommet(pgraphe_t g, int label) {
    psommet_t s;

    s = g;

    while ((s != NULL) && (s->label != label)) {
        s = s->sommet_suivant;
    }
    return s;
}

parc_t existence_arc(parc_t l, psommet_t s) {
    parc_t p = l;

    while (p != NULL) {
        if (p->dest == s)
            return p;
        p = p->arc_suivant;
    }
    return p;
}

void ajouter_arc(psommet_t o, psommet_t d, int distance) {
    parc_t parc;

    parc = (parc_t)malloc(sizeof(arc_t));

    if (existence_arc(o->liste_arcs, d) != NULL) {
        fprintf(stderr, "ajout d'un arc deja existant\n");
        exit(-1);
    }

    parc->poids = distance;
    parc->dest = d;
    parc->arc_suivant = o->liste_arcs;
    o->liste_arcs = parc;
    return;
}

// ===================================================================

int nombre_sommets(pgraphe_t g) {
    psommet_t p = g;
    int nb = 0;

    while (p != NULL) {
        nb = nb + 1;
        p = p->sommet_suivant;
    }

    return nb;
}

int nombre_arcs(pgraphe_t g) {

    psommet_t p = g;
    int nb_arcs = 0;

    while (p != NULL) {
        parc_t l = p->liste_arcs;

        while (l != NULL) {
            nb_arcs = nb_arcs + 1;
            l = l->arc_suivant;
        }

        p = p->sommet_suivant;
    }
    return nb_arcs;
}

void init_couleur_sommet(pgraphe_t g) {
    psommet_t p = g;

    while (p != NULL) {
        p->couleur = 0;        // couleur indefinie
        p = p->sommet_suivant; // passer au sommet suivant dans le graphe
    }

    return;
}

int colorier_graphe(pgraphe_t g) {
    /*
      coloriage du graphe g

      datasets
      graphe data/gr_planning
      graphe data/gr_sched1
      graphe data/gr_sched2
    */

    psommet_t p = g;
    parc_t a;
    int couleur;
    int max_couleur = INT_MIN; // -INFINI

    int change;

    init_couleur_sommet(g);

    while (p != NULL) {
        couleur = 1; // 1 est la premiere couleur

        // Pour chaque sommet, on essaie de lui affecter la plus petite couleur

        // Choix de la couleur pour le sommet p

        do {
            a = p->liste_arcs;
            change = 0;

            while (a != NULL) {
                if (a->dest->couleur == couleur) {
                    couleur = couleur + 1;
                    change = 1;
                }
                a = a->arc_suivant;
            }

        } while (change == 1);

        // couleur du sommet est differente des couleurs de tous les voisins

        p->couleur = couleur;
        if (couleur > max_couleur)
            max_couleur = couleur;

        p = p->sommet_suivant;
    }

    return max_couleur;
}

void afficher_graphe_largeur(pgraphe_t g, int r) {
    if (g == NULL)
        return;

    init_couleur_sommet(g);
    g = chercher_sommet(g, r);

    pfile_t file = creer_file();
    enfiler(file, g);

    while (!file_vide(file)) {
        g = (psommet_t)defiler(file);
        g->couleur = 1;
        printf("%d; ", g->label);

        for (parc_t courant = g->liste_arcs; courant != NULL;
             courant = courant->arc_suivant) {
            if (courant->dest->couleur == 0) {
                enfiler(file, courant->dest);
                courant->dest->couleur = 1;
            }
        }
    }
    printf("\n");
}

void afficher_graphe_profondeur_sub(pgraphe_t g) {

    if (g != NULL && g->couleur == 0) {
        printf("%i; ", g->label);
        g->couleur = 1;

        for (parc_t courant = g->liste_arcs; courant != NULL;
             courant = courant->arc_suivant) {
            if (courant->dest->couleur == 0) {
                afficher_graphe_profondeur_sub(courant->dest);
            }
        }
    }
}

void afficher_graphe_profondeur(pgraphe_t g, int r) {
    if (g != NULL) {
        g = chercher_sommet(g, r);
        init_couleur_sommet(g);
        afficher_graphe_profondeur_sub(g);
        printf("\n");
    }
}

void algo_dijkstra(pgraphe_t g, int r) {
    /*
      algorithme de dijkstra
      des variables ou des chanmps doivent etre ajoutees dans les structures.
    */

    return;
}

// ======================================================================

int degre_sortant_sommet(pgraphe_t g, psommet_t s) {
    int degre = 0;
    for (parc_t a = s->liste_arcs; a; a = a->arc_suivant) {
        degre++;
    }
    return degre;
}

int degre_entrant_sommet(pgraphe_t g, psommet_t cible) {
    int degre = 0;
    for (psommet_t s = g; s; s = s->sommet_suivant) {
        for (parc_t a = s->liste_arcs; a; a = a->arc_suivant) {
            if (a->dest == cible)
                degre++;
        }
    }
    return degre;
}

int degre_maximal_graphe(pgraphe_t g) {
    /*
      Max des degres des sommets du graphe g
    */

    return 0;
}

int degre_minimal_graphe(pgraphe_t g) {
    /*
      Min des degres des sommets du graphe g
    */

    return 0;
}

int independant(pgraphe_t g) {
    /* Les aretes du graphe n'ont pas de sommet en commun */

    return 0;
}

int complet(pgraphe_t g) {
    size_t sommets = 0, arcs = 0;

    for (psommet_t s = g; s; s = s->sommet_suivant) {
        sommets++;

        for (parc_t a = s->liste_arcs; a; a = a->arc_suivant) {
            arcs++;
        }
    }

    return (sommets * sommets) == arcs;
}

int regulier(pgraphe_t g) {
    int expected;
    if (g == NULL) {
        return true;
    } else {
        expected = degre_sortant_sommet(g, g);
    }

    for (psommet_t s = g->sommet_suivant; s; s = s->sommet_suivant) {
        if (degre_sortant_sommet(g, s) != expected)
            return false;
    }

    return true;
}

psommet_t chemin_sommet(chemin_t chemin, int index) {
    return (index == 0) ? chemin.start : chemin.arcs[index - 1]->dest;
}

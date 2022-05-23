/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

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
    /*
      afficher les sommets du graphe avec un parcours en largeur
    */

    return;
}

void afficher_graphe_profondeur(pgraphe_t g, int r) {
    /*
      afficher les sommets du graphe avec un parcours en profondeur
    */

    return;
}

bool all_selected(pgraphe_t g) {
    for (; g != NULL; g = g->sommet_suivant) {
        if (!g->selected) {
            return false;
        }
    }
    return true;
}

psommet_t trouver_plus_proche(pgraphe_t g) {
    psommet_t som = g;
    int dist_min = INT_MAX;
    for (psommet_t i = g; i != NULL; i = i->sommet_suivant) {
        if (som->selected) {
            for (parc_t a = som->liste_arcs; a != NULL; a = a->arc_suivant) {
                if (!a->dest->selected && a->dest->somme_distance < dist_min) {
                    som = a->dest;
                    dist_min = a->dest->somme_distance;
                }
            }
        }
    }
    return som;
}

void algo_dijkstra(pgraphe_t g, int r) {
    pgraphe_t selected = chercher_sommet(g, r);
    selected->selected = true;
    selected->somme_distance = 0;
    for (pgraphe_t i = g; i != NULL; i = i->sommet_suivant) {
        if (i != selected) {
            i->selected = false;
            i->somme_distance = INT_MAX;
        }
    }

    while (!all_selected(g)) {
        pgraphe_t plus_proche = trouver_plus_proche(g);
        plus_proche->selected = true;
        for (parc_t a = plus_proche->liste_arcs; a != NULL;
             a = a->arc_suivant) {

            if (!a->dest->selected &&
                a->dest->somme_distance >
                    plus_proche->somme_distance + a->poids) {
                a->dest->somme_distance =
                    plus_proche->somme_distance + a->poids;
                a->dest->predecesseur = plus_proche;
            }
        }
    }
}

// ======================================================================

int degre_sortant_sommet(pgraphe_t g, psommet_t s) {
    /*
      Cette fonction retourne le nombre d'arcs sortants
      du sommet n dans le graphe g
    */

    return 0;
}

int degre_entrant_sommet(pgraphe_t g, psommet_t s) {
    /*
      Cette fonction retourne le nombre d'arcs entrants
      dans le noeud n dans le graphe g
    */

    return 0;
}

int degre_maximal_graphe(pgraphe_t g) {
    pgraphe_t graphe = g;
    int m = INT_MIN;
    for (; g != NULL; g = g->sommet_suivant) {
        int degre = degre_sortant_sommet(graphe, g);
        if (degre > m) {
            m = degre;
        }
    }
    return m;
}

int degre_minimal_graphe(pgraphe_t g) {
    pgraphe_t graphe = g;
    int m = INT_MAX;
    for (; g != NULL; g = g->sommet_suivant) {
        int degre = degre_sortant_sommet(graphe, g);
        if (degre < m) {
            m = degre;
        }
    }
    return m;
}

int independant(pgraphe_t g) {
    /* Les aretes du graphe n'ont pas de sommet en commun */

    return 0;
}

int complet(pgraphe_t g) {
    /* Toutes les paires de sommet du graphe sont jointes par un arc */

    return 0;
}

int regulier(pgraphe_t g) {
    /*
       graphe regulier: tous les sommets ont le meme degre
       g est le ponteur vers le premier sommet du graphe
       renvoie 1 si le graphe est régulier, 0 sinon
    */

    return 0;
}

/*
  placer les fonctions de l'examen 2017 juste apres
*/

int distance(pgraphe_t g, int x, int y) {
    algo_dijkstra(g, x);
    psommet_t py = chercher_sommet(g, y);
    return py->somme_distance;
}
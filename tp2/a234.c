#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int hauteur(Arbre234 a) {
    int h0, h1, h2, h3;

    if (a == NULL)
        return 0;

    if (a->t == 0)
        return 0;

    h0 = hauteur(a->fils[0]);
    h1 = hauteur(a->fils[1]);
    h2 = hauteur(a->fils[2]);
    h3 = hauteur(a->fils[3]);

    return 1 + max(max(h0, h1), max(h2, h3));
}

int NombreCles(Arbre234 a) {
    if (a == NULL)
        return 0;

    int sum = a->t - 1;

    for (size_t i = 0; i < a->t; i++) {
        sum += NombreCles(a->fils[i]);
    }

    return sum;
}

int CleMax(Arbre234 a) {
    return a == NULL || a->t == 0
               ? INT_MIN
               : max(a->cles[a->t - 2], CleMax(a->fils[a->t - 1]));
}

int CleMin(Arbre234 a) {
    return a == NULL || a->t == 0 ? INT_MAX
                                  : min(a->cles[0], CleMin(a->fils[0]));
}

Arbre234 RechercherCle(Arbre234 a, int cle) {
    /*
       rechercher si la cle a est presente dans
       l'arbre a. Si oui, retourne le noeud ou se trouve la cle.
    */

    return NULL;
}

void AnalyseStructureArbre(Arbre234 a, int *feuilles, int *noeud2, int *noeud3,
                           int *noeud4) {
    if (a == NULL) {
        *feuilles += 1;
        return;
    }
    switch (a->t) {
    case 0:
        *feuilles += 1;
        break;
    case 2:
        *noeud2 += 1;
        break;
    case 3:
        *noeud3 += 1;
        break;
    case 4:
        *noeud4 += 1;
        break;
    default:
        printf("AnalyseStructureArbre: l'arbre n'est pas un arbre 234");
        exit(1);
    }
    for (int i = 0; i < a->t; i++) {
        AnalyseStructureArbre(a->fils[i], feuilles, noeud2, noeud3, noeud4);
    }
}

Arbre234 noeud_max(Arbre234 a) {
    /*
      Retourne le noeud avec la somme maximale des cles internes
    */

    return NULL;
}

void Afficher_Cles_Largeur(Arbre234 a) {
    /*
      Afficher le cles de l'arbre a avec
      un parcours en largeur
    */

    return;
}

void Affichage_Cles_Triees_Recursive(Arbre234 a) {
    if (a == NULL || a->t == 0) {
        return;
    }
    for (int i = 0; i < a->t - 1; i++) {
        Affichage_Cles_Triees_Recursive(a->fils[i]);
        printf("%d;", a->cles[i]);
    }
    Affichage_Cles_Triees_Recursive(a->fils[a->t]);
}

typedef struct {
    Arbre234 a;
    int progress;
} ParcoursArbre;

/** Type pile et fonctions associées, pour la fonction
 *  d'affichage non récursive
 **/
typedef struct {
    int len;
    int cap;
    ParcoursArbre *array;
} pile;

pile pile_avec_capacite(int cap) {
    pile p;
    p.len = 0;
    p.cap = cap;
    p.array = malloc(sizeof(ParcoursArbre) * cap);
    return p;
}
void empiler(pile *p, Arbre234 a, int progress) {
    if (a == NULL)
        return;
    if (p->len == p->cap) {
        p->array = realloc(p->array, p->cap * 2);
        p->cap *= 2;
    }
    p->array[p->len].a = a;
    p->array[p->len].progress = progress;
    p->len += 1;
}
ParcoursArbre depiler(pile *p) {
    ParcoursArbre top = p->array[p->len - 1];
    p->len -= 1;
    return top;
}

void Affichage_Cles_Triees_NonRecursive(Arbre234 a) {
    pile p = pile_avec_capacite(NombreCles(a));
    empiler(&p, a, 0);
    while (p.len > 0) {
        ParcoursArbre pa = depiler(&p);
        if (pa.a->t != 0) {
            if (pa.progress == 0) {
                empiler(&p, pa.a->fils[0], 0);
                empiler(&p, pa.a, 1);
            } else if (pa.progress != pa.a->t) {
                empiler(&p, pa.a->fils[pa.progress], 0);
                printf("%d;", pa.a->cles[pa.progress - 1]);
                empiler(&p, pa.a, pa.progress + 1);
            }
        }
    }
    printf("\n");
}

void Detruire_Cle(Arbre234 *a, int cle) {
    /*
      retirer la cle de l'arbre a
    */

    return;
}

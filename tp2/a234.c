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
    /*
       Retourne le nombre de cles presentes dans l'arbre a
    */

    return 0;
}

int CleMax(Arbre234 a) {
    switch (a->t) {
    case 0:
        return INT_MIN;
    case 2:
        return max(a->cles[0], CleMax(a->fils[1]));
    case 3:
        return max(a->cles[1], CleMax(a->fils[2]));
    case 4:
        return max(a->cles[2], CleMax(a->fils[3]));
    default:
        printf("CleMax: l'arbre n'est pas un arbre 234");
        exit(1);
        return 0;
    }
}

int CleMin(Arbre234 a) {
    switch (a->t) {
    case 0:
        return INT_MAX;
    case 2:
        return min(a->cles[0], CleMin(a->fils[1]));
    case 3:
        return min(a->cles[1], CleMin(a->fils[2]));
    case 4:
        return min(a->cles[2], CleMin(a->fils[3]));
    default:
        printf("CleMin: l'arbre n'est pas un arbre 234");
        exit(1);
        return 0;
    }
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
        printf("CleMin: l'arbre n'est pas un arbre 234");
        exit(1);
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
    /*
       Afficher les cles en ordre croissant
       Cette fonction sera recursive
    */
}

void Affichage_Cles_Triees_NonRecursive(Arbre234 a) {
    /*
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */
}

void Detruire_Cle(Arbre234 *a, int cle) {
    /*
      retirer la cle de l'arbre a
    */

    return;
}

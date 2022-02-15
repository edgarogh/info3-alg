//
// Created by matteo on 08/02/2022.
//


#include <stdlib.h>
#include "avl.h"

#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

Arbre init_avl() {
  Arbre a = malloc(sizeof(Arbre));
  a->bal = 0;
  a->fdroite = NULL;
  a->fgauche = NULL;
  return a;
}

Arbre creer_noeud(Arbre gauche, int cle, Arbre droit) {
  Arbre a = malloc(sizeof(Arbre));
  a->bal = 0;
  a->cle = cle;
  a->fgauche = gauche;
  a->fdroite = droit;
  return a;
}

int hauteur(Arbre a) {
  if (a == NULL) return 0;
  return (1 + max(hauteur(a->fgauche), hauteur(a->fdroite)));
}

int equilibre_avl(Arbre a) {
  int hg = hauteur(a->fgauche);
  int hd = hauteur(a->fdroite);
  if (hg == 1 + hd) return 1;
  if (hd == 1 + hg) return -1;
  if (hd == hg) return 0;
  if (hd > 1 + hg) return -2;
  if (hg > 1 + hd) return 2;
  return 10; // code erreur
}

Arbre rotation_gauche(Arbre a) {
  if (a == NULL || a->fdroite == NULL || a->fgauche == NULL) return a;
  Arbre A = a;
  Arbre ad = a->fdroite;
  Arbre adg = a->fdroite->fgauche;

  A->fdroite = adg;
  ad->fgauche = A;
  if (a->fdroite->bal == 1) {
    ad->bal = 0;
    A->bal = 0;
  } else if (a->fdroite->bal == 0) {
    A->bal = 1;
    ad->bal = -1;
  }
  return ad;
}

Arbre rotation_droite(Arbre a) {
  if (a == NULL || a->fdroite == NULL || a->fgauche == NULL) return a;
  Arbre A = a;
  Arbre ag = a->fgauche;
  Arbre agd = a->fgauche->fdroite;

  A->fgauche = agd;
  ag->fdroite = A;
  if (a->fgauche->bal == -1) {
    ag->bal = 0;
    A->bal = 0;
  } else if (a->fgauche->bal == 0) {
    A->bal = -1;
    ag->bal = 1;
  }
  return ag;
}

Arbre double_rotation_gauche(Arbre a) {
  int h = equilibre_avl(a->fdroite->fgauche);
  Arbre tmp = a;
  a->fdroite->fgauche->bal = 0;
  if (h == 0) {
    a->bal = 0;
    a->fdroite->bal = 0;
  } else if (h == 1) {
    a->bal = -1;
    a->fdroite->bal = 0;
  } else if (h == 1) {
    a->bal = 0;
    a->fdroite->bal = -1;
  }
  a->fdroite = rotation_droite(a->fdroite);
  return rotation_gauche(a);
}

Arbre double_rotation_droite(Arbre a) {
  int h = equilibre_avl(a->fgauche->fdroite);
  a->fgauche->fdroite->bal = 0;
  if (h == 0) {
    a->bal = 0;
    a->fdroite->bal = 0;
  } else if (h == 1) {
    a->bal = 1;
    a->fdroite->bal = 0;
  } else if (h == 1) {
    a->bal = 0;
    a->fdroite->bal = 1;
  }
  a->fgauche = rotation_gauche(a->fgauche);
  return rotation_droite(a);
}


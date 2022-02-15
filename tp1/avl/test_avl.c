//
// Created by matteo on 10/02/2022.
//

#include "stdio.h"
#include "stdbool.h"
#include "avl.h"

bool test_init() {
  Arbre a = init_avl();
  a->cle = 1;
  return (a->cle == 1 && a->fgauche == NULL && a->fdroite == NULL && a->bal == 0);
}

bool test_equilibre() {
  Arbre a = init_avl();
  a->cle = 1;
  a->fgauche = creer_noeud(NULL, 10, NULL);
  a->fdroite = creer_noeud(creer_noeud(NULL, 100, NULL), 20, creer_noeud(NULL, 200, NULL));
  a->fdroite->fdroite->fgauche = creer_noeud(NULL, 1000, NULL);

  return (equilibre_avl(a) == -2 && equilibre_avl(a->fdroite) == -1 && equilibre_avl(a->fgauche) == 0);
}

bool test_rotation_gauche() {
  Arbre a = init_avl();
  a->cle = 1;
  a->fgauche = creer_noeud(NULL, 10, NULL);
  a->fdroite = creer_noeud(creer_noeud(NULL, 100, NULL), 20, creer_noeud(NULL, 200, NULL));

  Arbre b = rotation_gauche(a);

  return (b->cle == 20 && b->fgauche->cle == 1 && b->fdroite->cle == 200);
}

bool test_rotation_droit() {
  Arbre a = init_avl();
  a->cle = 1;
  a->fgauche = creer_noeud(creer_noeud(NULL, 100, NULL), 10, creer_noeud(NULL, 200, NULL));
  a->fdroite = creer_noeud(NULL, 20, NULL);

  Arbre b = rotation_droite(a);

  return (b->cle == 10 && b->fdroite->cle == 1 && b->fdroite->fgauche->cle == 200);
}

bool test_double_rotation_gauche() {
  Arbre a = init_avl();
  a->cle = 1;
  a->fgauche = creer_noeud(NULL, 10, NULL);
  a->fdroite = creer_noeud(NULL, 20, creer_noeud(NULL, 200, NULL));
  a->fdroite->fgauche = creer_noeud(creer_noeud(NULL, 1000, NULL), 100, creer_noeud(NULL, 2000, NULL));

  Arbre b = double_rotation_gauche(a);

  return (b->cle == 100 && b->fdroite->cle == 20 && b->fdroite->fgauche->cle == 2000);
}

bool test_double_rotation_droit() {
  Arbre a = init_avl();
  a->cle = 1;
  a->fgauche = creer_noeud(creer_noeud(NULL, 100, NULL), 10, creer_noeud(NULL, 200, NULL));
  a->fdroite = creer_noeud(NULL, 20, NULL);
  a->fgauche->fdroite = creer_noeud(creer_noeud(NULL, 1000, NULL), 200, creer_noeud(NULL, 2000, NULL));

  Arbre b = double_rotation_droite(a);

  return (b->cle == 200 && b->fdroite->cle == 1 && b->fgauche->fdroite->cle == 1000);
}

int main() {
  printf("TEST INIT_VAL :");
  if (test_init()) { printf("OK\n"); }
  else { printf("NOT OK\n"); }

  printf("TEST EQUILIBRE :");
  if (test_equilibre()) { printf("OK\n"); }
  else { printf("NOT OK\n"); }

  printf("TEST ROTATION_GAUCHE :");
  if (test_rotation_gauche()) { printf("OK\n"); }
  else { printf("NOT OK\n"); }

  printf("TEST ROTATION_DROIT :");
  if (test_rotation_droit()) { printf("OK\n"); }
  else { printf("NOT OK\n"); }

  printf("TEST DOUBLE_ROTATION_GAUCHE :");
  if (test_double_rotation_gauche()) { printf("OK\n"); }
  else { printf("NOT OK\n"); }

  printf("TEST DOUBLE_ROTATION_DROIT :");
  if (test_double_rotation_droit()) { printf("OK\n"); }
  else { printf("NOT OK\n"); }

  return 1;
}
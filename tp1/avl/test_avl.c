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

  return (equilibre_avl(a) == 2 && equilibre_avl(a->fdroite) == 1 && equilibre_avl(a->fgauche) == 0);
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

bool test_equilibrage() {
  Arbre a = creer_noeud(creer_noeud(NULL, 4, NULL), 6, creer_noeud(NULL, 7, NULL));
  a->fgauche->fgauche = creer_noeud(creer_noeud(NULL, 1, NULL), 2, creer_noeud(NULL, 3, NULL));
  a->fgauche->fdroite = creer_noeud(NULL, 5, NULL);

  a->bal = -2;
  a->fgauche->bal = -1;
  a->fdroite->bal = 0;
  a->fgauche->fgauche->bal = 0;
  a->fgauche->fgauche->fgauche->bal = 0;
  a->fgauche->fgauche->fdroite->bal = 0;
  a->fgauche->fdroite->bal = 0;

  Arbre b = equilibrer(a);
  int e = equilibre_avl(a);
  return ((e == 0 || e == -1 | e == 1) && (b->cle == 4));
}

bool test_insertion() {
  Arbre a = creer_noeud(NULL, 4, NULL);
  Tuple t = insertion(a, 3);
  t = insertion(t.a, 1);
  t = insertion(t.a, 6);
  t = insertion(t.a, 7);
  t = insertion(t.a, 5);
  t = insertion(t.a, 2);
  a = t.a;

  return (a->cle == 4 && a->fgauche->cle == 2 && a->fdroite->cle == 6
          && a->fgauche->fgauche->cle == 1 && a->fgauche->fdroite->cle == 3
          && a->fdroite->fgauche->cle == 5 && a->fdroite->fdroite->cle == 7
  );
}

bool test_suppression() {
  Arbre a = creer_noeud(NULL, 8, NULL);
  Tuple t = insertion(a, 10);
  t = insertion(t.a, 12);
  t = insertion(t.a, 13);
  t = insertion(t.a, 14);
  t = insertion(t.a, 15);
  t = insertion(t.a, 20);
  t = insertion(t.a, 16);
  t = insertion(t.a, 21);
  t = insertion(t.a, 16);
  t = insertion(t.a, 17);
  a = t.a;

  t = suppression(a, 15);
  a = t.a;
  return false;
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

  printf("TEST EQUILIBRAGE :");
  if (test_equilibrage()) { printf("OK\n"); }
  else { printf("NOT OK\n"); }

  printf("TEST INSERTION :");
  if (test_insertion()) { printf("OK\n"); }
  else { printf("NOT OK\n"); }

  printf("TEST SUPPRRESSION :");
  if (test_suppression()) { printf("OK\n"); }
  else { printf("NOT OK\n"); }

  return 1;
}
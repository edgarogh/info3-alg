//
// Created by matteo on 08/02/2022.
//


#include <stdlib.h>
#include "avl.h"

#define max2(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min2(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


#define max3(a, b, c) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b);\
     __typeof__ (c) _c = (c); \
     _a > _b ? (_a > _c ? _a : _c ) : (_b > _c ? _b : _c ); })

#define min3(a, b, c) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b);\
     __typeof__ (c) _c = (c); \
     _a < _b ? (_a < _c ? _a : _c ) : (_b < _c ? _b : _c ); })

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

Tuple creer_tuple(Arbre a, int val) {
  Tuple t;
  t.a = a;
  t.val = val;

  return t;
}

int hauteur(Arbre a) {
  if (a == NULL) return 0;
  return (1 + max2(hauteur(a->fgauche), hauteur(a->fdroite)));
}

int equilibre_avl(Arbre a) {
  int hg = hauteur(a->fgauche);
  int hd = hauteur(a->fdroite);
  if (hg == 1 + hd) return -1;
  if (hd == 1 + hg) return 1;
  if (hd == hg) return 0;
  if (hd > 1 + hg) return 2;
  if (hg > 1 + hd) return -2;
  return 10; // code erreur
}

void auto_bal(Arbre a) {
  a->bal = equilibre_avl(a);
  if (a->fdroite != NULL) {
    auto_bal(a->fdroite);
  }
  if (a->fgauche != NULL) {
    auto_bal(a->fgauche);
  }
  return;
}

Arbre rotation_gauche(Arbre root) {
  if (root == NULL) return root;
  Arbre new_root = root->fdroite;
  int root_bal = root->bal;
  int new_root_bal = new_root->bal;

  // On change les branchements
  root->fdroite = new_root->fgauche;
  new_root->fgauche = root;

  // On met à jour les balances
  root->bal = root_bal - max2(new_root_bal, 0) - 1;
  new_root->bal = min3(root_bal - 2, root_bal + new_root_bal - 2, new_root_bal - 1);
  
  return new_root;
}

Arbre rotation_droite(Arbre root) {
  if (root == NULL) return root;
  Arbre new_root = root->fgauche;
  int root_bal = root->bal;
  int new_root_bal = new_root->bal;

  // On change les branchements
  root->fgauche = new_root->fdroite;
  new_root->fdroite = root;

  // On met à jour les balances
  root->bal = root_bal - min2(new_root_bal, 0) + 1;
  new_root->bal = max3(root_bal + 2, root_bal + new_root_bal + 2, new_root_bal + 1);

  return new_root;
}

Arbre double_rotation_gauche(Arbre a) {
  a->fdroite = rotation_droite(a->fdroite);
  return rotation_gauche(a);
}

Arbre double_rotation_droite(Arbre a) {
  a->fgauche = rotation_gauche(a->fgauche);
  return rotation_droite(a);
}

Arbre equilibrer(Arbre a) {
  if (a->bal == 2) {
    if (a->fdroite->bal >= 0)
      return rotation_gauche(a);
    else {
      return double_rotation_gauche(a);
    }
  } else if (a->bal == -2) {
    if (a->fgauche->bal <= 0)
      return rotation_droite(a);
    else {
      return double_rotation_droite(a);
    }
  }
  return a;
}

Tuple insertion(Arbre A, int el) {
  int h; // si h = 0 pas besoin d'équilibre l'arbre, sinon h vaut 1
  // algorithme d'insertion abr classique
  if (A == NULL) {
    A = creer_noeud(NULL, el, NULL);
    A->bal = 0;
    return creer_tuple(A, 1);
  } else if (el == A->cle) { // deja dans l'arbre
    return creer_tuple(A, 0);
  } else if (el > A->cle) {
    Tuple t = insertion(A->fdroite, el);
    A->fdroite = t.a;
    h = t.val;
  } else {
    Tuple t = insertion(A->fgauche, el);
    A->fgauche = t.a;
    h = t.val;
    h = -h;
  }
  if (h == 0) { // inserer ne necessitera pas d'equilibre (bal A = 0, 1, -1)
    return creer_tuple(A, 0);
  } else {
    A->bal = A->bal + h; // sinon on met à jour bal avec notre variation
    A = equilibrer(A); // on équilibre l'arbre en consequence
    if (A->bal == 0) return creer_tuple(A, 0);
    else return creer_tuple(A, 1);
  }
}


int min_arbre(Arbre a) {
  if (a->fgauche == NULL) return a->cle;
  return min_arbre(a->fgauche);
}

Tuple suppresion_aux(Arbre A) {
  Tuple t;
  int h;
  if (A->fgauche == NULL) {
    return creer_tuple(A->fdroite, -1);
  } else {
    t = suppresion_aux(A->fgauche);
    A->fgauche = t.a;
    h = t.val;
    h = -h;
  }
  if (h == 0) {
    return creer_tuple(A, 0);
  } else {
    A->bal = A->bal + h;
    A = equilibrer(A);
    if (A->bal == 0) return creer_tuple(A, -1);
    else creer_tuple(A, 0);
  }
  return creer_tuple(A, 99);
}


Tuple suppression(Arbre A, int el) {
  Tuple t;
  int h;
  Arbre tmp;
  if (A == NULL) {
    return creer_tuple(A, 0);
  } else if (el > A->cle) {
    t = suppression(A->fdroite, el);
    A->fdroite = t.a;
    h = t.val;
  } else if (el < A->cle) {
    t = suppression(A->fgauche, el);
    A->fgauche = t.a;
    h = t.val;
  } else if (A->fgauche == NULL) {
    tmp = A->fdroite;
    free(A);
    return creer_tuple(tmp, -1);
  } else if (A->fdroite == NULL) {
    tmp = A->fgauche;
    free(A);
    return creer_tuple(tmp, -1);
  } else {
    A->cle = min_arbre(A->fdroite);
    t = suppresion_aux(A->fdroite);
    A->fdroite = t.a;
    h = t.val;
  }
  if (h == 0) {
    return creer_tuple(A, 0);
  } else {
    A->bal = A->bal + h;
    A = equilibrer(A);
    if (A->bal == 0) return creer_tuple(A, -1);
    else return creer_tuple(A, 0);
  }
}


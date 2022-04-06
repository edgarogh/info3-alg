//
// Created by matteo on 08/02/2022.
//

#ifndef AVL_AVL_H
#define AVL_AVL_H

typedef struct n {
    int cle;
    int bal;
    struct n *fgauche, *fdroite;
} noeud;

typedef noeud *Arbre;

typedef struct tuple_ajouter {
    int val;
    Arbre a;
} Tuple;

Arbre init_avl();

Arbre creer_noeud(Arbre gauche, int cle, Arbre droit);

int equilibre_avl(Arbre a);

Arbre rotation_gauche(Arbre a);

Arbre rotation_droite(Arbre a);

Arbre double_rotation_gauche(Arbre a);

Arbre double_rotation_droite(Arbre a);

Arbre equilibrer(Arbre a);

Tuple insertion(Arbre A, int el);

Tuple suppression(Arbre A, int el);

#endif // AVL_AVL_H

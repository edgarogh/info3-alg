#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "a234.h"

pnoeud234 allouer_noeud() {
    pnoeud234 p = (pnoeud234)malloc(sizeof(noeud234));

    p->t = 0;
    p->cles[0] = 0;
    p->cles[1] = 0;
    p->cles[2] = 0;
    p->fils[0] = NULL;
    p->fils[1] = NULL;
    p->fils[2] = NULL;
    p->fils[3] = NULL;

    return p;
}

bool est_feuille(Arbre234 a) {
    return (a->fils[0] == NULL || a->fils[0]->t == 0)
        && (a->fils[1] == NULL || a->fils[1]->t == 0)
        && (a->fils[2] == NULL || a->fils[2]->t == 0)
        && (a->fils[3] == NULL || a->fils[3]->t == 0);
}

/* Idée de l'algorithme décrite ici : https://www.educative.io/page/5689413791121408/80001
 *
 * - on insère toujours dans les feuilles
 * - on ne peut pas insérer dans un nœud 4, donc on s'assure de ne jamais
 *   avoir de nœud 4 là où on va insérer
 * - pour ça, si on croise un nœud 4 lors de la recherche, on le sépare
 *
 *     A B C                  __B__
 *    / | | \     ->         /     \
 *   D  E F  G              A       C
 *                         / \     / \
 *                        D   E   F   G
 */
Arbre234 ajouter_cle(Arbre234 a, int cle) {
    // petite sécurité
    if (a == NULL) {
        a = allouer_noeud();
        a->cles[0] = cle;
        a->t = 2;
        return a;
    }

    // on a trouvé un 4 nœud dans la recherche : on le sépare
    if (a->t == 4) {
        Arbre234 nouvelle_racine = allouer_noeud();
        nouvelle_racine->t = 2;
        nouvelle_racine->cles[0] = a->cles[1];
        
        nouvelle_racine->fils[1] = allouer_noeud();
        nouvelle_racine->fils[1]->t = 2;
        nouvelle_racine->fils[1]->cles[0] = a->cles[2];
        nouvelle_racine->fils[1]->fils[0] = a->fils[2];
        nouvelle_racine->fils[1]->fils[1] = a->fils[3];

        // on évite une allocation et une libération pas très utiles
        // en réutilisant directement la partie gauche de l'arbre comme fils
        // gauche de la nouvelle racine (observer A sur le schéma au dessus
        // pour se convaincre que ça marche)
        nouvelle_racine->fils[0] = a;
        nouvelle_racine->fils[0]->t = 2;

        a = nouvelle_racine;
    }

    // on est arrivés au bout de la recherche, on insère ici
    if (est_feuille(a)) {
        // selon le nombre de clés actuelles, on regarde
        // où insérer et on décale les clés déjà présentes si besoin
        // il y a sans doute moyen de faire ça avec une boucle de 4 lignes
        // mais c'est un coup à faire une erreur d'indice donc j'écris tous
        // à la main, il y a pas tant de cas que ça
        if (a->t == 2) {
            if (a->cles[0] <= cle) {
                a->cles[1] = cle;
            } else {
                a->cles[1] = a->cles[0];
                a->cles[0] = cle;
            }
            a->t = 3;
        } else if (a->t == 3) {
            if (cle >= a->cles[1]) {
                a->cles[2] = cle;
            } else if (cle >= a->cles[0]) {
                a->cles[2] = a->cles[1];
                a->cles[1] = cle;
            } else {
                a->cles[2] = a->cles[1];
                a->cles[1] = a->cles[0];
                a->cles[0] = cle;
            }
            a->t = 4;
        } else {
            printf("PANIC (ajouter_cle) : la feuille a %d enfants\n", a->t);
            exit(1);
        }
    } else { // on est pas sur une feuille : on continue à descendre dans l'arbre
        int i = 0;
        while (i < a->t - 1 && a->cles[i] < cle) {
            i++;
        }
        a->fils[i] = ajouter_cle(a->fils[i], cle);
    }

    return a;
}
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    return (a->fils[0] == NULL || a->fils[0]->t == 0) &&
           (a->fils[1] == NULL || a->fils[1]->t == 0) &&
           (a->fils[2] == NULL || a->fils[2]->t == 0) &&
           (a->fils[3] == NULL || a->fils[3]->t == 0);
}

int inserer_ici(Arbre234 a, int cle);
Arbre234 split(Arbre234 parent, Arbre234 a, int cle);

/* Idée de l'algorithme décrite ici :
 * https://www.educative.io/page/5689413791121408/80001
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

    if (a->t == 4) {
        a = split(NULL, a, cle);
    }

    // on est arrivés au bout de la recherche, on insère ici
    if (est_feuille(a)) {
        inserer_ici(a, cle);
    } else { // on est pas sur une feuille : on continue à descendre dans
             // l'arbre
        int i = 0;
        while (i < a->t - 1 && a->cles[i] < cle) {
            i++;
        }
        int separe = a->fils[i]->t == 4;
        if (separe) { // on a trouvé un 4 nœud dans la recherche : on le
                      // sépare
            a = split(a, a->fils[i], cle);
            // maintenant qu'il a été séparé, on peut refaire l'insertion
            // sans souci, on passera dans le else juste en dessous
            a = ajouter_cle(a, cle);
        } else { // sinon on ajoute récursivement sans se poser de questions
            a->fils[i] = ajouter_cle(a->fils[i], cle);
        }
    }

    return a;
}

/**
 * Sépare un 4 nœud
 */
Arbre234 split(Arbre234 parent, Arbre234 a, int cle) {
    Arbre234 nouvelle_racine;
    int pos;
    if (parent == NULL) {
        // On a pas de racine : l'élément qui remonte devient la racine
        nouvelle_racine = allouer_noeud();
        nouvelle_racine->t = 2;
        nouvelle_racine->cles[0] = a->cles[1];
        pos = 0;
    } else {
        // On a une racine : l'élément qui remonte est ajouté dans le parent
        int middle = a->cles[1];
        pos = inserer_ici(parent, middle);
        nouvelle_racine = parent;
        // on réordonne les enfants pour faire de la place pour
        // les deux 2-nœuds qui vont être insérés ensuite
        for (int i = a->t - 2; i > pos; i--) {
            nouvelle_racine->fils[i + 1] = nouvelle_racine->fils[i];
        }
    }

    nouvelle_racine->fils[pos + 1] = allouer_noeud();
    nouvelle_racine->fils[pos + 1]->t = 2;
    nouvelle_racine->fils[pos + 1]->cles[0] = a->cles[2];
    nouvelle_racine->fils[pos + 1]->fils[0] = a->fils[2];
    nouvelle_racine->fils[pos + 1]->fils[1] = a->fils[3];

    // on évite une allocation et une libération pas très utiles
    // en réutilisant directement la partie gauche de l'arbre comme fils
    // gauche de la nouvelle racine (observer A sur le schéma au dessus
    // pour se convaincre que ça marche)
    nouvelle_racine->fils[pos] = a;
    nouvelle_racine->fils[pos]->t = 2;

    return nouvelle_racine;
}

/**
 * Insère la clé parmi celles de cet arbre, sans chercher à savoir si elle doit
 * aller dans un des arbres enfant ou non.
 *
 * Renvoie l'indice où la clé à été insérée
 */
int inserer_ici(Arbre234 a, int cle) {
    // selon le nombre de clés actuelles, on regarde
    // où insérer et on décale les clés déjà présentes si besoin
    // il y a sans doute moyen de faire ça avec une boucle de 4 lignes
    // mais c'est un coup à faire une erreur d'indice donc j'écris tous
    // à la main, il y a pas tant de cas que ça
    int pos;
    if (a->t == 2) {
        if (a->cles[0] <= cle) {
            a->cles[1] = cle;
            pos = 1;
        } else {
            a->cles[1] = a->cles[0];
            a->cles[0] = cle;
            pos = 0;
        }
        a->t = 3;
    } else if (a->t == 3) {
        if (cle >= a->cles[1]) {
            a->cles[2] = cle;
            pos = 2;
        } else if (cle >= a->cles[0]) {
            a->cles[2] = a->cles[1];
            a->cles[1] = cle;
            pos = 1;
        } else {
            a->cles[2] = a->cles[1];
            a->cles[1] = a->cles[0];
            a->cles[0] = cle;
            pos = 0;
        }
        a->t = 4;
    } else {
        printf("PANIC (inserer_ici) : la feuille a %d enfants\n", a->t);
        exit(1);
    }
    return pos;
}
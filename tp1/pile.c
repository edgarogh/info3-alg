#include "pile.h"
#include "abr.h"
#include <stdio.h>
#include <stdlib.h>

ppile_t creer_pile() {
    ppile_t pile = malloc(sizeof(pile_t));
    *pile = (pile_t){
        .sommet = -1,
    };
    return pile;
}

int detruire_pile(ppile_t p) {
    free(p);
    return 1;
}

int pile_vide(ppile_t p) { return p->sommet == -1; }

int pile_pleine(ppile_t p) { return p->sommet == MAX_PILE_SIZE - 1; }

pnoeud_t depiler(ppile_t p) {
    if (pile_vide(p))
        return NULL;
    else
        return p->Tab[p->sommet--];
}

int empiler(ppile_t p, pnoeud_t pn) {
    if (pile_pleine(p))
        return 0;
    else {
        p->Tab[++(p->sommet)] = pn;
        return 1;
    }
}

void imprimer_pile(ppile_t p) {
    char is_first = 1;
    while (!pile_vide(p)) {
        Arbre_t sommet = depiler(p);
        int cle = sommet->cle;
        if (is_first) {
            printf("%d", cle);
            is_first = 0;
        } else {
            printf(";%d", cle);
        }
    }
}

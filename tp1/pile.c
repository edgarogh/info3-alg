#include <stdlib.h>
#include "abr.h"
#include "pile.h"

ppile_t creer_pile ()
{
  ppile_t pile = malloc(sizeof(pile_t));
  *pile = (pile_t) {
    .sommet = -1,
  };
  return pile;
}

int detruire_pile (ppile_t p)
{
  free(p);
}  

int pile_vide (ppile_t p)
{
  return p->sommet == -1;
}

int pile_pleine (ppile_t p)
{
  return p->sommet == MAX_PILE_SIZE - 1;
} 

pnoeud_t depiler (ppile_t p)
{
  if (pile_vide(p)) return NULL;
  else return p->Tab[p->sommet--];
}

int empiler (ppile_t p, pnoeud_t pn)
{
  if (pile_pleine(p)) return 0;
  else {
    p->Tab[++(p->sommet)] = pn;
    return 1;
  }
}

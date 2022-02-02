#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "abr.h"
#include "pile.h"
#include "file.h"


#define max(a,b) ((a)>(b)?(a):(b))

int feuille (Arbre_t a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if ((a->fgauche == NULL) && (a->fdroite == NULL))
	return 1 ;
      else
	return 0 ;
    }
}

Arbre_t ajouter_noeud (Arbre_t a, Arbre_t n)
{
  /* ajouter le noeud n dans l'arbre a */
  
  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  else
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  return a ;
  
}  

Arbre_t rechercher_cle_arbre (Arbre_t a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else
    {
      if (a->cle == valeur)
	return a ;
      else
	{
	  if (a->cle < valeur)
	    return rechercher_cle_arbre (a->fdroite, valeur) ;
	  else
	    return rechercher_cle_arbre (a->fgauche, valeur) ;
	}
    }
}

Arbre_t ajouter_cle (Arbre_t a, int cle)
{
  Arbre_t n ;
  Arbre_t ptrouve ;
  
  /* 
     ajout de la clé. Creation du noeud n qu'on insere 
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
    {
      n = (Arbre_t) malloc (sizeof(noeud_t)) ;
      n->cle = cle;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      a = ajouter_noeud (a, n) ;
      return a ;
    }
  else
    return a ;
}


Arbre_t lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre_t a = NULL;
  
  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }
    
  fclose (f) ;

  return a ;
}

void afficher_arbre (Arbre_t a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */
  
  int i ;
  
  if (a != NULL)
      {
	afficher_arbre (a->fdroite,niveau+1) ;
	
	for (i = 0; i < niveau; i++)
	  printf ("\t") ;
	printf (" %d (%d)\n\n", a->cle, niveau) ;

	afficher_arbre (a->fgauche, niveau+1) ;
      }
  return ;
}


int hauteur_arbre_r (Arbre_t a)
{
  if (a == NULL)
    return 0;
  else {
    return max(hauteur_arbre_r(a->fgauche), hauteur_arbre_r(a->fdroite));
  }
}

int hauteur_arbre_nr (Arbre_t a)
{
    ppile_t pile = creer_pile();
    ppile_t hauteurs = creer_pile();
    empiler(pile, a);
    empiler(hauteurs, (Arbre_t)1);
    ssize_t h = 0;
    while (!pile_vide(pile)) {
        pnoeud_t n = depiler(pile);
        ssize_t prof = (ssize_t)depiler(hauteurs);
        if (n != NULL) {
            h = max(h, prof);
            empiler(pile, n->fgauche);
            empiler(pile, n->fdroite);
            empiler(hauteurs, (Arbre_t)(h + 1));
            empiler(hauteurs, (Arbre_t)(h + 1));
        }
    }
    return (int)h;
}


void parcourir_arbre_largeur (Arbre_t a)
{
  pfile_t file = creer_file();
  if (a != NULL) enfiler(file, a);

  while (!file_vide(file)) {
    Arbre_t current = defiler(file);
    printf("Noeud %d\n", current->cle);
    if (current->fgauche) enfiler(file, current->fgauche);
    if (current->fdroite) enfiler(file, current->fdroite);
  }
}


/**
 * Renvoie un arbre de la même forme dont les noeuds sont etiquetés par leur niveau
 */
static Arbre_t niveaux(Arbre_t a, int depth) {
  if (a == NULL) return NULL;

  Arbre_t n = malloc(sizeof(noeud_t));
  n->cle = depth;
  n->fgauche = niveaux(a->fgauche, depth + 1);
  n->fdroite = niveaux(a->fdroite, depth + 1);
  return n;
}


void afficher_nombre_noeuds_par_niveau (Arbre_t a)
{
  Arbre_t n = niveaux(a, 0);

  int current_level = 0;
  int current_level_count = 0;

  pfile_t file = creer_file();
  
  for (enfiler(file, n); !file_vide(file);) {
    Arbre_t current = defiler(file);
    if (current != NULL) {
      if (current->cle == current_level) current_level_count++;
      else {
        printf("Niveau %d: %d noeuds\n", current_level, current_level_count);
        current_level = current->cle;
        current_level_count = 1;
      }

      enfiler(file, current->fgauche);
      enfiler(file, current->fdroite);
      free(current);
    }
  }

  printf("Niveau %d (dernier): %d noeuds\n", current_level, current_level_count);
}


int nombre_cles_arbre_r (Arbre_t a)
{
  if (a == NULL) return 0;
  else return 1
    + nombre_cles_arbre_r(a->fgauche)
    + nombre_cles_arbre_r(a->fdroite);
}

int nombre_cles_arbre_nr (Arbre_t a)
{
  pfile_t file = creer_file();
  int cles = 0;
  
  for (enfiler(file, a); !file_vide(file);) {
    Arbre_t current = defiler(file);
    if (current != NULL) {
      cles++;
      enfiler(file, current->fgauche);
      enfiler(file, current->fdroite);
    }
  }
  
  return cles;
}


int min(int a, int b) {
  return a<b ? a : b;
}


int trouver_cle_min (Arbre_t a)
{
  if (a == NULL) {
    fprintf(stderr, "Panic: trouver_cle_min sur un arbre vide, pas de solution\n");
    exit(1);
  }

  if (a->fgauche == NULL) {
    return a->cle;
  } else {
    return trouver_cle_min(a->fgauche);
  }
}


void imprimer_liste_cle_triee_r (Arbre_t a)
{
  if (a == NULL) return;
  
  imprimer_liste_cle_triee_r(a->fgauche);
  printf("%d;", a->cle);
  imprimer_liste_cle_triee_r(a->fdroite);
}


void insertion_pile_triee(ppile_t pile1, Arbre_t a) {
  ppile_t pile2 = creer_pile();

  while (!pile_vide(pile1)) {
    Arbre_t sommet = depiler(pile1);

    if (sommet->cle < a->cle) {
      empiler(pile2, sommet);
    } else {
      empiler(pile1, sommet);
      break;
    }
  }

  empiler(pile1, a);

  while (!pile_vide(pile2)) {
    empiler(pile1, depiler(pile2));
  }
}


void imprimer_liste_cle_triee_nr (Arbre_t a)
{
  ppile_t pile_triee = creer_pile();

  pfile_t file = creer_file();
  
  for (enfiler(file, a); !file_vide(file);) {
    Arbre_t current = defiler(file);
    if (current != NULL) {
      insertion_pile_triee(pile_triee, current);
      enfiler(file, current->fgauche);
      enfiler(file, current->fdroite);
    }
  }

  imprimer_pile(pile_triee);
}

int est_feuille(Arbre_t a) {
    return a != NULL && a->fgauche == NULL && a->fdroite == NULL;
}

int arbre_plein (Arbre_t a)
{
    if (a == NULL) return 0;
    if (est_feuille(a)) return 1;
    if (a->fgauche == NULL || a->fdroite == NULL) return 0;
    return arbre_plein(a->fgauche) && arbre_plein(a->fdroite);
}

int arbre_parfait (Arbre_t a)
{
    if (a == NULL) return 0;
    if (est_feuille(a)) return 1;
    if (a->fgauche == NULL || a->fdroite == NULL) return 0;
    return hauteur_arbre_r(a->fgauche) == hauteur_arbre_r(a->fdroite)
        && arbre_parfait(a->fgauche) && arbre_parfait(a->fdroite);
}

Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur)
{
    if (a == NULL) return NULL;
    if (a->cle > valeur) {
        Arbre_t autre = rechercher_cle_sup_arbre(a->fdroite, valeur);
        if (a->cle > autre->cle) {
            return a;
        } else {
            return autre;
        }
    } else {
        return NULL;
    }
}

Arbre_t rechercher_cle_inf_arbre (Arbre_t a, int valeur)
{
    if (a == NULL) return NULL;
    if (a->cle < valeur) {
        Arbre_t autre = rechercher_cle_inf_arbre(a->fgauche, valeur);
        if (a->cle < autre->cle) {
            return a;
        } else {
            return autre;
        }
    } else {
        return NULL;
    }
}


Arbre_t detruire_cle_arbre (Arbre_t a, int cle)
{
    if (a == NULL) {
        return NULL;
    }

    Arbre_t g = detruire_cle_arbre(a->fgauche, cle);
    Arbre_t d = detruire_cle_arbre(a->fdroite, cle);
    if (a->cle == cle) {
        ajouter_noeud(g, d);
        return g;
    } else {
        Arbre_t resultat = malloc(sizeof(noeud_t));
        resultat->cle = a->cle;
        resultat->fgauche = g;
        resultat->fdroite = d;
        return resultat;
    }
}



Arbre_t intersection_deux_arbres (Arbre_t a1, Arbre_t a2)
{
    Arbre_t inter = malloc(sizeof(noeud_t));
    if (rechercher_cle_arbre(a1, a2->cle)) {
        inter->cle = a2->cle;
    } else {
        free(inter);
        inter = NULL;
    }
    Arbre_t g = intersection_deux_arbres(a1->fgauche, a2->fgauche);
    Arbre_t d = intersection_deux_arbres(a1->fdroite, a2->fdroite);
    if (inter != NULL) {
        ajouter_noeud(inter, g);
        ajouter_noeud(inter, d);
        return inter;
    } else {
        ajouter_noeud(g, d);
        return g;
    }
}

Arbre_t union_deux_arbres (Arbre_t a1, Arbre_t a2)
{
    if (a1 == NULL) {
        return a2;
    }
    if (a2 == NULL) {
        return a1;
    }
    Arbre_t uni = malloc(sizeof(noeud_t));
    uni->cle = a1->cle;
    ajouter_cle(uni, a2->cle);
    Arbre_t g = union_deux_arbres(a1->fgauche, a2->fgauche);
    Arbre_t d = union_deux_arbres(a1->fdroite, a2->fdroite);
    ajouter_noeud(uni, g);
    ajouter_noeud(uni, d);
    return uni;
}

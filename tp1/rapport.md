---
title: ALG TP 1
author: Mattéo DECORSAIRE, Ana GELEZ, Edgar ONGHENA
---

# Piles

# Files

![](https://md.edgar.bzh/uploads/upload_4803ea51dc46f7058a265772d8c87fa3.png)

## Creer / detruire une file 

Pour la créer, on alloue la taille d'une file et on initialise la queue et la tête à 0
Pour la détruire, on libère le tableau precedemment alloué.

## File vide / pleine

Assez trivial, si la taille de la file correspond à sa taille maximum elle est pleine.
De même, si la tête vaut 0, la file est vide.

## Defiler

Tout d'abord, on doit vérifier que la file n'est pas vide.
Si tête et queue sont égaux, c'est comme si la file était vide donc on assigne 0 aux deux, pour reinitialiser la file.
Si la tête est à la limite du tableau, on doit faire la jonction avec le tableau (f.tab[(N-1) +1] = f.tab[0])
Sinon on incrémente la tête de 1.

## Enfiler

Tout d'abord, on doit vérifier que la file n'est pas pleine.
Si la file est vide, on doit séparer la tête de la queuen qui sont au début égales, pour ajouter le premier élément.
Si la queue est à la limite du tableau, on doit faire la jonction avec le tableau (f.tab[(N-1) +1] = f.tab[0])
Sinon on incrémente la queue de 1.

# Arbres ABR

## Hauteur d'un arbre (non-récursif)

Pour l'implémentation non-recursive de cette fonction, nous avons utilisé deux piles,
simulant la pile d'appel de l'implémentation récursive. Une de ces piles contient les
nœuds qu'il faut encore visiter, et l'autre contient la hauteur de ces nœuds.

Le type de pile que nous avions ne pouvait normalement contenir que des pointeurs vers
des nœuds. Pour stocker les hauteurs des nœuds (qui sont des nombres) nous avons décidé
d'utiliser de faux pointeurs qui sont en réalité des nombres. Nous faisons donc des casts
quand nous empilons ou dépilons de cette seconde pile, et nous prenons bien soin de ne jamais
déréférencer les adresses qu'elle stocke, étant donné qu'elles ne sont pas valides.

Une autre solution aurait été de modifier les valeurs des clés des nœuds quand on les ajoutait
dans la pile pour qu'il contienne la hauteur du nœud. Cependant, cette solution aurait modifié
l'arbre passé en paramètre, ce qui est un effet de bord assez indésirable pour une fonction qui
est censé calculer la hauteur de l'arbre.

Une troisième solution aurait été d'allouer une feuille contenant juste la hauteur qu'on veut
retenir comme clé. Cependant, cette solution aurait demandé des allocations supplémentaires.

À part ça, l'algorithme est similaire à la version récursive : on regarde si la hauteur du nœud actuel
est plus grande que la hauteur maximale, et si oui, on change la valeur de la hauteur maximale.

## Arbre plein

Pour savoir si un arbre est plein, on distingue différents cas :

- si c'est une feuille, il est plein ;
- si un des deux enfants n'est pas défini, il n'est pas pas plein ;
- si les deux enfants sont des nœuds, il l'arbre est plein si ses deux enfants sont aussi pleins.

## Arbre parfait

Pour savoir si un arbre est parfait, on distingue différents cas :

- si c'est une feuille, il est parfait ;
- si un des deux enfants n'est pas défini, il n'est pas pas parfait ;
- si les deux enfants sont des nœuds, il l'arbre est parfait si ses deux enfants sont aussi parfaits,
  et que leurs hauteurs sont égales.

## Recherche de la clé immédiatement supérieure

Pour trouver la clé immédiatement supérieure à une valeur demandée, on utilise
les propriétés de l'arbre binaire : on a besoin que de chercher dans la moitié
droite de l'arbre, de manière récursive, jusqu'à n'avoir plus que des clés
inférieures.

## Recherche de la clé immédiatement inférieure

De la même façon, on ne cherche que dans la moitié gauche de l'arbre pour trouver
la clé immédiatement inférieure.

## Destruction d'une clé

On commence par éliminer récursivement la clé à gauche et à droite.

Si la clé actuelle est celle qu'on veut supprimer, on renvoie le sous-arbre
gauche auquel on ajoute le sous-arbre droit (sans la clé actuelle donc).

Sinon, on créé un nouveau nœud qui a comme clé la clé actuelle, et comme enfants
les deux sous-arbres sans la clé à enlever. Créer un nouveau nœud permet d'éviter
des soucis d'aliasing et nous permet de nous assurer facilement que notre arbre a une
structure correcte.

## Intersection de deux arbres

On applique récursivement cette fonction à gauche et à droite pour obtenir
deux nous nouveaux sous-arbres qui sont l'intersection des enfants gauches
et droits et `a1` et `a2`.

Si la clé de `a2` est présente dans `a1`, il faut l'ajouter dans l'arbre renvoyé.
On construit donc un arbre dont la clé est celle de `a2` et dont les enfants sont
les deux sous-arbres construits précédemment.

Sinon, on fusionne les deux enfants en un seul arbre (en ajoutant le sous-arbre droit dans
celui de gauche) et on renvoie l'arbre obtenu. La clé actuelle n'est pas ajoutée car elle
n'est pas présente dans `a1`.

## Union de deux arbres

Si un des deux arbres est nul, on renvoie l'autre.

Autrement on crée un nouvel arbre avec la même clé que `a1`. On y ajoute aussi
la clé de de `a2`. On applique récursivement la fonction sur les enfants, et on
ajoute les arbres ainsi obtenus comme sous-arbres du résultat.

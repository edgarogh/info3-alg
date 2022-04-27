---
title: ALG TP 2
author: Mattéo DECORSAIRE, Ana GELEZ, Edgar ONGHENA
---

## Modification d'ajouter_cle

La fonction ajouter_cle fournie produisait des arbres qui nous semblaient peu pratiques à manipuler : dans le cas de 2-nœuds, les fils étaients aux indices 1 et 2 du tableaux les contenant, au lieu d'être aux indices 0 et 1 comme nous nous y attendions.

Cette représentation nous empêchait d'itérer facilement sur les enfants ou les clés d'un nœud, et nous obligeait à écrire du code très répétitif.

Nous avons donc décidé de réécrire entièrement la fonction d'ajout pour utiliser une représentation qui nous semblait plus logique et plus facile à manipuler.

Nous avons bien pris soin de vérifier que les arbres produits avaient la même structure que ceux de la fonction originale (à part ce souci d'indices pour les enfants des 2-nœuds).

Le code de la fonction est assez largement documenté à l'aide de commentaire si notre implémentation vous intéresse, mais nous ne détaillerons pas ici notre algorithme car ce n'était pas le sujet du TP.

## NombreCles

Cette fonction compte le nombre total de clés dans un arbre. Le nombre de clé dans un nœud est le type de ce nœud moins un (par exemple un 4-nœud a 3 clés). En appliquant ce calcul récursivement à tous les nœuds on calcule le nombre total de clés dans l'arbre.

## CleMax

Selon le type d'arbre, on trouve l'indice de la clé la plus à droite.
On compare cette clé avec la clé la plus grande de l'enfant le plus à droite (qu'on trouve en appliquant la fonction récursivement). On explore ainsi qu'un seul chemin dans l'arbre et pas l'arbre en entier, profitant du fait que les clés sont ordonnées.

## CleMin

Le fonctionnnement est similaire à CleMax, mais on prend la clé et les enfants les plus à gauche.

## RechercherCle

On parcours les clés du nœud une à une. Si on en trouve une égale, on renvoie le nœud actuel. Si on trouve une clé qui est plus grande que la clé recherché, on continue la recherche dans l'enfant à gauche de cette clé, car toutes les clés plus à droite seront plus grandes.

## AnalyseStructureArbre

Cette fonction parcours récursivement l'arbre en incrémentant des compteurs pour compter le nombre total de clés, de 2-nœuds, de 3-nœuds et de 4-nœuds.

## noeud_max

Cette fonction renvoie le nœud dont la somme des clés internes a la plus grande valeur (sans compter les enfants). Afin de ne pas avoir à effectuer plusieurs fois cette somme à chaque visite, l'algorithme repose sur une structure qui associe à chaque nœud la somme de ses clés.

```c
typedef struct {
    Arbre234 a;
    int value;
} noeud_value;
```

La fonction "principale" renvoie une instance de cette structure pour un nœud donné. Elle fonctionne ainsi:
  * Elle somme la valeur des clés du nœud passé
  * Elle construit un `noeud_value` pour le nœud passé, à l'aide de la somme précédemment obtenue, et le stocke dans un accumulateur
  * Elle parcoure récursivement les `noeud_value` des enfants et remplace l'accumulateur si un `noeud_value` à valeur plus élevée est trouvé
  * Une fois tous les enfants parcourus, elle renvoie l'accumulateur, qui correspond au meilleur arbre (avec sa valeur)

La fonction demandée, de signature `Arbre234 noeud_max(Arbre234 a)` appelle cette fonction "principale" et ôte la valeur pour ne garder qu'un `Arbre234`.

```c
Arbre234 noeud_max(Arbre234 a) {
    return noeud_max_and_value(a).a;
}
```

## Afficher_Cles_Largeur

Pour parcourir en largeur, on utilise une pile, modélisée par la structure `bfs` (breadth-first search) et quelques "méthodes" associées. Il s'agit d'une simple pile basée sur une liste chaînée dont les deux extrémités sont connues à tout moment, pour pouvoir efficacement emfiler et défiler en O(1).

L'algorithme est celui d'un parcours en largeur classique. On enfile la racine puis tant que la pile n'est pas vide, on défile la tête courante pour enfiler tous ses enfants.

## Affichage_Cles_Triees_Recursive

Cette fonction parcours récursivement l'arbre pour afficher toutes ses clés dans l'ordre. On peut simplement alterner entre visiter un enfant récursivement et afficher une clé du nœud, en profitant du fait que l'arbre est ordonné.

## Affichage_Cles_Triees_NonRecursive

Pour cette fonction, nous avons décidé d'émuler la récursivité, en implémentant une pile, qui contient les mêmes valeurs que la pile d'appels utilisée par la version récursive.

On a donc un type pile, donc chaque élément contient un `Arbre234`, et un entier qui correspond au `i` de la boucle for dans la version récursive, c'est-à-dire un entier qui sert à se souvenir où nous en sommes de la visite de l'arbre.

On dépile et traite les éléments de cette pile tant qu'elle n'est pas vide, commençant par la racine et `i = 0`.

Quand on dépile un élément, on affiche la clé correspondante au `i` actuel, puis on explore l'enfant qui correspond au `i` actuel en l'empilant. On reprend l'exploration de ce nœud avec un `i` augmenté de 1 en le réempilant.

## Detruire_Cle

Nous n'avons pas réussi à implémenter cette fonction.

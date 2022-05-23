---
title: ALG TP 3
author: Mattéo DECORSAIRE, Ana GELEZ, Edgar ONGHENA
---

## `afficher_graphe_largeur`

On affiche le graphe `g`, en prenant le sommet `r` comme point de départ.
Nous faisons un récursion : pourquoi ? L'algorithme consiste en l'affichage d'abord des sommets a une distance 1 de r puis de ceux à une distance n+1.
Nous appliquons donc l'algorithme pour un sommet donné, affichons et marquons tous ses voisins non marqués. Puis nous faisons la même chose sur chacun des voisins.

## `afficher_graphe_profondeur`
On affiche le graphe `g`, en prenant le sommet `r` comme point de départ.
Comme avec un arbre binaire, nous utilisons une file dans laquelle nous enfilons des sommets voisins à `r`, nous défilons ensuite un à un les sommets en effectuant la même opération à chaque fois (defiler, marquer, afficher, renfiler les voisins non marqués).


## `algo_dijkstra`

Pour cet algorithme, on a eu besoin d'ajouter trois champs à chaque sommet : 

- `selected`, qui indique si un sommet a été « sélectionné », c'est-à-dire traité par l'algorithme. L'algorithme s'arrête une fois que tous les sommets ont été traités au moins une fois.
- `somme_distance`, qui est la plus petite somme de distance pour arriver à ce sommet.
- `predecesseur`, qui est le sommet vers lequel aller pour retourner au point de départ en parcourant le moins de chemin possible.

On aaussi eu besoin d'une fonction auxiliaire : `trouver_plus_proche` qui trouve le prochain sommet à sélectionner. Elle parcourt la liste des sommets déjà sélectionnés et renvoie le plus proche de leurs voisins.

L'algorithme en lui-même commence par une initialisation : on ne sélectionne que le sommet de départ, les autres ne le sont pas. On met la somme des distance de chaque sommet à `INT_MAX` pour marquer qu'on ne l'a pas encore calculée.

Ensuite, tant qu'il reste des sommets non sélectionnés, on prend le sommet non sélectionné le plus proche (en utilisant la fonction auxiliaire). On le sélectionne, et on traite ses voisins : si pour atteindre un voisin il est plus rapide de passer par ce sommet que par les autres chemins qui ont été calculé avant, on met à jour la distance minimale dans `somme_distance` et le sommet précédent dans le plus court chemin dans `predecesseur`.

Ainsi, à la fin de l'algorithme, on peut prendre n'importe quel sommet et parcourir le chemin le plus court pour revenir au point de départ en utilisant les `predecesseur` successifs.

## `degre_maximal_graphe`

Cette fonction calcule le degré sortant maximal parmi les sommets du graphe. Elle itère sur les sommets et calcule leur degré avec `degre_sortant_sommet`. Elle retourne le plus grand d'entre eux.

## `degre_minmal_graphe`

Cette fonction calcule le degré sortant minimal parmi les sommets du graphe. Elle itère sur les sommets et calcule leur degré avec `degre_sortant_sommet`. Elle retourne le plus petit d'entre eux.

# Propriétés sur les graphes

## `simple`
L'idée de l'algorithme est simple, il s'agit en soit de savoir si dans la liste des arcs (qui correspond à un chemin), deux arcs sont identiques ou non.
Nous utilisons donc deux boucles imbriquées pour comparer chaque arc à tous ceux qui le suivent dans la liste.


## `complet`

Dans un graphe dirigé complet à N sommets, il y a N² arrêtes. C'est le maximum possible dans un graphe. On peut donc compter les sommets et les arrêtes et vérifier `nb_sommets`² = `nb_arcs`.

## `regulier`

On récupère le degré du premier sommet (on court-circuite en renvoyant `true` si le graphe est NULL). On vérifie ensuite que tous les sommets ont le même degré que celui stocké précédemment.

## `elementaire`

On parcourt tous les sommets du chemin sur une première boucle. À chaque itération on lance une seconde boucle qui vérifie que tous les sommets suivant le sommet actuel du chemin sont bien différents.

## `eulerien`

On commence par marquer tous les arcs du chemin.
Ensuite, on vérifie que tous les arcs de l'arbre sont bien marqués.

## `hamiltonien`

On commence par marquer tous les sommets du chemin.
Ensuite, on vérifie que tous les sommets de l'arbre sont bien marqués.

## `graphe_eulerien`

On vérifie que les degrés sortants et entrants de tous les nœuds sont égaux SAUF un nœud qui peut avoir un `degré sortant=degré entrant+1` et vice-versa. Il faudrait aussi vérifier que le graphe non-dirigé correspondant à ce graphe est connexe, mais nous ne le faisons pas ici.

## `graphe_hamiltonien`

On récupère le nombre d'arcs du graphe.
On effectue un parcourt en profondeur à partir de tous les sommets en marquant les arcs déjà traversés et en décrémentant de 1 le nombre d'arcs restants à parcourir, à chaque récursion. Si ce nombre atteint 0, tous les arcs ont été parcourus et on court-circuite en renvoyant `true`.

## `distance`

Cette fonction renvoie la distance minimale entre deux sommets dans un graphe. Elle utilise pour celà l'algorithme de Dijkstra, en prenant le premier sommet comme point de départ. En regardant ensuite la valeur de `somme_distance` sur le second sommet, on a la distance entre les deux sommets.

## `excentricite`

Pour calculer l'excentricité, on utilise une fonction auxiliaire récursive qui parcoure en profondeur pour trouver un chemin le plus long. Un champ `marqueur` permet de ne pas parcourir deux fois le même sommet au sein d'une même "descente", mais le champ est remis à zero à la sortie d'un cadre de pile pour permettre la visite du sommet dans une autre "descente".

## `diametre`

On appelle simplement la fonction ci-dessus sur tous les sommets du graphe.


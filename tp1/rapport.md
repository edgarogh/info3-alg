---
title: ALG TP 1
author: Mattéo DECORSAIRE, Ana GELEZ, Edgar ONGHENA
---

# Tests

Tout notre code est testé grâce à des tests unitaires situés :
  * Dans `test_avl.c` pour les AVL
  * Dans `tests.cc` pour le reste

`test_avl` peut être construit avec le Makefile et s'exécute assez simplement et naturellement.

Le fichier `tests.cc` repose sur la bibliothèque [_Google Test_](https://github.com/google/googletest).
Elle peut être installée sur Ubuntu avec les instructions suivantes: https://rationalcity.wordpress.com/2018/07/18/how-to-install-gtest-on-ubuntu/.
Pour exécuter le fichier, il faut taper `make run-tests`.

Certains IDE comme CLion permettent d'exécuter les tests graphiquement compte tenu que le projet soit importé via CMake.

Le fichier `tests.cc` est techniquement écrit en C++ car GTest est prévu pour ce langage, mais nous n'utilisons presque aucune fonctionnalité spécifique au C++ (la seule étant l'usage de `nullptr` au lieu de `NULL`).
Les intérêts de GTest sont :
  * L'intégration avec notre IDE
  * La possibilité de capturer la sortie standard pour tester les fonctions `imprimer_*`
  * La possibilité de tester qu'un appel invalide à `trouver_cle_min` fait bien s'arrêter le programme avec un message d'erreur spécifique

# Piles

## Structure générale d'une pile

On considère que le champ `.sommet` correspond à l'indice du plus haut élément de la pile.
Quand la pile contient un élément, on `.sommet == 0`, et donc **si la pile est vide, `.sommet == -1`.**

## Créer / détruire une pile

La création d'une pile est triviale ; on alloue l'espace nécessaire pour stocker tout un objet `pile_t` et on initialise `.sommet = -1`, pour les raisons expliquées ci-dessus.
Comme le tableau `.T` fait partie de la structure (ce n'est pas un pointeur), il n'est pas nécessaire de l'initialiser pour le moment.

## Pile vide / pleine

Une fois de plus, un sommet valant -1 correspond à une pile vide.
De plus, comme le sommet est l'indice du dernier élément, la file est pleine si son sommet a pour indice le dernier élément du tableau.
Pour un tableau de taille `N`, il s'agit de `N-1`.
Ici, c'est `MAX_PILE_SIZE - 1`.

## Dépiler / empiler

Les dépilements se font simplement en _décrémentant_ le sommet, et en renvoyant la valeur de l'_ancien_ indice.
Les empilements se font à l'envers, en _incrémentant_ le sommet puis en définissant le _nouvel_ indice.
Dans les 2 situations, on vérifie toujours que l'opération ne va pas faire prendre une valeur invalide au sommet.

## Impression de la pile

Pour des raisons de débogage, une fonction `imprimer_pile` a été rajoutée à la spécification.
Elle affiche les clés des valeurs de la pile séparées par des points-virgule.

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

## Hauteur d'un arbre (récursif)

Le nœud d'un arbre binaire possède ou bien 2 enfants qui sont des arbres binaires, ou bien 0 enfants (arbre vide).

La hauteur d'un arbre correspond à :
  * `0` si l'arbre est vide
  * `1 + max(gauche, droit)` si l'arbre possède 2 enfants

L'implémentation du calcul de hauteur récursif est calquée sur cette définition. Le _cas de base_ de la récursion est le cas où l'arbre est vide (il vaut `NULL`).

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

## Parcours en largeur

Le parcours en largeur de n'importe quel arbre s'implémente avec une file. On l'initialise avec le nœud racine, puis tant que la file n'est pas vide, on défile un élément dont on ajoute les enfants de nouveau sur la pile.
En pratique, à chaque itération, on effectuerait une opération sur le nœud courant.
Ici, on décide d'afficher la clé du nœud.

## Affichage du nombre de nœuds par niveau

Étant donné un arbre, nous souhaitons une séquence dont chaque élément d'indice `i` correspond au nombre de nœuds à la profondeur `i` de l'arbre.
Le problème a été simplifié en le divisant en 2 :

  * Dans un premier temps, on utilise une nouvelle fonction récursive `Arbre_t niveaux(Arbre_t a, int depth)` qui créer un arbre ayant exactement la même topologie que celui passé en paramètre, mais dont les étiquettes correspondent à la profondeur du nœud, et non à des valeurs arbitraires.
    Il ne s'agit plus du tout d'un arbre binaire.
    On ne s'intéressera plus à l'arbre initial passé en paramètre à `afficher_nombre_noeuds_par_niveau`.
  * Dans un second temps, on parcourt le nouvel arbre en largeur. Par définition, le parcours en largeur se fait niveau par niveau.
    Comme notre nouvel arbre — par construction — est étiqueté par niveau, il suffit de compter le nombre d'occurrences d'une même valeur pour savoir combien de nœuds se trouvent sur un niveau donné.
    À chaque fois que l'étiquette du nœud visité change, on affiche le nombre de nœuds qui ont été vus avec l'étiquette précédente et on remet le compteur à zéro.

## Nombre de clés d'un arbre (récursif)

> Le nœud d'un arbre binaire possède ou bien 2 enfants qui sont des arbres binaires, ou bien 0 enfants (arbre vide).

Dans le cas ou un nœud est vide (`NULL`), il n'a pas de clé. Sinon, il en a une.

Si on étend ça à un arbre, un arbre vide n'a toujours pas de clé, car son nœud n'en a pas et qu'il a 0 enfants.
Par contre, un arbre non vide possède sa propre clé et les clés de ses deux enfants.
Cela s'implémente très naturellement avec une récursion.

## Nombre de clés d'un arbre (non récursif)

Tandis que la version récursive traite chaque nœud comme un arbre, la version non récursive parcoure tous les nœuds en largeur et ne cherche qu'à savoir si le nœud visité à une itération donnée est vide ou non ; auquel cas, elle incrémente un compteur.
Les enfants ne sont pas considérés, puisque le parcours en largeur causera leur traversée ultérieure.

## Trouver clé minimale

Dans un premier temps, on s'assure que l'arbre n'est pas vide (la fonction n'aurait pas de solution).

Ensuite, on se base strictement sur la définition d'un ABR.
Il suffit de trouver le nœud le plus à gauche possible pour avoir la valeur minimale de l'arbre.
Ici, nous faisons ça récursivement, mais il aurait été tout aussi simple de faire ça itérativement avec une quantité de mémoire finie, sans allocation ni appels.

## Imprimer une liste triée (récursif)

D'après la définition d'un ABR, pour imprimer une liste triée de nœuds, il suffit de faire un parcours en profondeur en commençant par la gauche (ordre croissant).
La valeur du nœud visité actuellement doit être affichée entre la visite de la gauche et de la droite, puisque par construction, la clé ne peut qu'être comprise entre tous les nœuds de gauche et ceux de droite.

## Imprimer une liste triée (non récursif)

La version non récursive est considérablement plus complexe comme le parcours en largeur n'a rien de remarquable pour visiter les nœuds d'un ABR.
Notre solution "bête" est de visiter les nœuds sans ordre particulier (ici, c'est un parcours en largeur, mais peu importe), et d'ajouter leurs clés à une pile qui reste toujours triée à un moment donné.

La gestion de la pile triée se fait avec `void insertion_pile_triee(ppile_t pile1, Arbre_t a)`.
L'algorithme repose sur une seconde pile, qui sert de stockage temporaire.
C'est une sorte de tri par insertion où 2 éléments consécutifs sont visibles au maximum à un moment donné, comme si on essayait d'insérer une carte à jouer dans un paquet trié, en ayant le droit de n'avoir que 2 piles face à soi, et en respectant le contrat d'une pile (empilement et dépilement par le dessus).

À la fin, on affiche cette pile triée.

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

# Arbres AVL

`test_avl.c` sert à tester les implémentations de `avl.c`

## Types dans `avl.h`
```c 
typedef struct n {
    int cle;
    int bal;
    struct n *fgauche, *fdroite;
} noeud;

typedef noeud *Arbre;

// on utilise cette structure pour insertion, pour indiquer une information sur l'arbre qu'on renvoie
typedef struct tuple_ajouter {
    int val;
    Arbre a;
} Tuple;

```

## `init_avl` & `creer_noeud`
Utile pour construire des arbres "à la main" lors des tests.

## `equilibre_avl`
Utile pour connaitre l'equilibre d'un arbre sans utiliser le champ de la structure. Permet de vérifier que chaque noeud à la bonne valeur bal qui correspon à la réalité de l'arbre.

##  `rotation_gauche`
Nous devons tout d'abord réagencer les noeuds comme indiqué dans l'algorithme. Il s'agit de deux liens : le droit de la racine et le gauche de la nouvelle racine.
La partie la plus importante de la fonction est de conserver les propriétés de l'avl : il faut que l'equilibre enregistré soit le bon.

Deux cas peuvent être observés :
- 1) Si le sous arbre droit est équilibré, alors le sous arbre gauche du nouvel arbre ne le sera pas :
     ![](https://md.edgar.bzh/uploads/upload_ef6898ba1c7235b03a37e29285cc69df.png)


- 2) Si le sous arbre droit n'est pas équilibré, alors le sous arbre gauche du nouvel arbre le sera, le plus long sera directement à droite de la racine, ce qui compensera le désequilibre :
     ![](https://md.edgar.bzh/uploads/upload_f36252bd20fe6249621d832236382c88.png)

Dans tous les cas il faut appliquer : bal(A)= h(D)-h(G)
Nous retrouvons cette logique ici :
```c 
root->bal = root_bal - max2(new_root_bal, 0) - 1; // on obtient soit 0 soit 1
new_root->bal = min3(root_bal - 2, root_bal + new_root_bal - 2, new_root_bal - 1); // on obtient soit 0 soit -1
  ```

De même pour `rotation_droite`

## `equilibrer`

Identique à l'implementation du cours

## `insertion`

C'est une fonction récursive qui parcourt l'arbre jusqu'à trouver la place ou doit être inséré l'element (ligne 2 à 19). Une fois inséré, on s'occupe de le réajuster pour qu'il corresponde aux propriétés de l'AVL (ligne 21 à 27).

```c 
Tuple insertion(Arbre A, int el) {
  int h; // si h = 0 pas besoin d équilibre l arbre, sinon h vaut 1
  // algorithme d insertion abr classique
  if (A == NULL) {
    A = creer_noeud(NULL, el, NULL);
    A->bal = 0;
    return creer_tuple(A, 1);
  } else if (el == A->cle) { // deja dans l arbre
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
  // Cette partie, equilibre l arbre et ajuste bal en conséquence
  if (h == 0) { // inserer ne necessitera pas d equilibre (bal A = 0, 1, -1)
    return creer_tuple(A, 0);
  } else {
    A->bal = A->bal + h; // sinon on met à jour bal avec notre variation
    A = equilibrer(A); // on équilibre l arbre
    if (A->bal == 0) return creer_tuple(A, 0); // completement équilibré
    else return creer_tuple(A, 1); // désequilibré
  }
}
```

## `supression`

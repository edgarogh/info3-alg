

/* structure noeud presentee en cours */

typedef struct n {

    int t; /* t type de noeud 0, 2, 3 ou 4 */
    int cles[3];
    struct n *fils[4];

} noeud234, *pnoeud234;

/* type Arbre, pointeur vers un noeud */

typedef pnoeud234 Arbre234;

Arbre234 lire_arbre(char *nom_fichier);

void afficher_arbre(Arbre234 a, int niveau);

Arbre234 ajouter_cle(Arbre234 a, int cle);

void Affichage_Cles_Triees_NonRecursive(Arbre234 a);


#include <stdbool.h>
#include <stddef.h>

typedef struct a *parc_t;

/*
  definition des types sommet et pointeur de sommet
  un graphe est constitué d'une liste de sommets
*/

typedef struct s {
    int label;                // label du sommet
    parc_t liste_arcs;        // arcs sortants du sommet
    struct s *sommet_suivant; // sommet suivant dans le graphe
    int couleur;              // couleur du sommet
    // Algo de Djikstra
    bool selected;
    int somme_distance;
    struct s *predecesseur;

    // Utilisé pour tout et n'importe quoi
    int marqueur;
} sommet_t, *psommet_t;

/*
  definition des types arc et pointeur d'arc
  Les arcs sortants d'un sommet sont chainés
  Pour chaque arc, il y a un poids qui peut par exemple correspondre a une
  distance
*/

typedef struct a {

    int poids;             // poids de l arc
    psommet_t dest;        // pointeur sommet destinataire
    struct a *arc_suivant; // arc suivant

    // Utilisé pour tout et n'importe quoi
    int marqueur;

} arc_t, *parc_t;

/*
  pgraphe_t: pointeur vers le premier sommet d'un graphe
*/

typedef psommet_t pgraphe_t;

typedef struct c {
    size_t len;
    psommet_t start;
    parc_t *arcs;
} chemin_t;

psommet_t chercher_sommet(pgraphe_t g, int label);

void ajouter_arc(psommet_t o, psommet_t d, int distance);

int nombre_arcs(pgraphe_t g);

int nombre_sommets(pgraphe_t g);

void lire_graphe(char *file_name, pgraphe_t *g);

void ecrire_graphe(psommet_t p);

void ecrire_graphe_colorie(psommet_t p);

int colorier_graphe(pgraphe_t g);

void afficher_graphe_profondeur(pgraphe_t g, int r);

void afficher_graphe_largeur(pgraphe_t g, int r);

void algo_dijkstra(pgraphe_t g, int r);

int distance(pgraphe_t g, int x, int y);

int degre_sortant_sommet(pgraphe_t g, psommet_t s);

int degre_entrant_sommet(pgraphe_t g, psommet_t cible);

/// Renvoie `true` si les arêtes du graphe n'ont pas de sommet en commun
int independant(pgraphe_t g);

/// Renvoie `true` si toutes les paires de sommet du graphe sont jointes par un
/// arc
int complet(pgraphe_t g);

/// Graphe régulier: tous les sommets ont le meme degré
/// g est le ponteur vers le premier sommet du graphe
int regulier(pgraphe_t g);

chemin_t chemin_new(pgraphe_t g, size_t len, const int *labels);

/// Renvoie le sommet du chemin `chemin` à l'indice `index`.
///
/// L'indice est compris entre 0 et `chemin.len` (inclus), car il y a un sommet
/// de plus que d'arcs.
psommet_t chemin_sommet(chemin_t chemin, size_t index);

int simple(pgraphe_t g, chemin_t c);

int elementaire(pgraphe_t g, chemin_t c);

int eulerien(pgraphe_t g, chemin_t c);

int hamiltonien(pgraphe_t g, chemin_t c);

int graphe_eulerien(pgraphe_t g);

int graphe_hamiltonien(pgraphe_t g);

int excentricite(pgraphe_t g, int label);

int diametre(pgraphe_t g);

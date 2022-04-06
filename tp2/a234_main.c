#include <stdlib.h>
#include <stdio.h>
#include "a234.h"

int main(int argc, char **argv) {
  Arbre234 a;

  if (argc != 2) {
    fprintf(stderr, "il manque le parametre nom de fichier\n");
    exit(-1);
  }

  a = lire_arbre(argv[1]);

  printf("==== Afficher arbre ====\n");

  afficher_arbre(a, 0);
}

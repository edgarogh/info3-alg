#include "file.h"
#include <stdlib.h>

pfile_t creer_file() {
    pfile_t f = malloc(sizeof(file_t));
    f->queue = 0;
    f->tete = 0;
    return f;
}

int detruire_file(pfile_t f) {
    free(f);
    return 0;
}

int file_vide(pfile_t f) { return (f->tete == 0); }

int file_pleine(pfile_t f) {
    if (file_vide(f))
        return 0;
    int taille;
    if (f->tete <= f->queue) {
        taille = f->queue - f->tete + 1;
    } else {
        taille = f->queue + MAX_FILE_SIZE - f->tete + 1;
    }

    return taille == MAX_FILE_SIZE - 1;
}

void *defiler(pfile_t f) {
    if (!file_vide(f)) {
        void *n = f->Tab[f->tete];
        if (f->tete == f->queue) {
            f->tete = 0;
            f->queue = 0;
        } else {
            if (f->tete == MAX_FILE_SIZE - 1) {
                f->tete = 1;
            } else {
                f->tete++;
            }
        }
        return n;
    }
    return NULL;
}

int enfiler(pfile_t f, void *p) {
    if (!file_pleine(f)) {
        if (file_vide(f)) {
            f->tete = 1;
        }
        if (f->queue == MAX_FILE_SIZE - 1) {
            f->queue = 1;
        } else {
            f->queue++;
        }
        f->Tab[f->queue] = p;
        return 1;
    }
    return 0;
}

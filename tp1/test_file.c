#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "file.h"


void test00() {
    pfile_t f = creer_file();
    assert(file_vide(f));
}

void test01() {
    pfile_t f = creer_file();
    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pnoeud_t n = malloc(sizeof(noeud_t));
        n->cle = i;
        enfiler(f, n);
    }

    assert(file_pleine(f));
    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pnoeud_t n = defiler(f);
        if (i < 31)
            assert(n->cle == i);
        else
            assert (n == NULL);
    }
    assert(file_vide(f));
}

void test02() {
    pfile_t f = creer_file();
    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pnoeud_t n = malloc(sizeof(noeud_t));
        n->cle = i;
        enfiler(f, n);
        pnoeud_t x = defiler(f);
        assert(x == n);
    }

    assert(file_vide(f));
}

int main() {
    printf("TEST 1");
    test00();
    printf("✔\n");

    printf("TEST 2");
    test01();
    printf("✔\n");

    printf("TEST 3");
    test02();
    printf("✔\n");
}




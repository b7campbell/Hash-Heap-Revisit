#include "heap.h"

void insert(int n) {
    int siz;
    int *hep;

    hep = heapp.hep;
    siz = heapp.size;

    if (siz >= heapp.max_size) {
        fprintf(stderr, "Warning: Heap full\n");
        return;
    }

    hep[siz] = n;
    per_up(siz);
    heapp.size += 1;
    printf("insert %i\n", n);
}

#define EMPTY (-1)
#define HEAD 0
void deletemin() {
    int *hep;

    hep = heapp.hep;

    if (heapp.size == 0) {
        printf("error_structure_is_empty\n");
        return;
    }
    /* BCC: potentiall dangerous side effects here*/
    printf("deleteMin %i\n", *hep);
    *hep = hep[--heapp.size];
    hep[heapp.size] = EMPTY;
    per_down(HEAD);
}

#define L_CHILD 1
#define R_CHILD 1
void per_down(int i) {
    int len, lchild, rchild, min_index, tmp;
    int *hep;

    len = heapp.size;
    lchild = (i << 1) + L_CHILD;
    rchild = lchild + R_CHILD;
    hep = heapp.hep;

    /* Case 1: index i is already a leaf */
    if (rchild > len) /* BCC: may be a bug?? */
        return;

    if (hep[i] > hep[lchild])
        min_index = lchild;
    if (hep[i] > hep[rchild])
        min_index = rchild;
    if (min_index != i) {
        tmp = hep[i];
        hep[i] = hep[min_index];
        hep[min_index] = tmp;
        per_down(min_index);
    }
}
void per_up(int i) {
    int p, tmp;
    int *hep;

    if (i == 0)
        return;

    p = (i - 1) / 2; /* integer division acts as a floor */
    hep = heapp.hep;

    if (hep[p] > hep[i]) {
        tmp = hep[p];
        hep[p] = hep[i];
        hep[i] = tmp;
        per_up(p);
    }
}

 /* insert, deletemin */


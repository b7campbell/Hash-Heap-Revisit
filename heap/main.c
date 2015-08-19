#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "heap.h" /* BCC: Will change */

#define MAX_MEM 10000
#define EMPTY (-1)

void initialize_heap(size_t memory_to_allocate);
void print_heap(void);
void verify_heap(void);

int rand(void);
int abs(int);

struct Heap heapp;

/* opting for static alloc rather than realloc */
int main(void) {
    int i;

    initialize_heap(MAX_MEM);
    /* testing only */
    /* srand((unsigned) time(NULL)); */
    for (i = 10000; i > 0; --i) {
        insert(i);
        /* insert(abs(i * rand()));*/
        /* print_heap();*/
    }
    /* print_heap();*/
    /* end testing */
    verify_heap();
    free(heapp.hep);
    return 0;
}

void initialize_heap(size_t m) {
    size_t i;

    heapp.hep = malloc(sizeof(int) * m);
    for (i = 0; i < m; ++i) {
        heapp.hep[i] = EMPTY;
    }
    heapp.size = 0;
    heapp.max_size = m;
    return;
}

void print_heap(void) {
    int i;
    int *hep;

    hep = heapp.hep;

    for (i = 0; i < heapp.size; ++i) {
        printf("[%3i] %6d\t", i, hep[i]);
        if (!(i % 5))
            printf("\n");
    }
}

void verify_heap(void) {
    int i, der;
    int *hep;

    hep = heapp.hep;

    for (i = 0; i < heapp.size; ++i) {
        der = i / 2;
        if (!(i % 2))
            der -= 1;
        if (der < 0)
            der = 0;
        if (hep[der] > hep[i]) {
            printf("\nERROR: HEAP NOT VALID i: %d hep[i]: %d \n", der, hep[der]);
            printf("ERROR: HEAP NOT VALID i: %d hep[i]: %d \n", i, hep[i]);
            exit(EXIT_FAILURE);
        }
    }
    printf("Heap looks good!\n");
}

#ifndef HASH_HEAP_H
#define HASH_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HashEntry {
    int data;
    /* will be expanded in future */
};

struct HashTable {
    int size;
    struct HashEntry *hep;
};

extern struct HashTable htabp;

void allocate_storage_ht(size_t n);
void initialize_ht(size_t n);

#endif /* HASH_HEAP_H */

#include "hash_heap.h"

void initialize_ht(size_t n) {
    allocate_storage_ht(n);
    htabp.size = n;
}

void allocate_storage_ht(size_t n) {
    htabp.hep = malloc(sizeof(struct HashEntry) * n);
}


#ifndef HASH_HEAP_H
#define HASH_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******** Hash Table ********/
struct HashEntry {
    int data;
    struct HashEntry *next;      /* for next in list; Null if last */
    struct HashEntry *prior;     /* for prior in list; Null if head */

    struct HeapEntry *heap_ptr;
};

struct HashTable {
    int size;
    struct HashEntry *hep;
};

extern struct HashTable htab;

void allocate_storage_ht(size_t);
void initialize_ht(size_t);

void lookup(int);
void insert(int);
void delete_entry(int);
void print_ht(void);

/******** Heap ********/
struct Heap {
    int size;
    int max_size;
    int *hep;
    /* BCC: Make Heap Entry a thing... */
};

extern struct Heap heapp;
extern FILE* outfp;

void initialize_heap(size_t);
void clear_heap(void);

void insert_heap(int);
void deletemin(void);

void per_up(int);
void per_down(int);

void verify_heap(void);
void print_heap(void);

#endif /* HASH_HEAP_H */

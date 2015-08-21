#include "hash_heap.h"

#define EMPTY (-1)

/*
 *  Hash Function
 */
int hash(int n) {
    /* BCC: only accomodates 101 and pos */
    return n % 101;
}

/*
 *  Create HashTable of N Entries
 */
void initialize_ht(size_t n) {
    struct HashEntry *max, *hep;

    allocate_storage_ht(n);
    htab.size = n;

    hep = htab.hep;
    max = hep + n;
    while (max - hep > 0) {
        hep->data  = EMPTY;
        hep->next  = NULL;
        hep->prior = NULL;
        ++hep;
    }
}

/*
 *  Allocate N entries and Set Value to -1
 */
void allocate_storage_ht(size_t n) {
    htab.hep = malloc(sizeof(struct HashEntry) * n);
}

/*
 *  Function 0: Insert
 *  Hash a Value and Insert it into Table
 */
void insert(int n) {
    int i;
    struct HashEntry *hep;

    i = hash(n);
    hep = &(htab.hep[i]);

    /*--------------------
      Check The List Head
     --------------------*/

    /* Case 1: Base is Empty */
    if (hep->data == EMPTY) {
        hep->data = n;
        hep->next = NULL;
        hep->prior = NULL;
        printf("insert %i\n", hep->data);
        return;
    }
    /* Case 2: Present at Base */
    else if (hep->data == n)
    {
        printf("error_already_present\n");
        return;
    }

    /*--------------------
      Check The List Head
     --------------------*/

    while (hep->next != NULL) {
        hep = hep->next;

        /* Case 3: Present in List */
         if (hep->data == n) {
            printf("error_already_present\n");
            return;
        }
    }

    /* Case 4: Not found in list; allocate new to end */
    hep->next = malloc(sizeof(struct HashEntry));
    hep->next->prior = hep;
    hep->next->data = n;
    hep->next->next = NULL;
    printf("insert %i\n", hep->next->data);
}

/*
 *  Function 1: Lookup          "Find"
 *  Hash a Value and Search for it in Table
 */
void lookup(int n) {
    int i;
    struct HashEntry *hep;

    i = hash(n);
    hep = &(htab.hep[i]);

    /*--------------------
      Check The List Head
     --------------------*/

    if (hep->data == n) {
        printf("find %i\n", n);
        return;
    }

    /*----------------
      Begin Iterating
     -----------------*/

    /* Case 1: Stop if in List */
    while (hep->next != NULL) {
        hep = hep->next;
        if (hep->data == n) {
            printf("find %i\n", n);
            return;
        }
    }

    /* Case 2: Not Present in List */
    printf("not_find %i\n", n);
}

/*
 *  Function 3: Delete_Entry    "Delete"
 *  Hash a Value and Search for it in Table
 *
 *    delete helper for mid-list
 *    delete helper base for list-head
 */
void delete_helper(struct HashEntry *);
void delete_helper_base(struct HashEntry *);
void delete_entry(int n) {
    int i;
    struct HashEntry *hep;

    i = hash(n);
    hep = &(htab.hep[i]);

    /*--------------------
      Check The List Head
     --------------------*/

    /* Case 1: No List */
    if (hep->data == EMPTY) {
        printf("error_not_find %i\n", n);
        return;
    }
    else if (hep->data == n) {
        /* Case 2A: No Linked List; Easy 'removal' */
        if (hep->next == NULL) {
            hep->data = EMPTY;
            printf("delete %i\n", n);
        }
        /* Case 2B: Linked List; Shift required */
        else {
            delete_helper_base(hep);
            printf("delete %i\n", n);
        }
        return;
    }

    /*----------------
      Begin Iterating
     -----------------*/

    while (hep->next != NULL ) {
        hep = hep->next;

        if (hep->data == n) {
            /* Case 1A: End of List; Easy Removal */
            if(hep->next == NULL) {
                free(hep);
                printf("delete %i\n", n);
            }
            /* Case 1B: In list; shift required */
            else {
                delete_helper(hep);
                printf("delete %i\n", n);
            }
            return;
        }
    }

    /* Case 2: Not in List */
    printf("error_not_find %i\n", n);
    return;
}
/* Delete the entry after the current, then shift left */
void delete_helper(struct HashEntry *hep) {
    hep->prior->next = hep->next;
    free (hep);
}
/* Replace value of base entry with next, then shift list left */
void delete_helper_base(struct HashEntry *hep) {
    struct HashEntry *thep;

    thep = hep->next;

    hep->data = hep->next->data;
    hep->next = hep->next->next;
    free (thep);
}

/*void deletemin(int n);*/

/* Print HT */
void print_ht() {
    int i;
    struct HashEntry *hep;

    for(i = 0; i < htab.size; ++i)
    {
        hep = &(htab.hep[i]);
        if ( hep->data >= 0) {
            printf(" [%3i] %9i", i, hep->data );
            while(hep->next != NULL) {
                hep = hep->next;
                printf(" |-> %9i", hep->data);
            }
            printf("\n");
        }
/*        else
            printf(" [%3i] %9s |\n", i, "Empty");
*/  }
}


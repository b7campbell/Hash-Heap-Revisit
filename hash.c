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
    allocate_storage_ht(n);
    htabp.size = n;
}

/*
 *  Allocate N entries and Set Value to -1
 */
void allocate_storage_ht(size_t n) {
    size_t i;

    htabp.hep = malloc(sizeof(struct HashEntry) * n);
    for (i = 0; i < n; ++i)
        htabp.hep[i].data = EMPTY;
}

/*
 *  Function 0: Insert
 *  Hash a Value and Insert it into Table
 */
void insert(int n) {
    int i;
    struct HashEntry *hep;

    i = hash(n);
    hep = &(htabp.hep[i]);

    if (hep->data == EMPTY) {
        hep->data = n;
        hep->next = NULL;
        hep->prior = NULL;
        return;                 /* Case 1: Base is Empty */
    }
    else if (hep->data == n)
    {
        printf("error_already_present\n");
        return;                 /* Case 2: Present at Base */
    }

    while (hep->next != NULL) {
        hep = hep->next;
        if (hep->data == n) {
            printf("error_already_present\n");
            return;             /* Case 3: Present in List */
        }
    }

    /* next is Null; at the last entry in list; allocate new */
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
    hep = &(htabp.hep[i]);

    if (hep->data == n) {
        printf("find %i\n", n);
        return;                 /* Case 2: Base Node */
    }

    while (hep->next != NULL ) {
        hep = hep->next;
        if (hep->data == n) {
            printf("find %i\n", n);
            return;             /* Case 3: Present in List */
        }
    }
    printf("not_find %i\n", n); /* Case 1: Not Present in Base Node */
}

/*
 *  Function 3: Delete_Entry    "Delete"
 *  Hash a Value and Search for it in Table
 */
void delete_helper(struct HashEntry *);
void delete_helper_base(struct HashEntry *);
void delete_entry(int n) {
    int i;
    struct HashEntry *hep;

    i = hash(n);
    hep = &(htabp.hep[i]);

    if (hep->data == EMPTY) {
        printf("error_not_find %i\n", n);
        return;                 /* Case 1: No List */
    }
    else if (hep->data == n) {
        /* Case 2A: No Linked List; Easy 'removal' */
        if (hep->next == NULL) {
            hep->data = EMPTY;
            printf("delete %i\n", n);
            return;
        }
        /* Case 2B: Linked List; Shift required */
        else {
            delete_helper_base(hep);
            printf("delete %i\n", n);
        }
    }

    while (hep->next != NULL ) {
        hep = hep->next;
        if (hep->data == n) {
            if(hep->next == NULL) { /* Case 3A: End of List; Easy Removal */
                free(hep);
                printf("delete %i\n", n);
            } else {
                delete_helper(hep); /* Case 3B: In list; shift required */
                printf("delete %i\n", n);
            }
            return;
        }
    }
    printf("error_not_find %i\n", n); /* Case 4: Not Present in List */
    return;
}
/* delete the entry after current, shift list over left */
void delete_helper(struct HashEntry *hep) {
    hep->prior->next = hep->next;
    free (hep);
}
void delete_helper_base(struct HashEntry *hep) {
    struct HashEntry *thep;

    thep = hep->next;

    hep->data = hep->next->data;
    hep->next = hep->next->next;
    free (thep);
}

/*void deletemin(int n);*/
void delete_entry(int n);

/* 
        case OP_DELETE :
            printf("DELETE: %i\n", *++args);
            break;
*/


/* look more into getline, memset, strtol */
#include "hash_heap.h"

#define READ "r"
#define STDIN 0
#define MAX_LINE_SIZE 256

void parse_input(char *);
void run_command(int *args[]);

void print_ht();

/* globally static, declared in .h, defined here */
struct HashTable htabp;

int main(int argc, char *argv[])
{
    FILE *fp;
    char *line;
    size_t len;
    ssize_t nread;

    fp = NULL, line = NULL;
    nread = len = 0;
    if(argc >= 2) {
        if ( (fp = fopen(argv[1], READ)) == NULL) {
            fprintf(stderr, "Failed to open file \n");
            exit(1);
        }
    }
    else {
        /* BCC: more later */
        printf("Did not enter a filename. Enterting Interactive Mode...\n");
        if ( (fp = fdopen(STDIN, READ)) == NULL) {
            fprintf(stderr, "Cannot read from stdin\n");
            exit(1);
        }
    }

    while ( (nread = getline(&line, &len, fp)) != EOF ) {
        /* printf("from while: %s", line <- before parsing);*/
        parse_input(line);
    }

    print_ht();

    free(htabp.hep);
    free(line);
    fclose(fp);
    return EXIT_SUCCESS;
}

#define OP_INSERT 0
#define OP_LOOKUP 1
#define OP_DELMIN 2
#define OP_DELETE 3

#define DECIMAL 10
#define MAX_NUM_OF_ARGS 2
#define NIL (-1)
void parse_input(char *s)
{
    int *args[MAX_NUM_OF_ARGS];
    size_t i, argc;

    long arg;          /* arg from string */
    char *arg_end;

    for (arg = strtol(s, &arg_end, DECIMAL), i = 0; s != arg_end;
                arg = strtol(s, &arg_end, DECIMAL), ++i) {
        s = arg_end;
        args[i] = malloc(sizeof(int));
        *(args[i]) = (int)arg;
    }

    argc = i;

    if (argc == 1) {
        initialize_ht(**args);
        free(*args);
        return;
    }
    run_command(args);

    while (i > 0)
        free(args[--i]);
}

void run_command(int *args[]) {
    switch (**args) {
        case OP_INSERT :
            insert(**++args);
            break;
        case OP_LOOKUP :
            lookup(**++args);
            break;
        case OP_DELMIN :
            break;
        case OP_DELETE :
            delete_entry(**++args);
            break;
        default :
            fprintf(stderr, "WARNING: can't parse input: Operation %i not \
                                found \n EXITING IMMEDIATELY \n", **args);
            exit(EXIT_FAILURE);
    }
}

void print_ht() {
    int i;
    struct HashEntry *hep;

    for(i = 0; i < htabp.size; ++i)
    {
        hep = &(htabp.hep[i]);
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


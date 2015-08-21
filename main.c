#include "hash_heap.h"
#include "cli.h"

#define MAX_LINE_SIZE 256

#define MAX_MEM 10000

void get_input(void);
void parse_input(char *);
void run_command(int *args[]);
void cleanup(void);

/* globally static, declared in .h, defined here */
struct HashTable htab;

FILE *infp, *outfp;

int main(int argc, char *argv[])
{
    extern FILE *infp, *outfp;

    infp = outfp = NULL;

    /* Open Input and Output Files */
    file_setup(argc, argv);
    /* Parse Commands from Input File or STDIN */
    get_input();
    /* Cleanup */
    cleanup();
    return EXIT_SUCCESS;
}

void get_input() {
    ssize_t nread;
    size_t  len;
    char    *line;

    nread = len = 0;
    line = NULL;

    while ( (nread = getline(&line, &len, infp)) != EOF ) {
        parse_input(line);
    }
    free(line);
}

#define OP_INSERT 0
#define OP_LOOKUP 1
#define OP_DELMIN 2
#define OP_DELETE 3
#define OP_PRINT  4

#define DECIMAL 10
#define MAX_NUM_OF_ARGS 2

#define FALS 0
#define TRU 1

void parse_input(char *s)
{
    int *args[MAX_NUM_OF_ARGS];
    size_t i;

    static int init = FALS;

    long arg;          /* arg from string */
    char *arg_end;

    for (arg = strtol(s, &arg_end, DECIMAL), i = 0; s != arg_end;
                arg = strtol(s, &arg_end, DECIMAL), ++i) {
        s = arg_end;
        args[i] = malloc(sizeof(int));
        *(args[i]) = (int)arg;
    }

    if (init == FALS) {
        initialize_ht(**args);
        free(*args);
        init = TRU;
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
            deletemin();
            break;
        case OP_DELETE :
            delete_entry(**++args);
            break;
        case OP_PRINT :
            print_heap();
            print_ht();
        default :
            fprintf(stderr, "WARNING: can't parse input: Operation %i not \
                                found \n EXITING IMMEDIATELY \n", **args);
            exit(EXIT_FAILURE);
            break;
    }
}

void cleanup() {
    int i;
    struct HashEntry *h;
    extern FILE *infp, *outfp;

    for (i = 0; i < htab.size; ++i) {
        h = htab.hep + i;
        if ( (h = h->next) == NULL)
            continue;
        while (h->next != NULL) {
            h = h->next;
            free(h->prior);
        }
        free(h);
    }
    free(htab.hep);
    /* free(heapp.hep);*/
    fclose(infp);
    fclose(outfp);

}

#include "hash_heap.h"

#define READ "r"
#define STDIN 0
#define MAX_LINE_SIZE 256

void parse_input(char *);
void run_command(int *args);

/* globally static, declared in .h, defined here */
struct HashTable htabp;

int main(int argc, char *argv[])
{
    FILE *fp;
    char *line;
    size_t len = MAX_LINE_SIZE;
    ssize_t nread;

    /*int i;*/

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
        /* printf("from while: %s", line);*/
        parse_input(line);
    }
    /* look more into getline */
    /*printf("%lu %lu\n", getline(&line, &len, fp), len);

     htabp = allocate_storage_ht(#);*/


/*    using this test seems to verfiy the size is correct
    memset(htabp.hep, 0, (htabp.size+2) * sizeof(struct HashEntry));
    for(i = 0; i < htabp.size; ++i)
    {
        printf("value at %i: %i\n", i, htabp.hep[i].data);
    }*/

    free(htabp.hep);
    free(line);
    fclose(fp);
    return EXIT_SUCCESS;
}

#define OP_LOOKUP 0
#define OP_INSERT 1
#define OP_DELMIN 2
#define OP_DELETE 3

#define DECIMAL 10
#define MAX_NUM_OF_ARGS 2
void parse_input(char *s)
{
    int *args;
    size_t i;
    size_t argc;

    long arg;          /* arg from string */
    char *arg_end;

    args = malloc(sizeof(int) * MAX_NUM_OF_ARGS);
    for (arg = strtol(s, &arg_end, DECIMAL), i = 0; s != arg_end;
                arg = strtol(s, &arg_end, DECIMAL), ++i) {
        s = arg_end;    /* if the pointer to char * is same as arg_end, reached end */
        args[i] = (int)arg;
        /* printf("from args: %i\n", args[i]);*/
    }

    argc = i;

    if (argc == 1)
    {   /* initialize */
        initialize_ht(*args);
        return;
    }
    run_command(args);
}

void run_command(int *args) {
    switch (*args) {
        case OP_LOOKUP :
            printf("LOOKUP: %i\n", *++args);
            break;
        case OP_INSERT :
            printf("INSERT: %i\n", *++args);
            break;
        case OP_DELMIN :
            printf("DELMIN: %i\n", *++args);
            break;
        case OP_DELETE :
            printf("DELETE: %i\n", *++args);
            break;
        default :
            fprintf(stderr, "WARNING: can't parse input: Operation %i not found \
                                \n EXITING IMMEDIATELY \n", *args);
            exit(EXIT_FAILURE);
    }
}

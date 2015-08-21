#include "cli.h"

#define STDIN 0
#define READ "r"
#define WRITE "w"

#define INTERACTIVE 1
#define INFILE 2
#define IN_OUT_FILE 3

/* Open STDIN for Input */
void open_stdin() {
    extern FILE* infp;

    fprintf(stdout, "Did not enter a filename. Enterting Interactive Mode...\n");
    if ( (infp = fdopen(STDIN, READ)) == NULL) {
        fprintf(stderr, "Cannot read from stdin\n");
        exit(EXIT_FAILURE);
    }
}

/* Open Default Log File */
void open_log() {
    extern FILE* outfp;

    if ( (outfp = fopen("log.out", WRITE)) == NULL) {
        fprintf(stderr, "Cannot open a log file\n");
        exit(EXIT_FAILURE);
    }
}
/* Open Named Input File */
void open_infile(char *argv[]) {
    extern FILE* infp;

    if ( (infp = fopen(argv[1], READ)) == NULL) {
        fprintf(stderr, "Failed to open in file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
}
/* Open Named Output File */
void open_outfile(char *argv[]) {
    extern FILE* outfp;

    if ( (argv[1] == argv[2]) || (outfp = fopen(argv[2], WRITE)) == NULL ) {
        fprintf(stderr, "Failed to open out file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
}

/* Decide How to Open Files */
void file_setup(int argc, char *argv[]) {
    switch(argc) {
    case INTERACTIVE :
        open_stdin();
        open_log();
        invoke_interactive_mode();
        break;
    case INFILE :
        open_infile(argv);
        open_log();
        break;
    case IN_OUT_FILE :
        open_infile(argv);
        open_outfile(argv);
        break;
    default :
        fprintf(stderr, "Usage: [in file] [out file]\n");
        exit(EXIT_FAILURE);
        break;
    }
}


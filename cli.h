#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void open_stdin(void);
void open_log(void);
void open_infile(char *argv[]);
void open_outfile(char *argv[]);

void file_setup(int argc, char *argv[]);

void invoke_interactive_mode(void);

#endif /* FILES_H */

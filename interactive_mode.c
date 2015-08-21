#include "cli.h"

/* BCC: Move into File */
#define FOREVER for(;;)
void invoke_interactive_mode() { /* Work in Progress */
    /* int c;

    fprintf(stdout, "Enter a Command. Enter 'm' for Menu. \n");
    FOREVER {
        c = getchar();

        switch ((unsigned char) c)
        {
        case '0' : case 'i' : case 'I':
            system("clear");
            fprintf(stdout, "i for insert\n");
            break;
        case 'm' :
            system("clear");
            fprintf(stdout, "\nCommands:\t\n\ \
                i:  insert\n\
                d:  delete\n\
                dm: deletemin\n\
                l:  lookup\n\
                p:  print HT\n
                m:  print this menu\n");
            break;
        case 'q' :
            fprintf(stderr, "Quiting the program...\n");
            exit(EXIT_SUCCESS);
            break;
        case '\n' :
            break;
        default:
            printf("\nunknown command %c\n", c);
            break;
        }
    }*/
    return;
}



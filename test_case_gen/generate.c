#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int i;

    i = 0;
    srand((unsigned)time(NULL));

    printf("101\n");                /* initialization number only */
    while (i++ < 1000)
        printf("0 %i\n", rand() % 9999);

    return EXIT_SUCCESS;
}


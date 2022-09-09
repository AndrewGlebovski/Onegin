#include <stdlib.h>
#include "onegin.hpp"


int read_poem(char *poem[], FILE *stream) {
    if (!stream)
        printf("File pointer was null");

    for(int l = 0; l < MAX_LINES; l++) {
        poem[l] = (char *) malloc(MAX_LENGTH);

        if (fgets(poem[l], MAX_LENGTH, stream) == NULL) {
            poem[l] = NULL;
            return l;
        }
    }

    return 1000;
}


void print_poem(char *poem[], FILE *stream) {
    if (!stream)
        printf("File pointer was null");

    for(int i = 0; poem[i] != NULL && i < MAX_LINES; i++) {
        if (fputs(poem[i], stream) == EOF)
            printf("fputs returned EOF\n");
    }
}

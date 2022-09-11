/**
 * \file io.cpp
 * \brief Contains input and output functions
*/

#include <stdlib.h>
#include "onegin.hpp"


int read_poem(char ***poem, FILE *stream) {
    if (!stream)
        printf("File pointer was null");

    int lines = 0;
    char line[100];
    while(fgets(line, MAX_LENGTH, stream) != NULL) 
        lines++;

    rewind(stream);

    *poem = (char **) calloc(lines, sizeof(char *));

    for(int l = 0; l < lines; l++) {
        (*poem)[l] = (char *) calloc(MAX_LENGTH, sizeof(char));
        fgets((*poem)[l], MAX_LENGTH, stream);
    }

    return lines;
}


void print_poem(char *poem[], FILE *stream) {
    if (!stream)
        printf("File pointer was null");

    for(int i = 0; poem[i] != NULL; i++) {
        if (fputs(poem[i], stream) == EOF)
            printf("fputs returned EOF\n");
        fflush(stream);
    }
}
